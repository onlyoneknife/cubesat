 /***************************************************************************//**
 * @file I2C_Driver.c
 * @author Stefan Damkjar
 * @date 2016-05-18
 *******************************************************************************
 * @section License
 * <b>Copyright (C) 2015  Stefan Damkjar</b>
 *******************************************************************************
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 ******************************************************************************/


/*******************************************************************************
 *******************************  INCLUDES   ***********************************
 ******************************************************************************/


/* System Includes */
#include <stdint.h> 
#include <stdbool.h>

/* EFM32 EMLIB Includes */
#include "em_i2c.h"
#include "em_dma.h"

/* FreeRTOS Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Driver Includes */
#include "sharedtypes.h"
#include "I2C_Driver.h"
#include "dmactrl.h"

/* GomSpace Includes */
#include <csp/csp_buffer.h>


/*******************************************************************************
 *******************************   GLOBALS   ***********************************
 ******************************************************************************/


/** I2C master mode lock */
xSemaphoreHandle i2c_lock = NULL;

device_object_t device[1] = {
  {
    .base = (uint8_t *)0x58000000,
    .is_initialised = 0,
    .is_busy = 0,
    .mode = DEVICE_MODE_M_T,
    .callback = NULL,
  },
};

/* DMA callback structure */
static DMA_CB_TypeDef dmaCallback;

/* Transfer flag */
static volatile bool transferActive = false;

/* I2C error flag */
static volatile bool i2cError = false;

/* Helper variables. These are used by I2C interrupt handler to 
 * retrieve the last bytes when doing a DMA read. */
static uint8_t *rxPointer;
static uint8_t bytesLeft;


/*******************************************************************************
 *******************************  FUNCTIONS  ***********************************
 ******************************************************************************/


/*****************************************************************************
 * @brief  Aborts the current transfer and sets the error flag
 *****************************************************************************/
void I2C_ErrorAbort(I2C_TypeDef *i2c)
{
  i2c->CMD = I2C_CMD_ABORT;
  transferActive = false;
  i2cError = true;  
}


/**************************************************************************//**
 * @brief  Setup I2C
 *
 * @param handle Which I2C bus (if more than one exists)
 * @param mode I2C device mode. Must be either I2C_MASTER or I2C_SLAVE
 * @param addr Own slave address
 * @param speed Bus speed in kbps
 *
 *****************************************************************************/
void I2C0_setup(int handle, int mode, uint8_t addr, uint16_t speed,
  int queue_len_tx, int queue_len_rx, i2c_callback_t callback) 
{

  /* Exit the BUSY state. The I2C will be in this state out of RESET. */
  if (I2C0->STATE & I2C_STATE_BUSY)
  {
    I2C0->CMD = I2C_CMD_ABORT;
  }
  
  /* Enable the Clock Low Timeout counter */
  I2C0->CTRL = (I2C0->CTRL & ~_I2C_CTRL_CLTO_MASK) | I2C_CTRL_CLTO_160PCC;
  
  /* Enable error interrupts */
  I2C0->IEN |= I2C_IEN_ARBLOST | I2C_IEN_BUSERR | I2C_IEN_CLTO;

  NVIC_EnableIRQ(I2C0_IRQn);

  /** Setup FreeRTOS semaphore and queues */

  if (i2c_lock == NULL)
    i2c_lock = xSemaphoreCreateMutex();
  if (i2c_lock == NULL)
    return E_NO_BUFFER;

  /* TX Queue */
  if (device[handle].tx.queue == NULL) {
    device[handle].tx.queue = xQueueCreate(queue_len_tx, sizeof(i2c_frame_t *));
  }

  /* RX Queue */
  if ((device[handle].rx.queue == NULL) && (queue_len_rx > 0)) {
    device[handle].rx.queue = xQueueCreate(queue_len_rx, sizeof(i2c_frame_t *));
  }
}


/*****************************************************************************
 * @brief Configure DMA to send and receive over I2C0
 *****************************************************************************/
void I2C0_dmaInit(void)
{
  CMU_ClockEnable(cmuClock_DMA, true);  
  
  DMA_Init_TypeDef        dmaInit;
  DMA_CfgChannel_TypeDef  txChannelConfig;
  DMA_CfgDescr_TypeDef    txDescriptorConfig;
  DMA_CfgChannel_TypeDef  rxChannelConfig;
  DMA_CfgDescr_TypeDef    rxDescriptorConfig;
  
  /* Initializing the DMA */
  dmaInit.hprot        = 0;
  dmaInit.controlBlock = dmaControlBlock;
  DMA_Init(&dmaInit);
  
  /* Setup call-back function */  
  dmaCallback.cbFunc  = transferComplete;
  dmaCallback.userPtr = NULL;

  /* Setting up TX channel */
  txChannelConfig.highPri   = false;
  txChannelConfig.enableInt = true;
  txChannelConfig.select    = DMAREQ_I2C0_TXBL;
  txChannelConfig.cb        = &dmaCallback;
  DMA_CfgChannel(DMA_CHANNEL_I2C_TX, &txChannelConfig);

  /* Setting up TX channel descriptor */
  txDescriptorConfig.dstInc  = dmaDataIncNone;
  txDescriptorConfig.srcInc  = dmaDataInc1;
  txDescriptorConfig.size    = dmaDataSize1;
  txDescriptorConfig.arbRate = dmaArbitrate1;
  txDescriptorConfig.hprot   = 0;
  DMA_CfgDescr(DMA_CHANNEL_I2C_TX, true, &txDescriptorConfig);
  
  /* Setting up RX channel */
  rxChannelConfig.highPri   = false;
  rxChannelConfig.enableInt = true;
  rxChannelConfig.select    = DMAREQ_I2C0_RXDATAV;
  rxChannelConfig.cb        = &dmaCallback;
  DMA_CfgChannel(DMA_CHANNEL_I2C_RX, &rxChannelConfig);

  /* Setting up RX channel descriptor */
  rxDescriptorConfig.dstInc  = dmaDataInc1;
  rxDescriptorConfig.srcInc  = dmaDataIncNone;
  rxDescriptorConfig.size    = dmaDataSize1;
  rxDescriptorConfig.arbRate = dmaArbitrate1;
  rxDescriptorConfig.hprot   = 0;
  DMA_CfgDescr(DMA_CHANNEL_I2C_RX, true, &rxDescriptorConfig);
}


/*****************************************************************************
 * @breif   Send I2C frame via the selected device
 *
 * @param   handle Handle to the device
 * @param   frame Pointer to I2C frame
 * @param   timeout Ticks to wait
 * @return  Error code as per error.h
 *****************************************************************************/
int I2C_send(int handle, i2c_frame_t * frame, uint16_t timeout) {

  if (xQueueSendToBack(device[handle].tx.queue, &frame, timeout) == pdFALSE)
    return E_TIMEOUT;

  return E_NO_ERR;
}


/*****************************************************************************
 * @brief   Send I2C address and checks for Ack
 *****************************************************************************/
void I2C_sendAddr(I2C_TypeDef *i2c, uint8_t deviceAddress) {
  /* Send the address */
  i2c->TXDATA     = deviceAddress;
  i2c->CMD        = I2C_CMD_START;

  if ( !i2cWaitForAckNack() )
  {
    I2C_ErrorAbort();
    return;
  }
}


/*****************************************************************************
 * @brief  Writes bytes to I2C EEPROM using DMA. 
 * 
 * @param deviceAddress 
 *      I2C address of EEPROM
 * 
 * @param data
 *      Pointer to the data buffer
 * 
 * @param length
 *      Number of bytes to write
 *****************************************************************************/
void I2C_dmaWrite(I2C_TypeDef *i2c, uint8_t *data, uint8_t length)
{ 

  /* Abort if an error has been detected */
  if ( i2cError )
  {
    return;
  }
   
  /* Automatically generate a STOP condition when there is no
   * more data to send. The DMA must be fast enough to 
   * keep up (normally not a problem unless the DMA is
   * been prescaled). */
  i2c->CTRL |= I2C_CTRL_AUTOSE;

  /* Set transfer active flag. Cleared by interrupt handler
   * when STOP condition has been sent. */
  transferActive = true;
  
  /* Activate DMA */
  DMA_ActivateBasic(DMA_CHANNEL_I2C_TX,         /* TX DMA channel */
                    true,                       /* Primary descriptor */
                    false,                      /* No burst */
                    (void *)&(i2c->TXDATA),     /* Write to TXDATA */
                    (void *)data,               /* Read from txBuffer */
                    length - 1 );               /* Number of transfers */
}


/*****************************************************************************
 * @brief  Reads from I2C using DMA. 
 * 
 * @param deviceAddress 
 *      I2C address
 * 
 * @param data
 *      Pointer to the data buffer
 * 
 * @param length
 *      Number of bytes to read
 *****************************************************************************/
void I2C_dmaRead(I2C_TypeDef *i2c, uint8_t *data, uint8_t length)
{ 
  
  /* Abort if an error has occured */
  if ( i2cError )
  {
    return;
  }
  
  /* These are used by the RX interrupt handler
   * to fetch the last two bytes of the transaction */
  rxPointer = data + length - 2;
  bytesLeft = 2;
  
  /* Set transfer active flag. Cleared by interrupt handler
   * when STOP condition has been sent. */
  transferActive = true;
  
  /* Activate DMA */
  DMA_ActivateBasic(DMA_CHANNEL_I2C_RX,         /* RX DMA channel */
                    true,                       /* Primary descriptor */
                    false,                      /* No burst */
                    (void *)data,               /* Write to rx buffer */        
                    (void *)&(i2c->RXDATA),     /* Read from RXDATA */
                    length - 3 );               /* Number of transfers */
}


/*****************************************************************************
 * @brief  Pick up a transmission from scratch or continue an on-going
 *         transmission (Context: ISR ONLY)
 * @param  handle Handle to device
 *****************************************************************************/
static void I2C_try_tx_from_isr(I2C_TypeDef *i2c, int handle,
  portBASE_TYPE * pxTaskWoken)
{

  uint8_t flags = 0;

  if (device[handle].is_initialised == 0)
    return;

  if (uxQueueMessagesWaitingFromISR(device[handle].tx.queue) > 0 ||
    device[handle].tx.frame != NULL)
  {
    device[handle].is_busy = 1;
    flags |= I2C_CMD_START;
  }
  else
  {
    device[handle].is_busy = 0;
    flags |= I2C_CMD_STOP;
  }

  flags |= I2C_CMD_ACK;

  device[handle].mode = DEVICE_MODE_M_T;

  i2c->CMD = flags;
}


/*****************************************************************************
 * @brief  Handles various I2C events and errors
 * 
 * When a STOP condition has been successfully sent, the MSTOP
 * interrupt is triggered and the transfer is marked as complete. 
 * 
 * When receiving with DMA, the last two bytes must be fetched 
 * manually by software. They are fetched by listening for the
 * RXDATAV interrupt. The last byte should per the I2C standard
 * be NACK'ed, to inform the slave that it is the last byte of
 * the transfer. 
 * 
 * The three errors: ARBLOST, BUSERR and CLTO are handled here. 
 * In all cases, the current transfer is aborted, and the error
 * flag is set to inform the main loop that an error occured
 * during the transfer. 
 *
 * The interrupt table is in assembly startup file startup_efm32.s
 * 
 *****************************************************************************/
void I2C0_IRQHandler(void)
{
  static int handle, len;
  static uint8_t dest;

  bool no_err = true;

  /* Save the interrupt flag and state registers */
  uint32_t flags  = I2C0->IF;
  uint32_t state  = I2C0->STATE;
  uint32_t status = I2C0->STATUS;
  
  /* Check for error flags from I2C peripheral */
  /* TODO: Error handling might conflict with GomSpace hardware */
  if ( flags & (I2C_IF_BUSERR | I2C_IF_CLTO | flags & I2C_IF_ARBLOST )
  {
    /* Restart transmission by resetting next_byte and saving tx_frame pointer */
    device[handle].tx.next_byte = 0;
    I2C_try_tx_from_isr(handle, task_woken);

    I2C0->IFC = flags;
    I2C_ErrorAbort(I2C0);
  }
  else if ( flags & I2C_IF_MSTOP )
  {
    /* Stop condition has been sent. Transfer is complete. */
    I2C0->IFC = I2C_IFC_MSTOP;
    I2C0->IEN &= ~I2C_IEN_MSTOP;
    transferActive = false;
        
    /* Clear AUTOSE if set */
    if ( I2C0->CTRL & I2C_CTRL_AUTOSE )
    {
      I2C0->CTRL &= ~I2C_CTRL_AUTOSE;
    }
  }
  else if ( I2C0->IF & I2C_IF_RXDATAV )
  {
    /* Read out the last two bytes here. Reading RXDATA
     * clears the interrupt flag. */
    *rxPointer++ = I2C0->RXDATA;
    
    if ( --bytesLeft == 0 )
    {
      /* Transfer is complete, NACK last byte and send STOP condition */
      I2C0->CMD = I2C_CMD_NACK;
      I2C0->IEN &= ~I2C_IEN_RXDATAV;
      I2C0->CMD = I2C_CMD_STOP;
    }
    else
    {
      /* ACK the second last byte */
      I2C0->CMD = I2C_CMD_ACK;
    }
  }
  /* Check for start condition indicating outgoing frames */
  else if ( flags & (I2C_IF_RSTART | I2C_IF_START) )
  {
    /* Mark as busy, so start flag is not sent from task context while
     * transmission is active */
    device[handle].is_busy = 1;

    /* If this is the beginning of a new frame, dequeue */
    if (device[handle].tx.frame == NULL && device[handle].rx.frame == NULL)
    {
      /* Try do dequeue element, if it fails, stop transmission */
      xQueueReceiveFromISR(device[handle].tx.queue,
                           &device[handle].tx.frame,
                           task_woken);

      /* When dequeue fails, tx frame will be empty */
      if (device[handle].tx.frame == NULL)
      {
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        device[handle].mode = DEVICE_MODE_ERR;
        I2C_ErrorAbort(I2C0);
      }
      /* Start master transmit if tx len is not zero */
      else if (device[handle].tx.frame->len)
      {
        device[handle].mode = DEVICE_MODE_M_T;
        device[handle].tx.next_byte = 0;
      }
      /* Start master receive if rx len is not zero */
      else if (device[handle].tx.frame->len_rx)
      {
        device[handle].mode = DEVICE_MODE_M_R;
        device[handle].rx.frame = device[handle].tx.frame;
        device[handle].tx.frame = NULL;
        device[handle].rx.frame->len = device[handle].rx.frame->len_rx;
        device[handle].rx.next_byte = 0;
      }
      /* If this point is reached, something is wrong... Stop tranmission */
      else
      {
        csp_buffer_free_isr(device[handle].tx.frame);
        device[handle].tx.frame = NULL;
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        device[handle].mode = DEVICE_MODE_ERR;
        I2C_ErrorAbort(I2C0);
      }
    }

    /* If mode is master receiver then set the read-bit in the address field */
    if (device[handle].mode == DEVICE_MODE_M_R)
    {
      dest = (device[handle].rx.frame->dest << 1) | I2C_READ_BIT;
      device[handle].rx.next_byte = 0;

      I2C_sendAddr(I2C0, dest);
    }
    /* If mode is master transmit then don't set read-bit in the address field */
    else if (defive[handle.mode == DEVICE_MODE_M_T])
    {
      dest = device[handle].tx.frame->dest << 1;
      device[handle].tx.next_byte = 0;

      I2C_sendAddr(I2C0, dest);

      if (device[handle].tx.frame->len > DMA_MAX_MINUS_1 )
      {
        I2C_dmaWrite(I2C0,
          &device[handle].tx.frame->data[device[handle].tx.next_byte]),
          DMA_MAX_MINUS_1 );
        device[handle].tx.next_byte += DMA_MAX_MINUS_1;
      }
      else
      {
        I2C_dmaWrite(I2C0,
          &device[handle].tx.frame->data[device[handle].tx.next_byte],
          device[handle].tx.frame->len);
        device[handle].tx.next_byte += device[handle].tx.frame->len;
      }
    }
    else
    {
      I2C_ErrorAbort(I2C0);
    }
    
    // TODO: Maybe add I2C0->CMD = I2C_CMD_ACK;
  }
  /* An ACK is received */
  else if ( flags & I2C_IF_ACK)
  {
    /* ACK received in transmitter mode. A node is ready to be written to */
    if ( state & I2C_STATE_TRANSMITTER )
    {

      /* Calculate remaining length */
      len = device[handle].tx.frame->len - device[handle].tx.next_byte;

      /* Error if frame is empty */
      if (device[handle].tx.frame == NULL)
      {
        I2C_ErrorAbort(I2C0);
      }
      /* Continue transmitting */
      else if (len > 0)
      {
        if (len > DMA_MAX_MINUS_1 + 1)
        {
          I2C_dmaWrite(I2C0,
            &device[handle].tx.frame->data[device[handle].tx.next_byte],
            DMA_MAX_MINUS_1 + 1);
          device[handle].tx.next_byte += PCA9665_MAX_BUF;
        }
        else
        { 
          I2C_dmaWrite(I2C0,
            &device[handle].tx.frame->data[device[handle].tx.next_byte],
            len);
          device[handle].tx.next_byte += len;
        }

        // TODO: Maybe add I2C0->CMD = I2C_CMD_ACK;
      }
      /* Or, Change from master transmit, to master read if wanted */
      }
      else if (device[handle].tx.frame->len_rx)
      {
        device[handle].mode = DEVICE_MODE_M_R;
        device[handle].rx.frame = device[handle].tx.frame;
        device[handle].tx.frame = NULL;
        device[handle].rx.frame->len = device[handle].rx.frame->len_rx;

        /* Send repeated start */
        I2C0->CMD = (I2C_CMD_ACK | I2C_CMD_START);
      }
      else
      {
        csp_buffer_free_isr(device[handle].tx.frame);
        device[handle].tx.frame = NULL;
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
      }
    }


    


  }
  /* If an NACK is received while attempting to perform a write */
  else if ( flags & (I2C_IF_NACK) && state & (I2C_STATE_TRANSMITTER) )
  {
    if (device[handle].tx.frame != NULL)
    {
      csp_buffer_free_isr(device[handle].tx.frame);
      device[handle].tx.frame = NULL;
    }

    I2C_try_tx_from_isr(I2C0, handle, task_woken);

    I2C0->IFC = flags;
    I2C_ErrorAbort(I2C0);
  }
  else if ()
}



  else if ( flags & I2C_IF_MSTOP )
  {
    /* Stop condition has been sent. Transfer is complete. */
    I2C0->IFC = I2C_IFC_MSTOP;
    I2C0->IEN &= ~I2C_IEN_MSTOP;
    transferActive = false;
        
    /* Clear AUTOSE if set */
    if ( I2C0->CTRL & I2C_CTRL_AUTOSE )
    {
      I2C0->CTRL &= ~I2C_CTRL_AUTOSE;
    }
  }
  else if ( I2C0->IF & I2C_IF_RXDATAV )
  {
    /* Read out the last two bytes here. Reading RXDATA
     * clears the interrupt flag. */
    *rxPointer++ = I2C0->RXDATA;
    /* Try do dequeue element, if it fails, stop transmission */
        xQueueReceiveFromISR(device[handle].tx.queue, &device[handle].tx.frame, task_woken);
    
    if ( --bytesLeft == 0 )
    {
      /* Transfer is complete, NACK last byte and send STOP condition */
      I2C0->CMD = I2C_CMD_NACK;
      I2C0->IEN &= ~I2C_IEN_RXDATAV;
      I2C0->CMD = I2C_CMD_STOP;
    }
    else
    {
      /* ACK the second last byte */
      I2C0->CMD = I2C_CMD_ACK;
    }
  }
}


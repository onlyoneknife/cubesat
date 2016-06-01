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
 * @brief  Called when DMA transfer is complete
 * Enables interrupts to finish the transfer.
 *****************************************************************************/
void I2C_transferComplete(unsigned int channel, bool primary, void *user)
{
  /* Ignore unused parameters */
  (void) primary;
  (void) user;
 
  if ( channel == DMA_CHANNEL_I2C_TX )
  {
    /* Enable MSTOP interrupt */
    I2C0->IEN |= I2C_IEN_MSTOP;
  }
  else if ( channel == DMA_CHANNEL_I2C_RX )
  {
    /* Stop automatick ACK'ing bytes */
    I2C0->CTRL &= ~I2C_CTRL_AUTOACK;
    
    /* Enable RX and MSTOP interrupt */
    I2C0->IEN |= I2C_IEN_RXDATAV | I2C_IEN_MSTOP;
  }
}


/*****************************************************************************
 * @brief  Aborts the current transfer and sets the error flag
 *****************************************************************************/
void I2C_ErrorAbort(I2C_TypeDef *i2c)
{
  i2c->CMD = I2C_CMD_ABORT;
  transferActive = false;
  i2cError = true;  
}


void I2C_CleanupTxRx(int handle)
{
  /* Clean up RX */
  if (device[handle].rx.frame != NULL) {
    csp_buffer_free_isr(device[handle].rx.frame);
    device[handle].rx.frame = NULL;
  }

  /* Clean up TX */
  if (device[handle].tx.frame != NULL) {
    csp_buffer_free_isr(device[handle].tx.frame);
    device[handle].tx.frame = NULL;
  }
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

  /* Error checking */
  if (handle >= efm32_device_count)
    return E_NO_DEVICE;

  if (device[handle].is_initialised)
    return E_NO_ERR;

  if (queue_len_tx <= 0)
    return E_INVALID_PARAM;

  if (mode != I2C_MASTER)
    return E_INVALID_PARAM;

  /** Setup FreeRTOS semaphore and queues */

  if (i2c_lock == NULL)
    i2c_lock = xSemaphoreCreateMutex();
  if (i2c_lock == NULL)
    return E_NO_BUFFER;

  /* TX Queue */
  if (device[handle].tx.queue == NULL)
    device[handle].tx.queue = xQueueCreate(queue_len_tx, sizeof(i2c_frame_t *));

  /* RX Queue */
  if ((device[handle].rx.queue == NULL) && (queue_len_rx > 0))
    device[handle].rx.queue = xQueueCreate(queue_len_rx, sizeof(i2c_frame_t *));

  /* Callback */
  if (callback != NULL) 
    device[handle].callback = callback;

  /* Remember chip memory address, and I2C node address */
  device[handle].slave_addr = addr;
  device[handle].speed = speed;

  I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

  init.enable = true;
  init.master = true;
  init.freq = speed * 1000;
  init.clhr = i2cClockHLRAsymetric;
  I2C_Init(I2C0, &init);

  /* Exit the BUSY state. The I2C will be in this state out of RESET. */
  if (I2C0->STATE & I2C_STATE_BUSY)
  {
    I2C0->CMD = I2C_CMD_ABORT;
  }

  I2C0->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN |
    (1 << _I2C_ROUTE_LOCATION_SHIFT);

  /* Setting up to slave address */
  I2C0->SADDR = device[handle].slave_addr << 1;

  /* Enable the Clock Low Timeout counter */
  I2C0->CTRL = (I2C0->CTRL & ~_I2C_CTRL_CLTO_MASK) | I2C_CTRL_CLTO_160PCC;
  
  /* Enable error interrupts */
  I2C0->IEN |= I2C_IEN_ARBLOST | I2C_IEN_BUSERR | I2C_IEN_CLTO;

  NVIC_EnableIRQ(I2C0_IRQn);

  device[handle].is_initialised = true;
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
  dmaCallback.cbFunc  = I2C_transferComplete;
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
int I2C_send(int handle, i2c_frame_t * frame, uint16_t timeout)
{

  if (xQueueSendToBack(device[handle].tx.queue, &frame, timeout) == pdFALSE)
    return E_TIMEOUT;

  return E_NO_ERR;
}


/**
 * receive I2C frame from selected device
 * Context: Task only
 *
 * @param handle Handle to the device
 * @param frame Pointer to I2C frame (free this when done!!!)
 * @param timeout Number of ticks to wait for a frame
 * @return Returns error code: E_NO_ERR if a frame is received, or E_TIMEOUT if timed out, E_NO_DEVICE if handle is not a valid device
 */
int i2c_receive(int handle, i2c_frame_t ** frame, uint16_t timeout)
{

  if (handle >= efm32_device_count)
    return E_NO_DEVICE;

  if (!device[handle].is_initialised)
    return E_NO_DEVICE;

  if (device[handle].rx.queue == NULL)
    return E_NO_DEVICE;

  if (xQueueReceive(device[handle].rx.queue, frame, timeout) == pdFALSE)
    return E_TIMEOUT;

  return E_NO_ERR;
}


/*****************************************************************************
 * @brief   Send I2C address and checks for Ack
 *****************************************************************************/
void I2C_sendAddr(I2C_TypeDef *i2c, uint8_t deviceAddress)
{

  /* Abort if an error has been detected */
  if ( i2cError )
  {
    return;
  }  

  /* Send the address */
  i2c->TXDATA     = deviceAddress;
  //i2c->CMD        = I2C_CMD_START;

  /*
  if ( !i2cWaitForAckNack() )
  {
    I2C_ErrorAbort();
    return;
  }
  */
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

  /* Wait for any previous transfer to finish */
  while ( transferActive )
  {
    EMU_EnterEM1();
  }

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
void I2C_dmaRead(I2C_TypeDef *i2c, int handle , uint8_t *data, uint8_t length)
{ 
  
  /* Abort if an error has occured */
  if ( i2cError )
  {
    return;
  }

  if (device[handle].rx.frame == NULL)
  {
    return;
  }

  /* Check buffer allocation */
  if (length + device[handle].rx.next_byte > I2C_MTU)
  {
    return;
  }

  /* These are used by the RX interrupt handler
   * to fetch the last two bytes of the transaction */
  rxPointer = data + length - 2;
  bytesLeft = 2;

  /* Automatically ACK received bytes */
  I2C0->CTRL |= I2C_CTRL_AUTOACK;
  
  /* Set transfer active flag. Cleared by interrupt handler
   * when STOP condition has been sent. */
  transferActive = true;

  device[handle].rx.next_byte += count;
  
  /* Activate DMA */
  DMA_ActivateBasic(DMA_CHANNEL_I2C_RX,         /* RX DMA channel */
                    true,                       /* Primary descriptor */
                    false,                      /* No burst */
                    (void *)data,               /* Write to rx buffer */        
                    (void *)&(i2c->RXDATA),     /* Read from RXDATA */
                    length );               /* Number of transfers */
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
    device[handle].mode = DEVICE_MODE_IDLE;
    flags |= I2C_CMD_STOP;
  }

  flags |= I2C_CMD_ACK;

  i2c->CMD = flags;
}


/**
 * Context: Task only
 */
int I2C_master_transaction(int handle, uint8_t addr, void * txbuf, size_t txlen, void * rxbuf, size_t rxlen, uint16_t timeout) {

  if (handle >= efm32_device_count)
    return E_NO_DEVICE;

  if (!device[handle].is_initialised)
    return E_NO_DEVICE;

  if ((txlen > I2C_MTU - 10) || (rxlen > I2C_MTU - 10))
    return E_INVALID_BUF_SIZE;

  i2c_frame_t * frame = csp_buffer_get(I2C_MTU);
  if (frame == NULL)
    return E_NO_BUFFER;

  /* Take the I2C lock */
  xSemaphoreTake(i2c_lock, 10 * configTICK_RATE_HZ);

  /* Temporarily disable the RX callback, because we wish the received message to go into the I2C queue instead */
  void * tmp_callback = device[handle].callback;
  device[handle].callback = NULL;

  frame->dest = addr;
  memcpy(&frame->data[0], txbuf, txlen);
  frame->len = txlen;
  frame->len_rx = rxlen;

  if (I2C_send(handle, frame, 0) != E_NO_ERR) {
    csp_buffer_free(frame);
    device[handle].callback = tmp_callback;
    xSemaphoreGive(i2c_lock);
    return E_TIMEOUT;
  }

  if (rxlen == 0) {
    device[handle].callback = tmp_callback;
    xSemaphoreGive(i2c_lock);
    return E_NO_ERR;
  }

  if (I2C_receive(handle, &frame, timeout) != E_NO_ERR) {
    device[handle].callback = tmp_callback;
    xSemaphoreGive(i2c_lock);
    return E_TIMEOUT;
  }

  memcpy(rxbuf, &frame->data[0], rxlen);

  csp_buffer_free(frame);
  device[handle].callback = tmp_callback;
  xSemaphoreGive(i2c_lock);
  return E_NO_ERR;

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
  static int      handle      = 0;
  static int      len         = 0;
  static int      remaining   = 0;
  static uint8_t  dest        = 0;
  static bool     readAdrSent = false;
  static bool     slaveAdrRec = false;
  static bool     no_err      = true;

  /* Save the interrupt flag and state registers */
  uint32_t flags  = I2C0->IF;
  uint32_t state  = I2C0->STATE;
  uint32_t status = I2C0->STATUS;
  
  /* Check for error flags from I2C peripheral */
  /* TODO: Error handling might conflict with GomSpace hardware */
  if ( flags & (I2C_IF_BUSERR | I2C_IF_CLTO) )
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
  else if ( flags & I2C_IF_START )
  {
    /* Mark as busy, so start flag is not sent from task context while
     * transmission is active */
    device[handle].is_busy = true;

    /* If this is the beginning of a new frame, dequeue and decide TX or RX*/
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
        I2C_ErrorAbort(I2C0);
      }
    }

    /* If mode is master receiver then set the read-bit in the address field */
    if (device[handle].mode == DEVICE_MODE_M_R && !i2cError)
    {
      dest = (device[handle].rx.frame->dest << 1) | I2C_READ_BIT;
      device[handle].rx.next_byte = 0;

      /* Set length of frame to receive */
      if (device[handle].rx.frame->len > DMA_MAX_MINUS_1 + 1) {
        len = DMA_MAX_MINUS_1 + 1;
      } else {
        len = device[handle].rx.frame->len;
      }
      
      /* Clear all pending interrupts prior to starting transfer. */
      I2C0->IFC = _I2C_IFC_MASK;
      
      I2C_sendAddr(I2C0, dest);
      readAdrSent = true;
    }
    /* If mode is master transmit then don't set read-bit in the address field */
    else if (device[handle].mode == DEVICE_MODE_M_T && !i2cError)
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
      csp_buffer_free_isr(device[handle].tx.frame);
      device[handle].tx.frame = NULL;
      I2C_try_tx_from_isr(I2C0, handle, task_woken);
      I2C_ErrorAbort(I2C0);
    }
    
    I2C0->CMD = I2C_CMD_ACK;
  }
  /* Master transmit mode */
  if ( device[handle].mode == DEVICE_MODE_M_T )
  {
    /* ACK received while in master tx mode. A node is ready to be written to */
    if ( flags & I2C_IF_ACK )
    {
      
      /* Calculate remaining length */
      len = device[handle].tx.frame->len - device[handle].tx.next_byte;

      /* Error if frame is empty */
      if (device[handle].tx.frame == NULL)
      {
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        device[handle].mode = DEVICE_MODE_ERR;
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
            &device[handle].tx.frame->data[device[handle].tx.next_byte], len);
          device[handle].tx.next_byte += len;
        }

        I2C0->CMD = I2C_CMD_ACK;
      }
      /* Or, Change from master transmit, to master read if wanted */
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
        I2C_ErrorAbort(I2C0);
      }
    }
    /* ERROR: NACK is received while trying to perform a write in master mode */
    else if ( flags & I2C_IF_NACK )
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
    /* ARBITRATION LOST: Start condition failed */
    else if ( flags & I2C_IF_ARBLOST )
    {
      /* Restart transmission by resetting next_byte and saving tx_frame pointer */
      device[handle].tx.next_byte = 0;
      I2C_try_tx_from_isr(handle, task_woken);

      I2C0->IFC = flags;
      I2C_ErrorAbort(I2C0);
    }
  }
  /* Master receiver mode */
  else if ( device[handle].mode == DEVICE_MODE_M_R )
  {
    /* READ ERROR: A read has failed */
    if ( flags & I2C_NACK && readAdrSent )
    {

      /* Clear read address sent flag */
      readAdrSent = false;

      /* Check for errors */
      if (device[handle].rx.frame == NULL)
      {
        I2C_CleanupTxRx(handle);
        /* Start up again */
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        I2C_ErrorAbort(I2C0);
      }
      /* Proceed if no error was found */
      else
      {
        csp_buffer_free_isr(device[handle].rx.frame);
        device[handle].rx.frame = NULL;
        /* Start up again */
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
      }
    }
    /* READ ACK: A node is ready to be read from */
    else if ( flags & (I2C_IF_ACK | I2C_IF_NACK) )
    {

      /* Clear read address sent flag */
      readAdrSent = false;

      /* Check for errors */
      if ( device[handle].rx.frame == NULL || device[handle].rx.queue == NULL )
      {
        I2C_CleanupTxRx(handle);
        /* Start up again */
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        I2C_ErrorAbort(I2C0);
      }
      /* Proceed if no error was found */
      else {

        I2C_dmaRead(I2C0, handle, 
          &device[handle].rx.frame->data[device[handle].rx.next_byte], len)

        remaining = device[handle].rx.frame->len - device[handle].rx.next_byte;

        /* If no more to receive */
        else if (remaining == 0) {

          if (xQueueSendToBackFromISR(device[handle].rx.queue,
            &device[handle].rx.frame, task_woken)  == pdFALSE)
          {
            csp_buffer_free_isr(device[handle].rx.frame);
          }
          device[handle].rx.frame = NULL;
          I2C_try_tx_from_isr(handle, task_woken);
        }

        else if (remaining > DMA_MAX_MINUS_1 + 1)
        {
          len = DMA_MAX_MINUS_1 + 1;
        }
        else
        {
          len = remaining;
        }

        I2C0->CMD = I2C_CMD_ACK;
      }
    }
  }
  /**
   * SLAVE RECEIVER BUFFERED MODE
   */
  else if ( flags & I2C_IF_ADDR )
  {
    /* Check if RX frame was started */
    if (device[handle].rx.frame != NULL)
    {
      I2C_CleanupTxRx(handle);
      /* Start up again */
      I2C_try_tx_from_isr(I2C0, handle, task_woken);
      I2C_ErrorAbort(I2C0);
    }
    /* Continue if successful */
    else
    {

      /* Enable slave address received flag */
      slaveAdrRec = true;

      /* Allocate new frame */
      device[handle].rx.frame = csp_buffer_get_isr(I2C_MTU);

      /* Check for failure */
      if (device[handle].rx.frame == NULL)
      {
        I2C_CleanupTxRx(handle);
        /* Start up again */
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        I2C_ErrorAbort(I2C0);
      }
      else
      /* Continue if successful */
      {
        device[handle].is_busy = 1;
        device[handle].rx.next_byte = 0;
        device[handle].rx.frame->len = 0;
        device[handle].rx.frame->dest = device[handle].slave_addr;

        I2C0->CMD = I2C_CMD_ACK;
      }
    }
  }
  else if ( slaveAdrRec )
  {
    if ( flags & I2C_IF_ACK )
    {
      /* Check for failure */
      if (device[handle].rx.frame == NULL)
      {
        I2C_CleanupTxRx(handle);
        /* Start up again */
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        I2C_ErrorAbort(I2C0);
      }
      else
      /* Continue if successful */
      {

        /* Receive data, if any */
        I2C_dmaRead(I2C0, handle, 
          &device[handle].rx.frame->data[device[handle].rx.next_byte], len)

        /* Limit incoming bytes */
        pca9665_write_reg(handle, I2CCOUNT, (device[handle].rx.next_byte + PCA9665_MAX_BUF > I2C_MTU) ? (I2C_MTU - device[handle].rx.next_byte) | 0x80 : PCA9665_MAX_BUF);

        I2C0->CMD = I2C_CMD_ACK;
      }
    }
    else if ( flags & (I2C_IF_NACK | I2C_IF_SSTOP) )
    {

      /* Clear slave address received flag */
      slaveAdrRec = false;

      /* Check for failure */
      if (device[handle].rx.frame == NULL)
      {
        I2C_CleanupTxRx(handle);
        /* Start up again */
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        I2C_ErrorAbort(I2C0);
      }
      else
      /* Continue if successful */
      {
        /* Receive data, if any */
        I2C_dmaRead(I2C0, handle, 
          &device[handle].rx.frame->data[device[handle].rx.next_byte], len)

        /* Queue up frame
         * Callback takes priority over RX queue
         * I2C master transaction temporarily disables the callback during master transactions in order to
         * ensure that the message is placed in the RX queue. */
        device[handle].rx.frame->len = device[handle].rx.next_byte;

        if (device[handle].callback != NULL)
        {
          device[handle].callback(device[handle].rx.frame, task_woken);
        }
        else if (device[handle].rx.queue != NULL)
        {
          if (xQueueSendToBackFromISR(device[handle].rx.queue, &device[handle].rx.frame, task_woken)  == pdFALSE)
          {
            csp_buffer_free_isr(device[handle].rx.frame);
          }
        }
        else
        {
          csp_buffer_free_isr(device[handle].rx.frame);
        }

        /* The frame has been freed now */
        device[handle].rx.frame = NULL;

        /* Set back to master mode */
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
      }
    }
  }
  /**
   * Other IRQ's, typically indicates a hardware or protcol error
   * IDLE status is error if asserted at same time as Serial Interrupt flag
   */
  else
  {
    I2C_CleanupTxRx(handle);
    /* Start up again */
    I2C_try_tx_from_isr(I2C0, handle, task_woken);
    I2C_ErrorAbort(I2C0);
  }
}




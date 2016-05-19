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

/* EFM32 EMLIB Includes */
#include "em_i2c.h"
#include "em_gpio.h"

/* FreeRTOS Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Other Driver Includes */
#include "sharedtypes.h"
#include "i2c.h"


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


/*******************************************************************************
 *******************************  FUNCTIONS  ***********************************
 ******************************************************************************/


/**************************************************************************//**
 * @brief  Setup I2C
 *
 * @param handle Which I2C bus (if more than one exists)
 * @param mode I2C device mode. Must be either I2C_MASTER or I2C_SLAVE
 * @param addr Own slave address
 * @param speed Bus speed in kbps
 *
 *****************************************************************************/
void I2C_init(int handle, int mode, uint8_t addr, uint16_t speed,
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

  /* Send the start/stop/restart condition */
  device[handle].mode = DEVICE_MODE_M_T;
  pca9665_write_reg(&(i2c0->CMD), flags);

}


/*****************************************************************************
 * @brief  Aborts the current transfer and sets the error flag
 *****************************************************************************/
void I2C_ErrorAbort(void)
{
  I2C0->CMD = I2C_CMD_ABORT;
  transferActive = false;
  i2cError = true;  
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

  /* Save the interrupt flag register status */
  uint32_t flags = I2C0->IF;
  
  /* Check for error flags from I2C peripheral */
  /* TODO: Error handling might conflict with GomSpace hardware */
  if ( flags & (I2C_IF_ARBLOST | I2C_IF_BUSERR | I2C_IF_CLTO) )
  {
    I2C0->IFC = flags;
    i2cErrorAbort();
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

      if (device[handle].tx.frame == NULL)
      {
        I2C_try_tx_from_isr(I2C0, handle, task_woken);
        /* TODO: Possibly should add i2cErrorAbort here */
      }
    }
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


/*
 * i2c.c
 *
 *  Created on: Apr 2, 2015
 *      Author: sdamkjar
 */

#include <stdbool.h>
#include <sharedtypes.h>

#include "i2c.h"

#include "FreeRTOS.h"
#include "queue.h"

#include "em_i2c.h"
#include "em_gpio.h"

uint8_t i2c_Buffer[I2C_MAX_QUEUE_SIZE] = {0};
uint8_t i2c_BufferIndex;

xQueueHandle xQueueI2C_RX;
xQueueHandle xQueueI2C_TX;

/**************************************************************************//**
 * @brief  Setup I2C
 *****************************************************************************/
void setupI2C(void)
{
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  xQueueI2C_RX = xQueueCreate( I2C_MAX_QUEUE_SIZE, sizeof( uint8_t ));
  xQueueI2C_TX = xQueueCreate( I2C_MAX_QUEUE_SIZE, sizeof( uint8_t ));

  /* Enable pins at location 1 */
  I2C0->ROUTE = I2C_ROUTE_SDAPEN |
                I2C_ROUTE_SCLPEN |
                (1 << _I2C_ROUTE_LOCATION_SHIFT);

  /* Initializing the I2C */
  I2C_Init(I2C0, &i2cInit);

  /* Setting up to enable slave mode */
  I2C0->SADDR |= I2C_ADDRESS << _I2C_SADDR_ADDR_SHIFT;
  I2C0->CTRL  |= I2C_CTRL_SLAVE | I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;

  I2C0->IFC = ~0;
  I2C0->IEN = I2C_IEN_ADDR | I2C_IEN_SSTOP;
  NVIC_EnableIRQ(I2C0_IRQn);
}

/**************************************************************************//**
 * @brief  Write data to the I2C transmit buffer (will be pending transmit)
 * @param  size Bytes to write to I2C
 * @param  point to read data from
 * @return Return error if buffer is full
 *****************************************************************************/
status_t writeI2C(void* ptr, uint8_t size)
{

  portBASE_TYPE xStatus;

  xStatus = xQueueSendToBack( xQueueI2C_TX, (uint8_t*)ptr, I2C_TX_WAIT/portTICK_RATE_MS );

  if ( pdPASS == xStatus ) return MEMS_SUCCESS;

  else return MEMS_ERROR;

}

/**************************************************************************//**
 * @brief  Read pull from the I2C recieve buffer
 * @param  size Bytes to read from I2C
 * @param  point to write data to
 * @return Return error if buffer is empty
 *****************************************************************************/
status_t readI2C(void* ptr, uint8_t size)
{

  portBASE_TYPE xStatus;

  uint8_t cursor = 0;

  for ( cursor = 0 ; cursor < size ; cursor++ ) {

    xStatus = xQueueReceive( xQueueI2C_RX, (uint8_t*)ptr, 0 );

    if ( pdPASS != xStatus ) return MEMS_ERROR;

  }

  return MEMS_SUCCESS;

}

/**************************************************************************//**
 * @brief I2C Interrupt Handler.
 *        The interrupt table is in assembly startup file startup_efm32.s
 *****************************************************************************/
void I2C0_IRQHandler(void)
{
  int status;
  status = I2C0->IF;

  uint8_t buffer = 0;

  if (status & I2C_IF_ADDR)
  {
    /* Address Match */
    I2C_IntClear(I2C0, I2C_IFC_ADDR);
    if (I2C0->RXDATA & 0x01)
    {

      if ( pdTRUE != xQueueReceive(xQueueI2C_TX, &buffer, 0))
    	  buffer = 0;

      /* Master read, enable slave Tx */
      I2C0->IEN |= I2C_IEN_ACK;
      I2C0->TXDATA = buffer;
    }
    else
    {
      /* Master write, enable slave Rx */
      I2C0->IEN |= I2C_IEN_RXDATAV;
    }
  }
  else if (status & I2C_IF_RXDATAV)
  {
    /* Data received */
	  buffer = I2C0->RXDATA;
	  xQueueSendToBack(xQueueI2C_RX, &buffer, 0);
  }
  else if (status & I2C_IF_ACK)
  {

	if ( pdTRUE != xQueueReceive(xQueueI2C_TX, &buffer, 0))
	    buffer = 0;

    /* ACK received, send next data */
    I2C_IntClear(I2C0, I2C_IFC_ACK);
    I2C0->TXDATA = buffer;
  }
  else
  {
    /* Stop received, Tx/Rx is ended */
    I2C_IntClear(I2C0, I2C_IFC_SSTOP);
    I2C0->IEN &= ~(I2C_IEN_ACK + I2C_IEN_RXDATAV);
  }
}

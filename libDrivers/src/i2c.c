/*
 * i2c.c
 *
 *  Created on: Apr 2, 2015
 *      Author: sdamkjar
 */

#include <stdbool.h>
#include "i2c.h"
#include "em_i2c.h"
#include "em_gpio.h"

uint8_t TxBuffer[I2C_MAX_TX_BUFFER_SIZE];
uint16_t TxBufferSize = sizeof(TxBuffer);
uint16_t TxBufferHead = 0;
uint16_t TxBufferTail = 0;

uint8_t RxBuffer[I2C_MAX_RX_BUFFER_SIZE];
uint16_t RxBufferSize = 0;
uint16_t RxBufferHead = 0;
uint16_t RxBufferTail = 0;

/**************************************************************************//**
 * @brief  Setup I2C
 *****************************************************************************/
void setupI2C(void)
{
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;


  /* Enable pins at location 1 */
  I2C0->ROUTE = I2C_ROUTE_SDAPEN |
                I2C_ROUTE_SCLPEN |
                (1 << _I2C_ROUTE_LOCATION_SHIFT);

  /* Initializing the I2C */
  I2C_Init(I2C0, &i2cInit);

  /* Setting up to enable slave mode */
  I2C0->SADDR = I2C_ADDRESS << _I2C_SADDR_ADDR_SHIFT;
  I2C0->CTRL |= I2C_CTRL_SLAVE | I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;

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
	int cursor = 0;

	if ( TxBufferSize - size >= 0 ) {

		TxBufferSize -= size;

		for ( cursor = 0 ; cursor < size ; cursor++ ) {
			TxBuffer[TxBufferHead++] = *(uint8_t*)ptr++;
			TxBufferHead %= I2C_MAX_TX_BUFFER_SIZE;
		}

		return MEMS_SUCCESS;
	}

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
	int cursor           =    0;
	uint8_t* cursor_ptr  =    (uint8_t*)ptr;

	if ( RxBufferSize - size >= 0 ) {

		RxBufferSize -= size;

		for ( cursor = 0 ; cursor < size ; cursor++, cursor_ptr++ ) {
			*cursor_ptr = (uint8_t)RxBuffer[RxBufferTail];
			RxBuffer[RxBufferTail++] = '\0';
			RxBufferHead %= I2C_MAX_RX_BUFFER_SIZE;
		}

		return MEMS_SUCCESS;
	}

	else return MEMS_ERROR;
}

/**************************************************************************//**
 * @brief I2C Interrupt Handler.
 *        The interrupt table is in assembly startup file startup_efm32.s
 *****************************************************************************/
void I2C0_IRQHandler(void)
{
  int status;
  status = I2C0->IF;

  TxBufferTail %= I2C_MAX_TX_BUFFER_SIZE;
  RxBufferHead %= I2C_MAX_RX_BUFFER_SIZE;

  if (status & I2C_IF_ADDR)
  {
    /* Address Match */
    I2C_IntClear(I2C0, I2C_IFC_ADDR);
    if (I2C0->RXDATA & 0x01)
    {
      /* Master read, enable slave Tx */
      I2C0->IEN |= I2C_IEN_ACK;
      I2C0->TXDATA = TxBuffer[TxBufferTail];
      TxBuffer[TxBufferTail++] = '\0';
      TxBufferSize++;
    }
    else
    {
      /* Master write, enable slave Rx */
      I2C0->IEN |= I2C_IEN_RXDATAV;
    }
  }
  else if (status & I2C_IF_RXDATAV && RxBufferSize < I2C_MAX_RX_BUFFER_SIZE)
  {
    /* Data received */
    RxBuffer[RxBufferHead++] = I2C0->RXDATA;
    RxBufferSize++;
  }
  else if (status & I2C_IF_ACK)
  {
    /* ACK received, send next data */
    I2C_IntClear(I2C0, I2C_IFC_ACK);
    I2C0->TXDATA = TxBuffer[TxBufferTail];
    TxBuffer[TxBufferTail++] = '\0';
    TxBufferSize++;
  }
  else
  {
    /* Stop received, Tx/Rx is ended */
    I2C_IntClear(I2C0, I2C_IFC_SSTOP);
    I2C0->IEN &= ~(I2C_IEN_ACK + I2C_IEN_RXDATAV);
  }
}

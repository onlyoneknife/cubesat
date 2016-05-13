/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"


/**************************************************************************//**
 * @brief Transmit single byte to BOOTLOADER_USART
 *****************************************************************************/
uint8_t USART_rxByte(void)
{
  uint32_t timer = 1000000;
  while (!(USART1->STATUS & USART_STATUS_RXDATAV) && --timer ) ;
  if (timer > 0)
  {
    return((uint8_t)(USART1->RXDATA & 0xFF));
  }
  else
  {
    return 0;
  }
}


/**************************************************************************//**
 * @brief Transmit single byte to BOOTLOADER_USART
 *****************************************************************************/
void USART_txByte(uint8_t data)
{
  /* Check that transmit buffer is empty */
  while (!(USART1->STATUS & USART_STATUS_TXBL)) ;

  USART1->TXDATA = (uint32_t) data;
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  enter_DefaultMode_from_RESET();

  /* Infinite loop */
  while (1) {

	  USART_txByte(0xEE);

  }
}

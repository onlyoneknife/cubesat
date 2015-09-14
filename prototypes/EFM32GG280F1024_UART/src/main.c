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


/* System Includes */
#include <stdio.h>
#include <stdint.h>

/* EFM32 Includes */
#include "InitDevice.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_usart.h"

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Initialize EFM32 Chip Settings */
  CHIP_Init();

  /* Transition to Default Mode */
  enter_DefaultMode_from_RESET();

  /* Infinite loop */
  while (1) {

	  while (!(USART0->STATUS & USART_STATUS_TXBL))
	      ;
	  USART0->TXDATA = 'x';

	  while (!(USART1->STATUS & USART_STATUS_RXDATAV))
	    ;
	  int result = USART1->RXDATA;

  }
}

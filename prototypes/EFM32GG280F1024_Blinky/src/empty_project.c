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
#define TIME_COUNTER 1000

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  /* ENTER YOUR CODE HERE */
  /* ENABLE TIMER0 in HFPERCLKEN0 register in CMU peripheral */
  CMU -> HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;
  /* START THE TIMER0 */
  TIMER0 -> CMD |= TIMER_CMD_START;

  while(TIMER0 -> CNT < 1000){
  /* Do nothing, just wait */
  }

  /* Infinite loop */
  while (1) {
  }
}

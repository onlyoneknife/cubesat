/**************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for EFM32GG_STK3700
 * @version 3.20.12
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"

#define LED_PORT                   (gpioPortE)
#define LED_PIN                    (2)

volatile uint32_t msTicks; /* counts 1ms timeTicks */

/******************************************************************************
 * @brief Delay function
 *****************************************************************************/
void Delay(uint16_t milliseconds)
{
  /* Enable clock for TIMER0 */
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;

  /* Set prescaler to maximum */
  TIMER0->CTRL = (TIMER0->CTRL & ~_TIMER_CTRL_PRESC_MASK) |  TIMER_CTRL_PRESC_DIV1024;

  /* Clear TIMER0 counter value */
  TIMER0->CNT = 0;

  /* Start TIMER0 */
  TIMER0->CMD = TIMER_CMD_START;

  /* Wait until counter value is over the threshold */
  while(TIMER0->CNT < 13*milliseconds){
   /* Do nothing, just wait */
  }

  /* Stop TIMER0 */
  TIMER0->CMD = TIMER_CMD_STOP;
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
  CMU_ClockEnable(cmuClock_GPIO, true);

  GPIO_PinModeSet(gpioPortE,2,gpioModePushPull,1);

  while (1) {

	  GPIO->P[LED_PORT].DOUTSET = 1 << LED_PIN;

	  Delay(100);

	  GPIO->P[LED_PORT].DOUTCLR = 1 << LED_PIN;

	  Delay(100);

  }

}

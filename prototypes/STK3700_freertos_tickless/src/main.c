/**************************************************************************//**
 * @file
 * @brief FreeRTOS Tickless Demo for Energy Micro EFM32GG_STK3700 Starter Kit
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

/* System Includes */

#include <stdio.h>
#include <stdlib.h>

/* FreeRTOS Includes */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

/* EFM32 Includes */
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include "sleep.h"

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 10)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)
#define DELAY                  ( 100 / portTICK_RATE_MS )

#define LED_PORT    gpioPortA
#define LED_PIN     7

/**************************************************************************//**

 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 *****************************************************************************/
static void LedBlink(void *pParameters)
{
  pParameters = pParameters;

  for (;;)
  {
		GPIO_PortOutSetVal(LED_PORT, 1<<LED_PIN, 1<<LED_PIN);
	    vTaskDelay(DELAY);
	    GPIO_PortOutSetVal(LED_PORT, 0<<LED_PIN, 1<<LED_PIN);
	    vTaskDelay(DELAY);
  }
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  /* Enable clock for GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
  GPIO_PinModeSet(LED_PORT,         /* Port */
                  LED_PIN,          /* Pin */
                  gpioModePushPull, /* Mode */
                  0 );              /* Output value */

  /* Initialize SLEEP driver, no calbacks are used */
  SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
  /* do not let to sleep deeper than define */
  SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif

  /*Create two task for blinking leds*/
  xTaskCreate( LedBlink, (const char *) "LedBlink", STACK_SIZE_FOR_TASK,  NULL, TASK_PRIORITY, NULL);

  /* Start FreeRTOS Scheduler */
  vTaskStartScheduler();

  return 0;
}

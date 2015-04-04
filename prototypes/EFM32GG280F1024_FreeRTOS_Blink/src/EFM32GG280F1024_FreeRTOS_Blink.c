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
#include <stdio.h>
#include <stdlib.h>

#include "sleep.h"
#include "autogen_init.h"

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 10)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)

#define LED_PORT    gpioPortA
#define LED_PIN     7

void LED_Init(void)
{
	/* Enable clock for GPIO */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
	GPIO_PinModeSet(LED_PORT,         /* Port */
	                LED_PIN,          /* Pin */
	                gpioModePushPull, /* Mode */
	                0 );              /* Output value */
}


/* Structure with parameters for LedBlink */
typedef struct
{
  /* Delay between blink of led */
  portTickType delay;
  /* Number of led */
  int          toggle;
} TaskParams_t;

/**************************************************************************//**
 * @brief Simple task which is blinking led
 * @param *pParameters pointer to parameters passed to the function
 *****************************************************************************/
static void LedBlink(void *pParameters)
{
  TaskParams_t     * pData = (TaskParams_t*) pParameters;
  const portTickType delay = pData->delay;

  for (;;)
  {
    /* Set LSB of count value on LED */
    GPIO_PortOutSetVal(LED_PORT, pData->toggle<<LED_PIN, 1<<LED_PIN);
    vTaskDelay(delay);
  }
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{

	/* Chip errata */
	CHIP_Init();

    /* Initialize SLEEP driver, no calbacks are used */
    SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
    /* do not let to sleep deeper than define */
  	SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif

  	/* Initialize chip */
  	eADesigner_Init();

    LED_Init();

    /* Parameters value for taks*/
    static TaskParams_t parametersToTask1 = { 1000 / portTICK_RATE_MS, 0 };
    static TaskParams_t parametersToTask2 = {  500 / portTICK_RATE_MS, 1 };

    /*Create two task for blinking leds*/
    xTaskCreate( LedBlink, (const signed char *) "LedBlink1", STACK_SIZE_FOR_TASK, &parametersToTask1, TASK_PRIORITY, NULL);
    xTaskCreate( LedBlink, (const signed char *) "LedBlink2", STACK_SIZE_FOR_TASK, &parametersToTask2, TASK_PRIORITY, NULL);

    /*Start FreeRTOS Scheduler*/
    vTaskStartScheduler();

    return 0;
}


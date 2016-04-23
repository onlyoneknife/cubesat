/*
 * Copyright (C) 2015  Brandon Borden, Stefan Damkjar, Taeho Kang, and Peng Zhang
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
 */

/**
 * @file main.c
 * @author Brandon Borden, Stefan Damkjar
 * @date 2015-02-20
 */

/* System Includes */
#include <stdio.h>
#include <stdint.h>

/* EFM32 EMLIB Includes */
#include "InitDevice.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"

/* EFM32 Driver Includes */
#include "sleep.h"


/* Other Driver Includes */
#include "sharedtypes.h"


/* FreeRTOS Includes */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#define LEDBLINK_STACK_SIZE        (configMINIMAL_STACK_SIZE + 10)
#define LEDBLINK_TASK_PRIORITY     (tskIDLE_PRIORITY + 1)

#define LED_DELAY                  (100 / portTICK_RATE_MS)
#define LED_PORT                   (gpioPortC)
#define LED_PIN                    (2U)

/* Ram buffers
 * BUFFERSIZE should be between 512 and 1024, depending on available ram *****/
#define BUFFERSIZE      1024

char   receiveBuffer[BUFFERSIZE];

/***************************************************************************//**
 * @brief
 *   This function is required by the FAT file system in order to provide
 *   timestamps for created files. Since this example does not include a
 *   reliable clock we hardcode a value here.
 *
 *   Refer to drivers/fatfs/doc/en/fattime.html for the format of this DWORD.
 * @return
 *    A DWORD containing the current time and date as a packed datastructure.
 ******************************************************************************/


/**************************************************************************//**
 * @brief Simple task which is blinking led
 *****************************************************************************/



/**************************************************************************//**
 * @brief Simple task which is blinking led
 *****************************************************************************/
static void LedBlink(void *pParameters)
{

  pParameters = pParameters;   /* to quiet warnings */

  for (;;)
  {
    /* Set LSB of count value on LED */
  GPIO->P[LED_PORT].DOUTSET = 1 << LED_PIN;
    vTaskDelay(LED_DELAY);
    GPIO->P[LED_PORT].DOUTCLR = 1 << LED_PIN;
    vTaskDelay(LED_DELAY);
  }
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Initialize EFM32 Chip Settings */
  CHIP_Init();

  /* Transition to Default Mode */
  enter_DefaultMode_from_RESET();



  /* Create task for blinking leds */
  xTaskCreate( LedBlink,
           (const char *) "LedBlink",
           LEDBLINK_STACK_SIZE,
           NULL,
           LEDBLINK_TASK_PRIORITY,
           NULL );


  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  /* Infinite loop */
  for( ;; ) { /* do nothing */ }

}

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

/* EFM32 Includes */
#include "InitDevice.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"

/* Driver Includes */
#include "sharedtypes.h"
#include "gyro.h"
#include "rtc.h"
#include "fram.h"
#include "mag.h"
#include "i2c.h"
#include "tempsense.h"
#include "spi.h"
#include "sleep.h"

/* FreeRTOS Includes */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#define LEDBLINK_STACK_SIZE        (configMINIMAL_STACK_SIZE + 10)
#define LEDBLINK_TASK_PRIORITY     (tskIDLE_PRIORITY + 1)

#define SPI2RECEIVE_STACK_SIZE     (configMINIMAL_STACK_SIZE + 100)
#define SPI2RECEIVE_TASK_PRIORITY  (tskIDLE_PRIORITY + 1)

#define LED_DELAY                  (50 / portTICK_RATE_MS)
#define LED_PORT    		       (gpioPortA)
#define LED_PIN     		       (7)

#define BUFFERSIZE                 (5)

char    receiveBuffer[BUFFERSIZE];



/**************************************************************************//**
 * @brief Initialize drivers
 *****************************************************************************/
void DRIVERS_Init(void)
{

	/* Enable I2C0 is slave mode */
	I2C0_setup();

	/* Enable USART2 in SPI slave mode */
	SPI_setup(2, 1, 0);

}



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
 * @brief Simple task which is receiving as a slave on USART2
 *****************************************************************************/
static void SPI2Receive(void *pParameters)
{

  pParameters = pParameters;   /* to quiet warnings */

  for (;;)
  {
	/* Data reception as slave */
	/* *********************** */
	/*Setting up both RX and TX interrupts for slave */
	SPI2_setupSlaveInt(receiveBuffer, BUFFERSIZE, NO_TX, NO_TX);
	vTaskDelay(50 / portTICK_RATE_MS);
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

  /* Initialize Hardware Drivers */
  DRIVERS_Init();

  /* Create task for blinking leds */
  xTaskCreate( LedBlink,
		       (const char *) "LedBlink",
		       LEDBLINK_STACK_SIZE,
		       NULL,
		       LEDBLINK_TASK_PRIORITY,
		       NULL );

  /* Create task for receiving on USART2 */
   xTaskCreate( SPI2Receive,
 		       (const char *) "SPI2Receive",
 		       SPI2RECEIVE_STACK_SIZE,
 		       NULL,
 		       SPI2RECEIVE_TASK_PRIORITY,
 		       NULL );

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  /* Infinite loop */
  for( ;; ) { /* do nothing */ }

}

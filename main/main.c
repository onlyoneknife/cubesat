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
 * @author Brandon Borden
 * @date 2015-02-20
 */

/* System Includes */
#include <stdio.h>
#include <stdint.h>
#include <autogen_init.h>

/* Driver Includes */
#include "gyro.h"
#include "i2c.h"
#include "tempsense.h"
#include "sleep.h"

/* EFM32 Includes */
#include "em_chip.h"
#include "em_gpio.h"

/* FreeRTOS Includes */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 100)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)
#define LED_DELAY              ( 100 / portTICK_RATE_MS )

#define LED_PORT    gpioPortA
#define LED_PIN     7

uint8_t response;

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

int main(void)
{
  /* Initialize chip */
  eADesigner_Init();
  CHIP_Init();

  /* Initialize drivers */
  ADCConfig();
  setupI2C();
  // Set all SPI CS to default high
  GPIO->P[GYRO_CS_PORT].DOUTSET = 1 << GYRO_CS_PIN;
  GPIO->P[gpioPortD].DOUTSET = 1 << 3;
  GPIO->P[gpioPortF].DOUTSET = 1 << 6;
  GPIO->P[gpioPortB].DOUTSET = 1 << 12;
  /* Initialize SLEEP driver, no calbacks are used */
  SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
  /* do not let to sleep deeper than define */
  SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif

  /* Initialize buffers and variables */
  uint8_t buffer[50];
  uint8_t value;
  uint32_t result = 0;

  /*Create task for blinking leds*/
  xTaskCreate( LedBlink, (const signed char *) "LedBlink", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();
  /*
  int len = 0;
  uint8_t position=0, old_position=0;
  AxesRaw_t data;


  //set PowerMode
  //response = GYRO_SetMode(GYRO_NORMAL);
  //set Fullscale
  //response = GYRO_SetFullScale(GYRO_FULLSCALE_250);
  //set axis Enable
  //response = GYRO_SetAxis(GYRO_X_ENABLE | GYRO_Y_ENABLE | GYRO_Z_ENABLE);
  // Check ID - Should be 11010111b, D7h
  //response = GYRO_ReadReg(GYRO_I_AM_L3GD20H, &value);


  while(1){
	  //get Acceleration Raw data
	  //GYRO_GetAngRateRaw(&data);

	  __WFI();
	  I2C_READ(result,sizeof(result));

	  //response = GYRO_ReadReg(GYRO_I_AM_L3GD20H, &value);

	  //len = sprintf((char*)buffer, "X=%6d Y=%6d Z=%6d \r\n", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
	  //old_position = position;
	 // I2C_WRITE(data.AXIS_X);
	 //

  }
  */

  return 0;

}

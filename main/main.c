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
#include "rtc.h"
#include "fram.h"
#include "mag.h"
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

#define LED_DELAY              (50 / portTICK_RATE_MS)
#define LED_PORT    		   (gpioPortA)
#define LED_PIN     		   (7)

/**************************************************************************//**
 * @brief Initialize drivers
 *****************************************************************************/
void DRIVERS_Init(void)
{
  /* Initialize SPI Chip Select Pins */
  // Set all SPI CS to default high
  // TODO Fix PCB to have pull-ups so this is not needed
  GPIO->P[GYRO_CS_PORT].DOUTSET = 1 << GYRO_CS_PIN;
  GPIO->P[FRAM_CS_PORT].DOUTSET = 1 << FRAM_CS_PIN;
  GPIO->P[MAG_CS_PORT].DOUTSET  = 1 << MAG_CS_PIN;
  GPIO->P[RTC_CS_PORT].DOUTSET  = 1 << RTC_CS_PIN;

  /* Initialize ADC */
  ADCConfig();

  /* Initialize I2C */
  setupI2C();

  /* Initialize SLEEP driver, no call-backs are used */
  SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
  /* do not let to sleep deeper than define */
  SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif

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

static void GyroRead(void *pParameters)
{

  xSemaphoreHandle* semSPI = (xSemaphoreHandle*) pParameters;

  uint8_t  xlow  = 0;
  uint8_t  xhigh = 0;
  int16_t  value = 0x0000;
  uint8_t  size  = 0;
  char buffer[11];

  /* set PowerMode */
  if ( GYRO_SetMode(GYRO_NORMAL) == MEMS_ERROR )
  {
	I2C_WRITE("Gyro init error!\n");
  }

  if ( GYRO_SetHPFCutOFF == MEMS_ERROR )
  {
	I2C_WRITE("Gyro init error!\n");
  }

  for (;;)
  {
    vTaskDelay(GYRO_READ_DELAY / portTICK_RATE_MS);

    //if (pdTRUE == xSemaphoreTake(*semSPI, portMAX_DELAY)) {

      //GYRO_ReadReg(GYRO_I_AM_L3GD20H, &value);

      GYRO_ReadReg(GYRO_OUT_X_L, &xlow);

      GYRO_ReadReg(GYRO_OUT_X_H, &xhigh);

      GYRO_SetHPFCutOFF(1);

      value = (xhigh << 8) + xlow;

      size = sprintf(buffer,"X = %hd\n",value);

      writeI2C(&buffer,size);

    //}

    //xSemaphoreGive(*semSPI);
  }
}

int main(void)
{
  /* Initialize EFM32 Chip Settings */
  eADesigner_Init();
  CHIP_Init();

  /* Initialize Hardware Drivers */
  DRIVERS_Init();

  /* Create binary semaphore for SPI */
  xSemaphoreHandle       semSPI;
  vSemaphoreCreateBinary(semSPI);

  /* Create task for blinking leds */
  xTaskCreate( LedBlink, (const char *) "LedBlink", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /* Create task for interaction with gyro */
  xTaskCreate( GyroRead, (const char *) "GyroRead", STACK_SIZE_FOR_TASK, &semSPI, TASK_PRIORITY, NULL);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;

}

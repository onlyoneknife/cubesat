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
#include "gpiointerrupt.h"

/* FreeRTOS Includes */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

#define STACK_SIZE_FOR_TASK    (configMINIMAL_STACK_SIZE + 1000)
#define TASK_PRIORITY          (tskIDLE_PRIORITY + 1)

#define LED_DELAY              (50 / portTICK_RATE_MS)
#define LED_PORT    		   (gpioPortA)
#define LED_PIN     		   (7)

/* Create mutex semaphore for SPI1 */
xSemaphoreHandle   xSemaphoreSPI;

/* Create */
xQueueHandle       xQueueMag;
xQueueHandle       xQueueGyro;

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

  /* Initialize mutex semaphore for SPI1 */
  xSemaphoreSPI = xSemaphoreCreateMutex();

  xQueueMag  = xQueueCreate( 10, sizeof( uint8_t ));
  xQueueGyro = xQueueCreate( 10, sizeof( uint8_t ));

  /* Initialize SLEEP driver, no call-backs are used */
  SLEEP_Init(NULL, NULL);
#if (configSLEEP_MODE < 3)
  /* do not let to sleep deeper than define */
  SLEEP_SleepBlockBegin((SLEEP_EnergyMode_t)(configSLEEP_MODE+1));
#endif
}

/**************************************************************************//**
 * @brief  Gpio callback
 * @param  pin - pin which triggered interrupt
 *****************************************************************************//*
void gpioCallback(uint8_t pin)
{
  if (pin == 11)
  {
	  GPIO->P[LED_PORT].DOUTSET = 1 << LED_PIN;
  }
  else GPIO->P[LED_PORT].DOUTCLR = 1 << LED_PIN;
}*/

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
 * @brief Task to control Gyro sampling
 *****************************************************************************/
static void GyroRead(void *pParameters)
{

  pParameters = pParameters;   /* to quiet warnings */

  uint8_t ucReceivedValue = 0;
  uint8_t ucTransmitValue = 0;

  uint8_t ucWhoAmI        = 0;

  /* set PowerMode *//*
  if ( GYRO_SetMode(GYRO_NORMAL) == MEMS_ERROR )
	I2C_WRITE("Gyro CTRL1 init error!\n");

  if ( GYRO_SetHPFCutOFF(8) == MEMS_ERROR )
	I2C_WRITE("Gyro HPF init error!\n");

  if ( GYRO_SetBLE(0) == MEMS_ERROR )
	I2C_WRITE("Gyro BLE init error!\n");

  if ( GYRO_SetSelfTest(1) == MEMS_ERROR )
	I2C_WRITE("Gyro BLE init error!\n");

  if ( GYRO_SetInt2Pin(GYRO_I2_DRDY_ON_INT2_ENABLE) == MEMS_ERROR )
	I2C_WRITE("Gyro INT2 init error!\n");

  /* Gyro sampling SPI transactions */ /*
  GYRO_ReadReg(GYRO_I_AM_L3GD20H, &ucWhoAmI);
  if ( ucWhoAmI != GYRO_WHOIAM_VALUE )
	I2C_WRITE("Gyro READ error!\n"); */

  for (;;)
  {

    vTaskDelay(GYRO_READ_DELAY / portTICK_RATE_MS);

    if ( pdPASS == xQueueReceive( xQueueGyro, &ucReceivedValue, portMAX_DELAY ) )
    {
      if (pdTRUE == xSemaphoreTake(xSemaphoreSPI, portMAX_DELAY)) {

        GYRO_ReadReg(ucReceivedValue, &ucTransmitValue);

	    writeI2C(&ucTransmitValue,1);

	    xSemaphoreGive(xSemaphoreSPI);
      }
    }
  }
}

/**************************************************************************//**
 * @brief Task to control Mag sampling
 *****************************************************************************/
static void MagRead(void *pParameters)
{

  pParameters = pParameters;   /* to quiet warnings */

  uint8_t ucReceivedValue = 0;
  uint8_t ucValueToSend   = 0;

  uint8_t ucWhoAmI        = 0;

  /* Mag sampling SPI transactions *//*
  MAG_ReadReg(REG_WHOAMI_ADDR, &ucWhoAmI);
  if ( ucWhoAmI != WHOIAM_VALUE )
	I2C_WRITE("Mag READ error!\n");

  if ( MAG_SetODR_M(ODR_100Hz_M) == MEMS_ERROR )
    I2C_WRITE("Mag ODR_M init error!\n");

  if ( MAG_SetFullScale(FULLSCALE_2) == MEMS_ERROR )
    I2C_WRITE("Mag FSCALE init error!\n");

  if ( MAG_SetModeMag(CONTINUOUS_MODE) == MEMS_ERROR )
    I2C_WRITE("Mag CTRL7 init error!\n");*/

  for (;;)
  {
    vTaskDelay(MAG_READ_DELAY / portTICK_RATE_MS);

    if ( pdPASS == xQueueReceive( xQueueMag, &ucReceivedValue, portMAX_DELAY ) )
    {
	  if ( pdTRUE == xSemaphoreTake(xSemaphoreSPI, portMAX_DELAY )) {

	    MAG_ReadReg(ucReceivedValue, &ucValueToSend);

	    I2C_WRITE(ucValueToSend);

	    xSemaphoreGive(xSemaphoreSPI);
	  }
    }
  }
}

static void I2CReceive(void *pParameters)
{

  pParameters = pParameters;   /* to quiet warnings */

  uint8_t ucDeviceID = 0;
  uint8_t ucRegister = 0;

  for (;;)
  {

    ucDeviceID = 0;
    ucRegister = 0;

    I2C_READ(ucDeviceID);

	switch(ucDeviceID) {
	case 0:
	break;
	case 'M':
	  I2C_READ(ucRegister);
	  xQueueSendToBack( xQueueMag, &ucRegister, 0 );
	break;
	case 'G':
	  I2C_READ(ucRegister);
	  xQueueSendToBack( xQueueGyro, &ucRegister, 0 );
	break;
	ucRegister = 0;
    }
  }
}

int main(void)
{
  /* Initialize EFM32 Chip Settings */

  eADesigner_Init();
  CHIP_Init();

  /* Initialize Hardware Drivers */
  DRIVERS_Init();

  /* Initialize GPIO interrupt dispatcher */
  //GPIOINT_Init();

  /* Register callbacks before setting up and enabling pin interrupt. */
  //GPIOINT_CallbackRegister(0, gpioCallback);

  /* Set falling edge interrupt for both ports */
  //GPIO_IntConfig(gpioPortC, 11, false, true, true);



  /* Create task for blinking leds */
  xTaskCreate( LedBlink, (const char *) "LedBlink", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /* Create task for interaction with gyro */
  xTaskCreate( GyroRead, (const char *) "GyroRead", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /* Create task for interaction with mag */
  xTaskCreate( MagRead, (const char *) "MagRead", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /* Create task for processing I2C commands */
  xTaskCreate( I2CReceive, (const char *) "I2CReceive", STACK_SIZE_FOR_TASK, NULL, TASK_PRIORITY, NULL);

  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  return 0;

}

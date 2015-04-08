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

#define LED_DELAY              (10 / portTICK_RATE_MS)
#define LED_PORT    		   (gpioPortA)
#define LED_PIN     		   (7)

uint8_t

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

  MAG_SetODR_M(ODR_100Hz_M);

  MAG_SetFullScale(FULLSCALE_2);

  MAG_SetModeMag(CONTINUOUS_MODE);

  /* set PowerMode */
  GYRO_SetMode(GYRO_NORMAL);

  GYRO_SetHPFCutOFF(8);

  GYRO_SetBLE(0);

  GYRO_SetSelfTest(1);

  /* Initialize ADC */
  ADCConfig();

  /* Initialize I2C */
  setupI2C();

}

int main(void)
{
  /* Initialize EFM32 Chip Settings */
  eADesigner_Init();
  CHIP_Init();

  /* Initialize Hardware Drivers */
  DRIVERS_Init();


  uint8_t ucDeviceID      = 0;
  uint8_t ucRegister      = 0;
  uint8_t ucValueToSend   = 0;

  for( ;; ){

	    __WFI();

		if( readI2C(&ucDeviceID) ) {

			switch(ucDeviceID) {
			case 'G':
				readI2C(&ucRegister);
				GYRO_ReadReg(ucRegister, &ucValueToSend);
				writeI2C(&ucValueToSend);
				__WFI();
			break;
			case 'M':
				readI2C(&ucRegister);
				MAG_ReadReg(ucRegister, &ucValueToSend);
				writeI2C(ucValueToSend);
				__WFI();
			break;
			}
		}
  }


  return 0;

}

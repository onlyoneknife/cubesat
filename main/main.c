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

#include <stdio.h>
#include <stdint.h>
#include <autogen_init.h>

#include "gyro.h"
#include "tempsense.h"
#include "em_chip.h"
#include "em_gpio.h"

uint8_t response;

int main(void)
{
  /* Initialize chip */
  eADesigner_Init();

  /* Initialize chip */
  CHIP_Init();
  ADCConfig();

  GPIO->P[gpioPortD].DOUTSET = 1 << 3; // Set CS high
  GPIO->P[gpioPortF].DOUTSET = 1 << 6; // Set CS high
  GPIO->P[gpioPortB].DOUTSET = 1 << 12; // Set CS high

  //uint8_t value;
  //GYRO_ReadReg(GYRO_I_AM_L3GD20H, value);

  uint8_t buffer[50];
  uint8_t value;

  int len = 0;
  uint8_t position=0, old_position=0;
  AxesRaw_t data;

  /* Initialize Gyro */
  GYRO_Init();

  // Check ID - Should be 11010111, 0xD7
  response = GYRO_ReadReg(GYRO_I_AM_L3GD20H, &value);

  //set PowerMode
  response = GYRO_SetMode(GYRO_NORMAL);

  //set Fullscale
  response = GYRO_SetFullScale(GYRO_FULLSCALE_250);

  //set axis Enable
  response = GYRO_SetAxis(GYRO_X_ENABLE | GYRO_Y_ENABLE | GYRO_Z_ENABLE);

  /*********************/
  /******Example 1******/
  /*********************/

  while(1){
	  //get Acceleration Raw data
	  response = GYRO_ReadReg(GYRO_OUT_TEMP, &value);

	  response = GYRO_GetAngRateRaw(&data);
	  if(response==1){    //debug print axies value for MKI109V1 board
		  len = sprintf((char*)buffer, "X=%6d Y=%6d Z=%6d \r\n", data.AXIS_X, data.AXIS_Y, data.AXIS_Z);
		  old_position = position;
	  }
  }

}

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

#include "tempsense.h"

#include "em_chip.h"

int main(void)
{
  /* Initialize chip */
  eADesigner_Init();

  /* Initialize chip */
  CHIP_Init();

  ADCConfig();

  uint32_t sample = 0;

  /* Infinite blink loop */
  while(1){

	  sample = ADC_GetData(ADC0);

  }

  /* Initialize other components */

  // Initialize Code Flash
  // Initialize SD Card
  // Initialize FRAM
  // Initialize Sensors
  // Initialize External I2C?

  return 0;

}

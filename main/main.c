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
#include "diskio.h"
#include "microsd.h"
#include "ff.h"
#include "sleep.h"
#include "i2c.h"
#include "spi.h"

/* Other Driver Includes */
#include "sharedtypes.h"
#include "gyro.h"
#include "rtc.h"
#include "fram.h"
#include "mag.h"
#include "tempsense.h"
#include "spi.h"

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

#define BUFFERSIZE                 (1024)

char    receiveBuffer[BUFFERSIZE];


#define USE_SD_CARD                (true)

#if USE_SD_CARD == true
/* Ram buffers
 * BUFFERSIZE should be between 512 and 1024, depending on available ram *****/
#define BUFFERSIZE      1024
/* Filename to open/write/read from SD-card */
#define TEST_FILENAME    "test.txt"

FIL fsrc;			            	/* File objects */
FATFS Fatfs;			        	/* File system specific */
FRESULT res;				        /* FatFs function common result code */
UINT br, bw;			        	/* File read/write count */
DSTATUS resCard;		            /* SDcard status */
int8_t ramBufferWrite[BUFFERSIZE];	/* Temporary buffer for write file */
int8_t ramBufferRead[BUFFERSIZE];	/* Temporary buffer for read file */
int8_t StringBuffer[] = "EFM32 ...the world's most energy friendly microcontrollers !";
int16_t i;
int16_t filecounter;

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
DWORD get_fattime(void)
{
  return (28 << 25) | (2 << 21) | (1 << 16);
}

#endif

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

  //pParameters = pParameters;   /* to quiet warnings */

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

  //pParameters = pParameters;   /* to quiet warnings */

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

  GPIO->P[LED_PORT].DOUTSET = 1 << LED_PIN;

#if USE_SD_CARD == true

  resCard = disk_initialize(0);       /*Check micro-SD card status */

  switch(resCard)
  {
  case STA_NOINIT:                    /* Drive not initialized */
    break;
  case STA_NODISK:                    /* No medium in the drive */
    break;
  case STA_PROTECT:                   /* Write protected */
    break;
  default:
    break;
  }

  /* Initialize filesystem */
  res = f_mount(0, &Fatfs);
  if (res != FR_OK)
  {
    /* Error.No micro-SD with FAT32 is present */
    while(1);
  }

  /*Step4*/
  /* Open  the file for write */
  res = f_open(&fsrc, TEST_FILENAME,  FA_WRITE);
  if (res != FR_OK)
  {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, TEST_FILENAME, FA_CREATE_ALWAYS | FA_WRITE );
    if (res != FR_OK)
    {
      /* Error. Cannot create the file */
      while(1);
    }
  }

  /*Step5*/
  /*Set the file write pointer to first location */
  res = f_lseek(&fsrc, 0);
  if (res != FR_OK)
  {
    /* Error. Cannot set the file write pointer */
    while(1);
  }

  /*Step6*/
  /*Write a buffer to file*/
  res = f_write(&fsrc, ramBufferWrite, filecounter, &bw);
  if ((res != FR_OK) || (filecounter != bw))
  {
    /* Error. Cannot write the file */
  while(1);
  }

  /*Step7*/
  /* Close the file */
  f_close(&fsrc);
  if (res != FR_OK)
  {
    /* Error. Cannot close the file */
    while(1);
  }

  /*Step8*/
  /* Open the file for read */
  res = f_open(&fsrc, TEST_FILENAME,  FA_READ);
  if (res != FR_OK)
  {
    /* Error. Cannot create the file */
    while(1);
  }

  /*Step9*/
  /*Set the file read pointer to first location */
  res = f_lseek(&fsrc, 0);
  if (res != FR_OK)
  {
    /* Error. Cannot set the file pointer */
    while(1);
  }

  /*Step10*/
  /* Read some data from file */
  res = f_read(&fsrc, ramBufferRead, filecounter, &br);
  if ((res != FR_OK) || (filecounter != br))
  {
    /* Error. Cannot read the file */
    while(1);
  }

  /*Step11*/
  /* Close the file */
  f_close(&fsrc);
  if (res != FR_OK)
  {
    /* Error. Cannot close the file */
    while(1);
  }

  /*Step12*/
  /*Compare ramBufferWrite and ramBufferRead */
  for(i = 0; i < filecounter ; i++)
  {
    if ((ramBufferWrite[i]) != (ramBufferRead[i]))
    {
      /* Error compare buffers*/
      while(1);
    }
  }

#endif

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

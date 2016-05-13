/*
 * Copyright (C) 2015  Stefan Damkjar, Zack Cooper-Black
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
 * @author Stefan Damkjar, Zack Cooper-Black
 * @date 2015-02-20
 */

/*******************************************************************************
 ******************************   INCLUDES   ***********************************
 ******************************************************************************/

/* System Includes */
#include <stdio.h>
#include <stdint.h>

/* EFM32 EMLIB Includes */
#include "InitDevice.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_adc.h"
#include "em_dma.h"

/* Driver Includes */
#include "sleep.h"
#include "LCD.h"
#include "dmactrl.h"

/* FreeRTOS Includes */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "croutine.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

 #define Max_Voltage 				(5)							// [V]
 #define Min_Voltage 				(4)							// [V]
 #define VOLTAGE_DELAY 				(100 / portTICK_RATE_MS)


 #define Max_Current 				(1000)						// [mA]
 #define Min_Current 				(500)						// [mA]
 #define CURRENT_DELAY 				(100 / portTICK_RATE_MS)


#define LEDBLINK_STACK_SIZE        	(configMINIMAL_STACK_SIZE + 10)
#define LEDBLINK_TASK_PRIORITY     	(tskIDLE_PRIORITY + 1)
#define LED_DELAY                  	(100 / portTICK_RATE_MS)

 #define ALARM_DELAY 				(100 / portTICK_RATE_MS)
 #define ALARM_TIME 				(100 / portTICK_RATE_MS)
 #define ALARM_ON 					(true)
 #define ALARM_OFF 					(false)

/** DMA channel used for scan sequence sampling adc channel 0, and 2. */
#define DMA_CHANNEL    0
#define NUM_SAMPLES    2
 
 #define Error_Check_STACK_SIZE (configMINIMAL_STACK_SIZE + 10)
 #define Error_Check_TASK_PRIORITY (tskIDLE_PRIORITY + 1)

char  message[12];




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


/*******************************************************************************
 ***************************   LOCAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
* @brief
*   Configure ADC for scan mode.
*******************************************************************************/
static void ADCConfig(int* errataShift)
{

	SYSTEM_ChipRevision_TypeDef chipRev;

	ADC_InitScan_TypeDef scanInit = ADC_INITSCAN_DEFAULT;

	/* ADC errata for rev B when using VDD as reference, need to multiply */
	/* result by 2 */
	SYSTEM_ChipRevisionGet(&chipRev);
	if ((chipRev.major == 1) && (chipRev.minor == 1))
	{
		*errataShift = 1;
	}
	else
	{
		*errataShift = 0;
	}

	/* Init for scan sequence use. */
	scanInit.reference = adcRefVDD;
	scanInit.input     = ADC_SCANCTRL_INPUTMASK_CH0 |
	                     ADC_SCANCTRL_INPUTMASK_CH2;
	ADC_InitScan(ADC0, &scanInit);

}

/***************************************************************************//**
* @brief
*   Configure DMA usage for this application.
*******************************************************************************/
static void DMAConfig(void)
{
  DMA_Init_TypeDef       dmaInit;
  DMA_CfgDescr_TypeDef   descrCfg;
  DMA_CfgChannel_TypeDef chnlCfg;

  /* Configure general DMA issues */
  dmaInit.hprot        = 0;
  dmaInit.controlBlock = dmaControlBlock;
  DMA_Init(&dmaInit);

  /* Configure DMA channel used */
  chnlCfg.highPri   = false;
  chnlCfg.enableInt = false;
  chnlCfg.select    = DMAREQ_ADC0_SCAN;
  chnlCfg.cb        = NULL;
  DMA_CfgChannel(DMA_CHANNEL, &chnlCfg);

  descrCfg.dstInc  = dmaDataInc4;
  descrCfg.srcInc  = dmaDataIncNone;
  descrCfg.size    = dmaDataSize4;
  descrCfg.arbRate = dmaArbitrate1;
  descrCfg.hprot   = 0;
  DMA_CfgDescr(DMA_CHANNEL, true, &descrCfg);
}


/**************************************************************************//**
 * @brief Simple task which is blinking led
 *****************************************************************************/
static void LedBlink(void *pParameters)
{

  pParameters = pParameters;   /* to quiet warnings */

  init();
  output("Hello world!",1,true);
  GPIO->P[BUZZER_PORT].DOUTSET = 1 << BUZZER_PIN;
  vTaskDelay(ALARM_TIME);
  GPIO->P[BUZZER_PORT].DOUTCLR = 1 << BUZZER_PIN;
  vTaskDelay(ALARM_DELAY);

  uint32_t samples[NUM_SAMPLES];
  int      i;

  int errataShift = 0;

  ADCConfig(&errataShift);
  DMAConfig();

  for (;;)
  {

	  //vTaskDelay(10000 / portTICK_RATE_MS);
    /* Set LSB of count value on LED */
	  GPIO->P[LED_PORT].DOUTSET = 1 << LED_PIN;
	  vTaskDelay(ALARM_TIME);
	  GPIO->P[LED_PORT].DOUTCLR = 1 << LED_PIN;
	  vTaskDelay(ALARM_DELAY);


	  DMA_ActivateBasic(DMA_CHANNEL,
	                      true,
	                      false,
	                      samples,
	                      (void *)((uint32_t) &(ADC0->SCANDATA)),
	                      NUM_SAMPLES - 1);

	  /* Start Scan */
	  ADC_Start(ADC0, adcStartScan);

	  /* Poll for scan comversion complete */
	  while (ADC0->STATUS & ADC_STATUS_SCANACT);

	  if (errataShift)
	  {
	      for (i = 0; i < NUM_SAMPLES; i++)
	      {
	        samples[i] <<= errataShift;
	      }
	  }

	  /* Format numbers and write to LCD */
	  char buffer[20];
	  sprintf(buffer,"Current:\t%5d\tmA",(int)((samples[0])*0.27-30));
	  output(buffer,2,false);
	  sprintf(buffer,"Voltage:\t%5d\tmV",(int)((samples[1])*2.0-300));
	  output(buffer,3,false);

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


  GPIO_DriveModeSet(BUZZER_PORT, GPIO_P_CTRL_DRIVEMODE_HIGH);

  //GPIO->P[CHARGE_PORT].DOUTSET = 1 << CHARGE_PIN;


  /* Create task for blinking leds */
  xTaskCreate( LedBlink,
           (const char *) "LedBlink",
           LEDBLINK_STACK_SIZE,
           NULL,
           LEDBLINK_TASK_PRIORITY,
           NULL );

  /* Configure PB9 as an input for PB0 button with filter enable (out = 1)*/
  GPIO_PinModeSet(gpioPortB, 9, gpioModeInput, 1);

  /* Enable GPIO_ODD interrupt vector in NVIC */
  NVIC_EnableIRQ(GPIO_ODD_IRQn);

  /* Configure PB9 interrupt on falling edge */
  GPIO_IntConfig(gpioPortB, 9, false, true, true);



  /*Start FreeRTOS Scheduler*/
  vTaskStartScheduler();

  /* Infinite loop */
  for( ;; ) { /* do nothing */ }

}

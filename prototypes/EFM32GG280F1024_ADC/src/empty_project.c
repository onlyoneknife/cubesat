/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_adc.h"
#include "em_gpio.h"

#define LED_PORT    gpioPortE
#define LED_PIN     2

/***************************************************************************//**
* @brief
*   Configure ADC usage for this application.
*******************************************************************************/
static void ADCConfig(void)
{
  ADC_Init_TypeDef       init       = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;

  /* Init common settings for both single conversion and scan mode */
  init.timebase = ADC_TimebaseCalc(0);
  /* Might as well finish conversion as quickly as possibly since polling */
  /* for completion. */
  /* Set ADC clock to 7 MHz, use default HFPERCLK */
  init.prescale = ADC_PrescaleCalc(7000000, 0);

  /* WARMUPMODE must be set to Normal according to ref manual before */
  /* entering EM2. In this example, the warmup time is not a big problem */
  /* due to relatively infrequent polling. Leave at default NORMAL, */

  ADC_Init(ADC0, &init);

  /* Init for single conversion use, measure VDD/3 with 1.25 reference. */
  singleInit.reference  = adcRef2V5;
  singleInit.input      = adcSingleInpCh4;
  singleInit.resolution = adcRes12Bit;

  /* The datasheet specifies a minimum aquisition time when sampling vdd/3 */
  /* 32 cycles should be safe for all ADC clock frequencies */
  singleInit.acqTime = adcAcqTime32;

  ADC_InitSingle(ADC0, &singleInit);
}

/******************************************************************************
 * @brief Delay function
 *****************************************************************************/
void Delay(uint16_t milliseconds)
{
  /* Enable clock for TIMER0 */
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;

  /* Set prescaler to maximum */
  TIMER0->CTRL = (TIMER0->CTRL & ~_TIMER_CTRL_PRESC_MASK) |  TIMER_CTRL_PRESC_DIV1024;

  /* Clear TIMER0 counter value */
  TIMER0->CNT = 0;

  /* Start TIMER0 */
  TIMER0->CMD = TIMER_CMD_START;

  /* Wait until counter value is over the threshold */
  while(TIMER0->CNT < 13*milliseconds){
   /* Do nothing, just wait */
  }

  /* Stop TIMER0 */
  TIMER0->CMD = TIMER_CMD_STOP;
}


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  uint32_t sample;
  uint32_t voltage;
  _Bool led_toggle = 0;

  /* Enable clock for GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
  GPIO_PinModeSet(LED_PORT,         /* Port */
                    LED_PIN,          /* Pin */
                    gpioModePushPull, /* Mode */
                    0 );              /* Output value */

  /* Enable clocks required */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_ADC0, true);

  ADCConfig();

  /* Stay in this loop forever at end of program */
  while (1)
  {

	  ADC_Start(ADC0, adcStartSingle);

	  /* Wait while conversion is active */
	  while (ADC0->STATUS & ADC_STATUS_SINGLEACT) ;

	  /* Get ADC result */
	  sample = ADC_DataSingleGet(ADC0);

	  /* Calculate supply voltage relative to 1.25V reference */
	  voltage = (sample * 2500) / 4096;

	  Delay(100);

	  /* Set LSB of count value on LED */
	  GPIO_PortOutSetVal(LED_PORT, led_toggle<<LED_PIN, 1<<LED_PIN);
  }
}

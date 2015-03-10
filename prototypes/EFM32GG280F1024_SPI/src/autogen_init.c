/********************************************************************
 *                 WARNING - DO NOT EDIT THIS FILE                  *
 * This file is automatially generated by the energyAware Designer. *
 * Any changes to this file will be overwritten if the project      *
 * files are generated again by the eADesigner.                     *
 ********************************************************************/

#include "autogen_init.h"
#include "em_cmu.h"

void eADesigner_Init(void)
{
  /* Using HFRCO at 14MHz as high frequency clock, HFCLK */
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
  
  /* No low frequency clock source selected */
  
  /* Enable GPIO clock */
  CMU_ClockEnable(cmuClock_GPIO, true);
  
  /* To avoid false start, configure output US1_TX as high on PD0 */
  GPIO->P[3].DOUT |= (1 << 0);
  /* Pin PD0 is configured to Push-pull */
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE0_MASK) | GPIO_P_MODEL_MODE0_PUSHPULL;
  /* Pin PD1 is configured to Input enabled */
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE1_MASK) | GPIO_P_MODEL_MODE1_INPUT;
  /* Pin PD2 is configured to Push-pull */
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE2_MASK) | GPIO_P_MODEL_MODE2_PUSHPULL;
  /* To avoid false start, configure output US1_CS as high on PD3 */
  GPIO->P[3].DOUT |= (1 << 3);
  /* Pin PD3 is configured to Push-pull */
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE3_MASK) | GPIO_P_MODEL_MODE3_PUSHPULL;
  
  /* Enable clock for USART1 */
  CMU_ClockEnable(cmuClock_USART1, true);
  /* Custom initialization for USART1 */
  USART1_setup(); 
  
  /* Module USART1 is configured to location 1 */
  USART1->ROUTE = (USART1->ROUTE & ~_USART_ROUTE_LOCATION_MASK) | USART_ROUTE_LOCATION_LOC1;
  /* Enable signals TX, RX, CLK, CS */
  USART1->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_CLKPEN | USART_ROUTE_CSPEN;
  
}
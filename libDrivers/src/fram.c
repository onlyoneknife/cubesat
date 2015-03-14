/**
 * @file fram.c
 * @author Brandon Borden
 * @date 2015-03-13
 */

/* Includes ------------------------------------------------------------------*/
#include "gyro.h"
#include "em_usart.h"
#include "em_gpio.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_TypeDef *spi;
unsigned int cs_pin;
GPIO_Port_TypeDef cs_port;
unsigned int hold_pin;
GPIO_Port_TypeDef hold_port;
unsigned int wp_pin;
GPIO_Port_TypeDef wp_port;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : FRAM_SetSPI
 * Description    : Configures the FRAM to use a given USART.
 * 				  : Target-specific for AlbertaSat Athena OBC Hardware.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetSPI(void) {
	spi = USART2;
	cs_port = gpioPortB;
	cs_pin = 6;
	hold_port = gpioPortD;
	hold_pin = 8;
	wp_port = gpioPortD;
	wp_pin = 5;

	GPIO->P[cs_port].DOUTSET = 1 << cs_pin; // Make sure CS is high/default state
}

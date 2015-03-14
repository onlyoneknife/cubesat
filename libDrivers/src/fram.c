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
unsigned int csPin;
GPIO_Port_TypeDef csPort;
unsigned int holdPin;
GPIO_Port_TypeDef holdPort;
unsigned int wpPin;
GPIO_Port_TypeDef wpPort;

FRAM_Mode_t FRAM_Mode;

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
	csPort = gpioPortB;
	csPin = 6;
	holdPort = gpioPortD;
	holdPin = 8;
	wpPort = gpioPortD;
	wpPin = 5;

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Make sure CS is high/default state
}

/*******************************************************************************
 * Function Name  : FRAM_SetWriteEnableLatch
 * Description    : Allows the issuing of subsequent opcodes for write
 * 				  : instructions.  Must be issued before any write operation.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetWriteEnableLatch(void) {

}

/*******************************************************************************
 * Function Name  : FRAM_ResetWriteEnableLatch
 * Description    : Disables all activity by clearing the write enable latch.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_ResetWriteEnableLatch(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Provides information about the current state of the
 *				  : write-protection features.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_ReadStatusReg(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Write into the status register and change the write protect
 * 				  : configuration.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteStatusReg(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Read memory from the FRAM.
 * Input          : Address (18-bit) of the first byte of the read operation.
 * 				  : Upper 6 bytes are ignored.
 * 				  : Number of bytes to read.
 * Output         : Memory data
 * Return         : None
 *******************************************************************************/
void FRAM_ReadMemory(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_WriteMemory
 * Description    : Write data into the FRAMs memory.
 * Input          : Address (18-bit) of the first byte of the write operation.
 * 				  : Upper 6 bytes are ignored.
 * 				  : Number of bytes to write
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteMemory(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_EnterSleepMode
 * Description    : Puts the FRAM into a low-power sleep mode.
 * Input          : Address (18-bit) of the first byte of the write operation.
 * 				  : Upper 6 bytes are ignored.
 * 				  : Number of bytes to write
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_EnterSleepMode(void) {
}

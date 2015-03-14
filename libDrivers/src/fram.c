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
 * Description    : Configures the FRAM to use a given USART
 * 				  : Target-specific for AlbertaSat Athena OBC Hardware
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

	FRAM_Mode = FRAM_NORMAL;

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Make sure CS is high/default state
	//TODO: Wait until device is powered up (1 ms after V_DD = V_DD_min)
}

/*******************************************************************************
 * Function Name  : FRAM_SetWriteEnableLatch
 * Description    : Allows the issuing of subsequent opcodes for write
 * 				  : instructions.  Must be issued before any write operation
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetWriteEnableLatch(void) {

}

/*******************************************************************************
 * Function Name  : FRAM_ResetWriteEnableLatch
 * Description    : Disables all activity by clearing the write enable latch
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_ResetWriteEnableLatch(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Provides information about the current state of the
 *				  : write-protection features
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_ReadStatusReg(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Write into the status register and change the write protect
 * 				  : configuration
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteStatusReg(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Read memory from the FRAM.
 * Input          : Address (18-bit) of the first byte of the read operation,
 * 				  : upper 6 bytes are ignored
 * Output         : Memory data
 * Return         : None
 *******************************************************************************/
void FRAM_ReadMemory(uint32_t address, uint8_t* data) {

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_TxDouble(spi, OP_READ);

	/* Send address bits 17 - 0. Bits 23- 18 are don't care */
	USART_TxDouble(spi, (uint8_t) (address >> 16));
	USART_TxDouble(spi, (uint8_t) (address >> 8));
	USART_TxDouble(spi, (uint8_t) address);

	* data = USART_RxDouble(spi);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_WriteMemory
 * Description    : Write data into the FRAMs memory
 * Input          : Address (18-bit) of the first byte of the write operation,
 * 				  : upper 6 bytes are ignored
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteMemory(void) {
}

/*******************************************************************************
 * Function Name  : FRAM_EnterSleepMode
 * Description    : Puts the FRAM into a low-power sleep mode or normal mode
 * Input          : FRAM_NORMAL | FRAM_SLEEP
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetMode(FRAM_Mode_t mode) {
	switch (mode) {

	case FRAM_SLEEP:
		if (FRAM_Mode = FRAM_NORMAL)
		{
			//TODO: put FRAM into sleep mode
		}
		break;

	case FRAM_NORMAL:
		if (FRAM_Mode = FRAM_SLEEP)
		{
			//TODO: Send dummy Read
			//TODO: make delay of at least 8ns
		}
		break;

	default:
		//TODO: return error
	}

	FRAM_Mode = mode;

}

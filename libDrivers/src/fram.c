/**
 * @file fram.c
 * @author Brandon Borden
 * @date 2015-03-13
 */

/* Includes ------------------------------------------------------------------*/
#include "fram.h"
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
void FRAM_Init(void) {
	spi = USART2;
	csPort = gpioPortB;
	csPin = 6;
	holdPort = gpioPortD;
	holdPin = 8;
	wpPort = gpioPortD;
	wpPin = 5;

	FRAM_Mode = FRAM_NORMAL;

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Make sure CS is high/default state
	GPIO->P[holdPort].DOUTSET = 1 << holdPin; // Make sure hold is high/default state

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
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, FRAM_OP_WREN);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_ResetWriteEnableLatch
 * Description    : Disables all activity by clearing the write enable latch
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_ResetWriteEnableLatch(void) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, FRAM_OP_WRDI);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Provides information about the current state of the
 *				  : write-protection features
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_ReadStatusReg(uint8_t* data) {
	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, FRAM_OP_RDSR);
	* data = USART_Rx(spi);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_ReadStatusReg
 * Description    : Write into the status register and change the write protect
 * 				  : configuration
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteStatusReg(uint8_t data) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	FRAM_ResetWriteEnableLatch(); // Allow writing
	GPIO->P[wpPort].DOUTSET = 1 << wpPin; // Set #WP high
	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, FRAM_OP_WRSR);
	USART_Tx(spi, data);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
	GPIO->P[wpPort].DOUTCLR = 1 << wpPin; // Set #WP low
	FRAM_SetWriteEnableLatch();
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
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, FRAM_OP_READ);

	/* Send address bits 17 - 0. Bits 23- 18 are don't care */
	USART_Tx(spi, (uint8_t) (address >> 16));
	USART_Tx(spi, (uint8_t) (address >> 8));
	USART_Tx(spi, (uint8_t) address);

	* data = USART_Rx(spi);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : FRAM_WriteMemory
 * Description    : Write data into the FRAMs memory
 * Input          : Address (18-bit) of the first byte of the write operation,
 * 				  : upper 6 bytes are ignored
 * 				  : Data to be written
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteMemory(uint32_t address, uint8_t data) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	FRAM_ResetWriteEnableLatch(); // Allow writing

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, FRAM_OP_WRITE);

	/* Send address bits 17 - 0. Bits 23- 18 are don't care */
	USART_Tx(spi, (uint8_t) (address >> 16));
	USART_Tx(spi, (uint8_t) (address >> 8));
	USART_Tx(spi, (uint8_t) address);

	USART_Tx(spi, data);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high

	FRAM_SetWriteEnableLatch();
}

/*******************************************************************************
 * Function Name  : FRAM_EnterSleepMode
 * Description    : Puts the FRAM into a low-power sleep mode or normal mode
 * Input          : FRAM_NORMAL | FRAM_SLEEP
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetSleepMode(FRAM_Mode_t mode) {
	switch (mode) {

	case FRAM_SLEEP:
		if (FRAM_Mode == FRAM_NORMAL)
		{
			GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low
			USART_Tx(spi, FRAM_OP_SLEEP);
			GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
		}
		break;

	case FRAM_NORMAL:
		if (FRAM_Mode == FRAM_SLEEP)
		{
			uint8_t value;
			FRAM_ReadStatusReg(&value); // Do a dummy read to wake up the FRAM
			//TODO: make delay of at least 8ns
		}
		break;

		//TODO: return error if otherwise?
	}

	FRAM_Mode = mode;

}

/*******************************************************************************
 * Function Name  : FRAM_SetBlockProtectRange
 * Description    : Set the range for the write protected block in FRAM
 * Input          : FRAM_NONE | FRAM_00000_TO_3FFFF | FRAM_20000_TO_3FFFF |
 * 				  : FRAM_30000_TO_3FFFF
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_SetBlockProtectRange(FRAM_BlkProtectRange_t blockRange) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	uint8_t value;
	FRAM_ReadStatusReg(&value);

	value &= 0xF3;	// Clear block protect bits
	value |= blockRange << FRAM_BLK_PROTECT; // Set new block protect range bits

	FRAM_WriteStatusReg(value);
}

/*******************************************************************************
 * Function Name  : FRAM_SetWriteProtectEnableMode
 * Description    : Enable or disable the write protect pin control.  Write
 * 				  : protect (#wp) disables writing to the status register when
 * 				  :	low
 * Input          : MEMS_ENABLE | MEMS_DISABLE
 * Output         : None
 * Return         : None
 *******************************************************************************/
void FRAM_WriteProtectEnable(State_t mode) {
	FRAM_SetSleepMode(FRAM_NORMAL); // Ensure FRAM not in sleep mode

	uint8_t value;
	FRAM_ReadStatusReg(&value);

	value &= 0x7F;	// Clear write protect bit
	value |= mode << FRAM_WPEN; // Set new write protect bit

	FRAM_WriteStatusReg(value);
}

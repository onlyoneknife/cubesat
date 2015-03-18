/**
 * @file SD.c
 * @author Brandon Borden
 * @date 2015-03-17
 */

// -----------------------------------------------------------
// TODO: REPLACE FRAM CODE BELOW WITH ACTUAL SD DRIVER CODE!!!
// -----------------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "SD.h"
#include "em_usart.h"
#include "em_gpio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
USART_TypeDef *spi;
unsigned int csPin;
GPIO_Port_TypeDef csPort;

SD_Mode_t SD_Mode;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : SD_SetSPI
 * Description    : Configures the SD to use a given USART
 * 				  : Target-specific for AlbertaSat Athena OBC Hardware
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_SetSPI(void) {
	spi = USART2;
	csPort = gpioPortC;
	csPin = 5;

	// Reduce clock to 400kHz for initialization

	SD_Mode = SD_NORMAL;



	GPIO->P[csPort].DOUTSET = 1 << csPin; // Make sure CS is high/default state
	// Restore clock frequency after initialization

}

/*******************************************************************************
 * Function Name  : SD_SetWriteEnableLatch
 * Description    : Allows the issuing of subsequent opcodes for write
 * 				  : instructions.  Must be issued before any write operation
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_SetWriteEnableLatch(void) {
	SD_SetSleepMode(SD_NORMAL); // Ensure SD not in sleep mode

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, SD_OP_WREN);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : SD_ResetWriteEnableLatch
 * Description    : Disables all activity by clearing the write enable latch
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_ResetWriteEnableLatch(void) {
	SD_SetSleepMode(SD_NORMAL); // Ensure SD not in sleep mode

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, SD_OP_WRDI);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : SD_ReadStatusReg
 * Description    : Provides information about the current state of the
 *				  : write-protection features
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_ReadStatusReg(uint8_t* data) {
	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, SD_OP_RDSR);
	* data = USART_Rx(spi);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : SD_ReadStatusReg
 * Description    : Write into the status register and change the write protect
 * 				  : configuration
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_WriteStatusReg(uint8_t data) {
	SD_SetSleepMode(SD_NORMAL); // Ensure SD not in sleep mode

	SD_ResetWriteEnableLatch(); // Allow writing
	GPIO->P[wpPort].DOUTSET = 1 << wpPin; // Set #WP high
	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, SD_OP_WRSR);
	USART_Tx(spi, data);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
	GPIO->P[wpPort].DOUTCLR = 1 << wpPin; // Set #WP low
	SD_SetWriteEnableLatch();
}

/*******************************************************************************
 * Function Name  : SD_ReadStatusReg
 * Description    : Read memory from the SD.
 * Input          : Address (18-bit) of the first byte of the read operation,
 * 				  : upper 6 bytes are ignored
 * Output         : Memory data
 * Return         : None
 *******************************************************************************/
void SD_ReadMemory(uint32_t address, uint8_t* data) {
	SD_SetSleepMode(SD_NORMAL); // Ensure SD not in sleep mode

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, SD_OP_READ);

	/* Send address bits 17 - 0. Bits 23- 18 are don't care */
	USART_Tx(spi, (uint8_t) (address >> 16));
	USART_Tx(spi, (uint8_t) (address >> 8));
	USART_Tx(spi, (uint8_t) address);

	* data = USART_Rx(spi);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
}

/*******************************************************************************
 * Function Name  : SD_WriteMemory
 * Description    : Write data into the SDs memory
 * Input          : Address (18-bit) of the first byte of the write operation,
 * 				  : upper 6 bytes are ignored
 * 				  : Data to be written
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_WriteMemory(uint32_t address, uint8_t data) {
	SD_SetSleepMode(SD_NORMAL); // Ensure SD not in sleep mode

	SD_ResetWriteEnableLatch(); // Allow writing

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	USART_Tx(spi, SD_OP_WRITE);

	/* Send address bits 17 - 0. Bits 23- 18 are don't care */
	USART_Tx(spi, (uint8_t) (address >> 16));
	USART_Tx(spi, (uint8_t) (address >> 8));
	USART_Tx(spi, (uint8_t) address);

	USART_Tx(spi, data);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high

	SD_SetWriteEnableLatch();
}

/*******************************************************************************
 * Function Name  : SD_EnterSleepMode
 * Description    : Puts the SD into a low-power sleep mode or normal mode
 * Input          : SD_NORMAL | SD_SLEEP
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_SetSleepMode(SD_Mode_t mode) {
	switch (mode) {

	case SD_SLEEP:
		if (SD_Mode == SD_NORMAL)
		{
			GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low
			USART_Tx(spi, SD_OP_SLEEP);
			GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high
		}
		break;

	case SD_NORMAL:
		if (SD_Mode == SD_SLEEP)
		{
			uint8_t value;
			SD_ReadStatusReg(&value); // Do a dummy read to wake up the SD
			//TODO: make delay of at least 8ns
		}
		break;

		//TODO: return error if otherwise?
	}

	SD_Mode = mode;

}

/*******************************************************************************
 * Function Name  : SD_SetBlockProtectRange
 * Description    : Set the range for the write protected block in SD
 * Input          : SD_NONE | SD_00000_TO_3FFFF | SD_20000_TO_3FFFF |
 * 				  : SD_30000_TO_3FFFF
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_SetBlockProtectRange(SD_BlkProtectRange_t blockRange) {
	SD_SetSleepMode(SD_NORMAL); // Ensure SD not in sleep mode

	uint8_t value;
	SD_ReadStatusReg(&value);

	value &= 0xF3;	// Clear block protect bits
	value |= blockRange << SD_BLK_PROTECT; // Set new block protect range bits

	SD_WriteStatusReg(value);
}

/*******************************************************************************
 * Function Name  : SD_SetWriteProtectEnableMode
 * Description    : Enable or disable the write protect pin control.  Write
 * 				  : protect (#wp) disables writing to the status register when
 * 				  :	low
 * Input          : MEMS_ENABLE | MEMS_DISABLE
 * Output         : None
 * Return         : None
 *******************************************************************************/
void SD_WriteProtectEnable(State_t mode) {
	SD_SetSleepMode(SD_NORMAL); // Ensure SD not in sleep mode

	uint8_t value;
	SD_ReadStatusReg(&value);

	value &= 0x7F;	// Clear write protect bit
	value |= mode << SD_WPEN; // Set new write protect bit

	SD_WriteStatusReg(value);
}

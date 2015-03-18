/**
 * @file SD.h
 * @author Brandon Borden
 * @date 2015-03-17
 */

// -----------------------------------------------------------
// TODO: REPLACE FRAM CODE BELOW WITH ACTUAL SD DRIVER CODE!!!
// -----------------------------------------------------------

#ifndef SD_H_
#define SD_H_

#include <stdint.h>

#ifndef __SHARED__TYPES
#define __SHARED__TYPES

typedef enum {
	MEMS_ENABLE = 0x01, MEMS_DISABLE = 0x00
} State_t;

#endif /*__SHARED__TYPES*/

typedef enum {
	SD_NORMAL = 0x00, SD_SLEEP = 0x01
} SD_Mode_t;

typedef enum {
	SD_NONE = 0x00,
	SD_30000_TO_3FFFF = 0x01,
	SD_20000_TO_3FFFF = 0x02,
	SD_00000_TO_3FFFF = 0x03,
} SD_BlkProtectRange_t;


#ifndef __SHARED__MACROS

#define __SHARED__MACROS
#define BIT(x) ( (x) )

#endif /*__SHARED__MACROS*/

/***************OP CODES***************/
#define SD_OP_WREN		0x06	// Set write enable latch
#define SD_OP_WRDI		0x04	// Reset write enable latch
#define SD_OP_RDSR		0x05	// Read status register
#define SD_OP_WRSR		0x01	// Write status register
#define SD_OP_READ		0x03	// Read memory data
#define SD_OP_FSTRD		0x0B	// Fast read memory data
#define SD_OP_WRITE		0x02	// Write memory data
#define SD_OP_SLEEP		0xB9	// Enter sleep mode
#define SD_OP_RDID		0x9F	// Read device ID

/***************STATUS REGISTER***************/
#define SD_WEL				1
#define SD_BLK_PROTECT		2
#define SD_WPEN				7

void SD_SetSPI(void);
void SD_SetWriteEnableLatch(void);
void SD_ResetWriteEnableLatch(void);
void SD_ReadStatusReg(uint8_t* data);
void SD_WriteStatusReg(uint8_t data);
void SD_ReadMemory(uint32_t address, uint8_t* data);
void SD_WriteMemory(uint32_t address, uint8_t data);
void SD_SetSleepMode(SD_Mode_t mode);
void SD_SetBlockProtectRange(SD_BlkProtectRange_t blockRange);
void SD_WriteProtectEnable(State_t mode);

#endif /* SD_H_ */

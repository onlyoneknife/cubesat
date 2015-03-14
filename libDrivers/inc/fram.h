/**
 * @file fram.h
 * @author Brandon Borden
 * @date 2015-03-13
 */

#ifndef FRAM_H_
#define FRAM_H_

#ifndef __ARCHDEP__TYPES
#define __ARCHDEP__TYPES
typedef unsigned char 		u8_t;
typedef unsigned short int 	u16_t;
typedef unsigned int 		u32_t;
#endif /*__ARCHDEP__TYPES*/

#ifndef __SHARED__TYPES
#define __SHARED__TYPES

typedef enum {
	MEMS_ENABLE = 0x01, MEMS_DISABLE = 0x00
} State_t;

#endif /*__SHARED__TYPES*/

typedef enum {
	FRAM_NORMAL = 0x00, FRAM_SLEEP = 0x01
} FRAM_Mode_t;

typedef enum {
	FRAM_NONE = 0x00,
	FRAM_30000_TO_3FFFF = 0x01,
	FRAM_20000_TO_3FFFF = 0x02,
	FRAM_00000_TO_3FFFF = 0x03,
} FRAM_BlkProtectRange_t;


#ifndef __SHARED__MACROS

#define __SHARED__MACROS
#define BIT(x) ( (x) )

#endif /*__SHARED__MACROS*/

/***************OP CODES***************/
#define FRAM_OP_WREN		0x06	// Set write enable latch
#define FRAM_OP_WRDI		0x04	// Reset write enable latch
#define FRAM_OP_RDSR		0x05	// Read status register
#define FRAM_OP_WRSR		0x01	// Write status register
#define FRAM_OP_READ		0x03	// Read memory data
#define FRAM_OP_FSTRD		0x0B	// Fast read memory data
#define FRAM_OP_WRITE		0x02	// Write memory data
#define FRAM_OP_SLEEP		0xB9	// Enter sleep mode
#define FRAM_OP_RDID		0x9F	// Read device ID

/***************STATUS REGISTER***************/
#define FRAM_WEL				1
#define FRAM_BLK_PROTECT		2
#define FRAM_WPEN				7

void FRAM_SetSPI(void);
void FRAM_SetWriteEnableLatch(void);
void FRAM_ResetWriteEnableLatch(void);
void FRAM_ReadStatusReg(u8_t* data);
void FRAM_WriteStatusReg(u8_t data);
void FRAM_ReadMemory(u32_t address, u8_t* data);
void FRAM_WriteMemory(u32_t address, u8_t data);
void FRAM_SetSleepMode(FRAM_Mode_t mode);
void FRAM_SetBlockProtectRange(FRAM_BlkProtectRange_t blockRange);
void FRAM_WriteProtectEnable(State_t mode);

#endif /* FRAM_H_ */

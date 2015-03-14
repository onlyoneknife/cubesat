/**
 * @file fram.h
 * @author Brandon Borden
 * @date 2015-03-13
 */

#ifndef FRAM_H_
#define FRAM_H_

typedef enum {
	FRAM_NORMAL = 0x00, FRAM_SLEEP = 0x01
} FRAM_Mode_t;

/***************OP CODES***************/
#define FRAM_WREN		0x06	// Set write enable latch
#define FRAM_WRDI		0x04	// Reset write enable latch
#define FRAM_RDSR		0x05	// Read status register
#define FRAM_WRSR		0x01	// Write status register
#define FRAM_READ		0x03	// Read memory data
#define FRAM_FSTRD		0x0B	// Fast read memory data
#define FRAM_WRITE		0x02	// Write memory data
#define FRAM_EN_SLEEP	0xB9	// Enter sleep mode
#define FRAM_RDID		0x9F	// Read device ID


#endif /* FRAM_H_ */

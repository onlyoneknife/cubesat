/**
 * @file SD.h
 * @author Brandon Borden
 * @date 2015-03-17
 */

#ifndef SD_H_
#define SD_H_

#include <stdint.h>

#ifndef __SHARED__TYPES
#define __SHARED__TYPES

typedef enum {
	MEMS_ENABLE = 0x01, MEMS_DISABLE = 0x00
} State_t;

#endif /*__SHARED__TYPES*/

#ifndef __SHARED__MACROS

#define __SHARED__MACROS
#define BIT(x) ( (x) )

#endif /*__SHARED__MACROS*/

/***************CID_REG***************/
#define SD_CID			0x06
#define SD_OP_WRDI		0x04




void SD_SetSPI(void);

#endif /* SD_H_ */

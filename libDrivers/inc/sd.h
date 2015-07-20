/**
 * @file SD.h
 * @author Brandon Borden
 * @date 2015-03-17
 */

#ifndef SD_H_
#define SD_H_

#include <stdint.h>

#ifndef __SHARED__MACROS

#define __SHARED__MACROS
#define BIT(x) ( (x) )

#endif /*__SHARED__MACROS*/

/***************CID_REG***************/
#define SD_CID			0x06
#define SD_OP_WRDI		0x04




void SD_Init(void);

#endif /* SD_H_ */

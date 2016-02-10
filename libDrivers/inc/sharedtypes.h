/*
 * sharedtypes.h
 *
 *  Created on: Apr 6, 2015
 *      Author: sdamkjar
 */

#ifndef SHAREDTYPES_H_
#define SHAREDTYPES_H_

/* --Exported common structure -----------------------------------------------*/
#ifndef __SHARED__TYPES
#define __SHARED__TYPES

/* --Shared includes -- */
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	MEMS_SUCCESS = 0x01, MEMS_ERROR = 0x00
} status_t;

typedef enum {
	MEMS_ENABLE = 0x01, MEMS_DISABLE = 0x00
} State_t;

typedef struct {
	int16_t AXIS_X;
	int16_t AXIS_Y;
	int16_t AXIS_Z;
} AxesRaw_t;

/* --Error Codes -------------------------------------------------------------*/
enum
{
	E_NO_ERR
	E_NO_DEVICE
	E_MALLOC_FAIL
	E_THREAD_FAIL
	E_NO_QUEUE
	E_INVALID_BUF_SIZE
	E_INVALID_PARAM
	E_NO_SS
	E_GARBLED_BUFFER
	E_FLASH_ERROR
	E_BOOT_SER
	E_BOOT_DEBUG
	E_BOOT_FLASH
	E_TIMEOUT
	E_NO_BUFFER
	E_OUT_OF_MEM
	E_FAIL
};

#endif /*__SHARED__TYPES*/

#endif /* SHAREDTYPES_H_ */

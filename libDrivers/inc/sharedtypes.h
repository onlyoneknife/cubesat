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




#define E_NO_ERR 			-1
#define E_NO_DEVICE 		-2
#define E_MALLOC_FAIL 		-3
#define E_THREAD_FAIL 		-4
#define E_NO_QUEUE 			-5
#define E_INVALID_BUF_SIZE 	-6
#define E_INVALID_PARAM 	-7
#define E_NO_SS 			-8
#define E_GARBLED_BUFFER 	-9
#define E_FLASH_ERROR 		-10
#define E_BOOT_SER 			-13
#define E_BOOT_DEBUG 		-14
#define E_BOOT_FLASH 		-15
#define E_TIMEOUT 			-16
#define E_NO_BUFFER 		-17
#define E_OUT_OF_MEM 		-18
#define E_FAIL 				-19

#endif /*__SHARED__TYPES*/

#endif /* SHAREDTYPES_H_ */

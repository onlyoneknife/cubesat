/*
 * i2c.h
 *
 *  Created on: Apr 2, 2015
 *      Author: sdamkjar
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#define I2C_ADDRESS         (98)
#define I2C_MAX_TX_BUFFER_SIZE ((uint8_t)100)
#define I2C_MAX_RX_BUFFER_SIZE ((uint8_t)100)
#define I2C_WRITE(n)        writeI2C(&n,sizeof(n))
#define I2C_READ(n,m)       readI2C(&n,m)

/* Exported common structure --------------------------------------------------------*/

#ifndef __SHARED__TYPES
#define __SHARED__TYPES

typedef enum {
	MEMS_SUCCESS = 0x01, MEMS_ERROR = 0x00
} status_t;

#endif /*__SHARED__TYPES*/

void setupI2C(void);

void I2C0_IRQHandler(void);

status_t writeI2C(void*,uint8_t);
status_t readI2C(void*,uint8_t);

#endif /* I2C_H_ */

 /***************************************************************************//**
 * @file I2C_Driver.h
 * @author Stefan Damkjar
 * @date 2016-05-18
 *******************************************************************************
 * @section License
 * <b>Copyright (C) 2015  Stefan Damkjar</b>
 *******************************************************************************
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_


/*******************************************************************************
 *******************************  INCLUDES   ***********************************
 ******************************************************************************/


/* System Includes */
#include <stdint.h>

/* FreeRTOS Includes */
#include "FreeRTOS.h"


/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/


/* CSP status values for error checking and interrupt handling */
#define MAX_DEVICES				(1)
#define DEVICE_MODE_M_T			(0)
#define DEVICE_MODE_M_R			(1)
#define DEVICE_MODE_ERR			(2)

/* I2C configuration. */
#define I2C_ADDRESS         	(98)
#define I2C_MAX_TX_BUFFER_SIZE 	((uint8_t)200)
#define I2C_MAX_RX_BUFFER_SIZE 	((uint8_t)200)

/* The I2C read bit is OR'ed with the address for a read operation */
#define I2C_READ_BIT 			(0x01)

/* DMA channels */
#define DMA_CHANNEL_I2C_TX 		(0)
#define DMA_CHANNEL_I2C_RX 		(1)

/* Maximum number of DMA transfer elements (minus 1) to transfer (<= 1023) */
#define DMA_MAX_MINUS_1	((_DMA_CTRL_N_MINUS_1_MASK >> _DMA_CTRL_N_MINUS_1_SHIFT)))


/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/


/**
 * Data structure for I2C frames
 */
typedef struct __attribute__((packed)) i2c_frame_s {
	uint8_t padding;
	uint8_t retries;
	uint32_t reserved;
	uint8_t dest;
	uint8_t len_rx;
	uint16_t len;
	uint8_t data[I2C_MTU];
} i2c_frame_t;


/**
 * Data structure for buffering frames on I2C
 */
typedef struct transmission_object_s {
	xQueueHandle queue;
	i2c_frame_t * frame;
	uint16_t next_byte;
} transmission_object_t;


/**
 * Details and status of I2C transactions
 */
typedef struct device_object_s {
	uint8_t * base;
	transmission_object_t rx;
	transmission_object_t tx;
	uint16_t speed;
	volatile unsigned int is_initialised;
	volatile unsigned int slave_addr;
	volatile unsigned int is_busy;
	volatile unsigned int mode;
	i2c_callback_t callback;
} device_object_t;


/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/


void I2C_init(int handle, int mode, uint8_t addr, uint16_t speed,
  int queue_len_tx, int queue_len_rx, i2c_callback_t callback);

 int I2C_send(int handle, i2c_frame_t * frame, uint16_t timeout);

 void I2C0_setup(void);

void I2C0_IRQHandler(void);

status_t commandRdy(void);
status_t writeI2C(uint8_t*);
status_t readI2C(uint8_t*);

 #endif /* I2C_DRIVER_H_ */
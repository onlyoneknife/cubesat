/**
 * @file i2c_efm32.c
 * @author Stefan Damkjar
 * @date 2015-12-25
 */

/* EFM32 EMLIB Includes */
#include "em_i2c.h"
#include "em_gpio.h"

/* Other Driver Includes */
#include "sharedtypes.h"
#include "i2c.h"

uint8_t TxBuffer[I2C_MAX_TX_BUFFER_SIZE ];
uint16_t TxBufferSize = 0;
uint16_t TxBufferHead = 0;
uint16_t TxBufferTail = 0;

uint8_t RxBuffer[I2C_MAX_RX_BUFFER_SIZE ];
uint16_t RxBufferSize = 0;
uint16_t RxBufferHead = 0;
uint16_t RxBufferTail = 0;


/**
 * Initialise the I2C driver
 *
 * @param handle Which I2C bus (if more than one exists)
 * @param mode I2C device mode. Must be either I2C_MASTER or I2C_SLAVE
 * @param addr Own slave address
 * @param speed Bus speed in kbps
 *
 */
int i2c_init(int handle, int mode, uint8_t addr, uint16_t speed, int queue_len_tx, int queue_len_rx, i2c_callback_t callback) {


}

/**
 * Send I2C frame via the selected device
 *
 * @param handle Handle to the device
 * @param frame Pointer to I2C frame
 * @param timeout Ticks to wait
 * @return Error code as per error.h
 */
int i2c_send(int handle, i2c_frame_t * frame, uint16_t timeout) {


}

/**
 * receive I2C frame from selected device
 * Context: Task only
 *
 * @param handle Handle to the device
 * @param frame Pointer to I2C frame (free this when done!!!)
 * @param timeout Number of ticks to wait for a frame
 * @return Returns error code: E_NO_ERR if a frame is received, or E_TIMEOUT if timed out, E_NO_DEVICE if handle is not a valid device
 */
int i2c_receive(int handle, i2c_frame_t ** frame, uint16_t timeout) {


}
/***************************************************************************//**
 * @file
 * @brief Provide MicroSD SPI configuration parameters.
 * @version 3.20.12
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __MICROSDCONFIG_H
#define __MICROSDCONFIG_H

/* Don't increase MICROSD_HI_SPI_FREQ beyond 8MHz. Next step will be 16MHz  */
/* which is out of spec.                                                    */
#define MICROSD_HI_SPI_FREQ     115200

#define MICROSD_LO_SPI_FREQ     100000
#define MICROSD_USART           USART1
#define MICROSD_LOC             USART_ROUTE_LOCATION_LOC0
#define MICROSD_CMUCLOCK        cmuClock_USART1
#define MICROSD_GPIOPORT        gpioPortB
#define MICROSD_CSPIN           11


#endif /* __MICROSDCONFIG_H */

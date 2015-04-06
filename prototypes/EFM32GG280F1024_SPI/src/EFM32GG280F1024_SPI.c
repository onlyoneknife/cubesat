#include "autogen_init.h"

/******************************************************************************
 * @file main_spi.c
 * @brief SPI Demo Application
 * @author Silicon Labs
 * @version 1.14
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/

#include <string.h>
#include "em_device.h"
#include "em_gpio.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "spi.h"
#include "usart.h"

#define LED_PORT    gpioPortB
#define LED_PIN     5

/* Buffers */
char transmitBuffer[] = {(char)241,(char)0};
#define            BUFFERSIZE    (sizeof(transmitBuffer) / sizeof(char))
char receiveBuffer[BUFFERSIZE];

/******************************************************************************
 * @brief  initializing spi settings
 *
 *****************************************************************************/
void init(void)
{
  /* Enabling clock to USART 1 */
  CMU_ClockEnable(cmuClock_USART1, true);
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
  GPIO_PinModeSet(LED_PORT,         /* Port */
                  LED_PIN,          /* Pin */
                  gpioModePushPull, /* Mode */
                  0 );              /* Output value */

  /* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
    GPIO_PinModeSet(gpioPortD,         /* Port */
                    3,          /* Pin */
                    gpioModePushPull, /* Mode */
                    0 );              /* Output value */
  /* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
    GPIO_PinModeSet(gpioPortF,         /* Port */
                    6,          /* Pin */
                    gpioModePushPull, /* Mode */
                    0 );              /* Output value */
  /* Configure LED_PORT pin LED_PIN (User LED) as push/pull outputs */
    GPIO_PinModeSet(gpioPortB,         /* Port */
                    12,          /* Pin */
                    gpioModePushPull, /* Mode */
                    0 );              /* Output value */

  /* Setup UART */
  SPI_setup(USART1_NUM, GPIO_POS1, true);
}

/******************************************************************************
 * @brief  Main function
 * Main is called from _program_start, see assembly startup file
 *****************************************************************************/
int main(void)
{

  /* Initialize chip */
  //eADesigner_Init();
  /* Initialize chip */
  CHIP_Init();

  /* Initalizing */
  init();

  GPIO_PortOutSetVal(gpioPortD, 1<<3, 1<<3);
  GPIO_PortOutSetVal(gpioPortF, 1<<6, 1<<6);
  GPIO_PortOutSetVal(gpioPortB, 1<<12, 1<<12);
  GPIO_PortOutSetVal(LED_PORT, 1<<LED_PIN, 1<<LED_PIN);
  while(1){
	  /* Data transmission to slave */
	  /* ************************** */
	  /* Setting up RX interrupt for master */
	  SPI1_setupRXInt(receiveBuffer, BUFFERSIZE);
	  GPIO_PortOutSetVal(LED_PORT, 0<<LED_PIN, 1<<LED_PIN);
	  /* Transmitting data */
	  USART1_sendBuffer(transmitBuffer, BUFFERSIZE);
	  GPIO_PortOutSetVal(LED_PORT, 1<<LED_PIN, 1<<LED_PIN);
  }

}







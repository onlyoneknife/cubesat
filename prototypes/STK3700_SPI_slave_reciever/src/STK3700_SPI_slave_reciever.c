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

/* Buffers */

#define            BUFFERSIZE    1
char receiveBuffer[BUFFERSIZE];

#define LED_PORT    gpioPortD
#define LED_PIN     4


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

  /* Setup UART */
  SPI_setup(USART1_NUM, GPIO_POS1, false);

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

	while(1){
	  /* Data reception from master */
	  /* ************************** */

	  /*Setting up both RX and TX interrupts for slave */
	  SPI1_setupSlaveInt(receiveBuffer, BUFFERSIZE, NO_TX, NO_TX);

	  if ( receiveBuffer[0] == (char)100 ) {
		  /* Set LSB of count value on LED */
		  GPIO_PortOutSetVal(LED_PORT, 1<<LED_PIN, 1<<LED_PIN);
	  }
	  else GPIO_PortOutSetVal(LED_PORT, 0<<LED_PIN, 1<<LED_PIN);

	}

  while (1) ;
}







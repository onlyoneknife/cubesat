/******************************************************************************
 * @file 3_lcd_solution.c
 * @brief LCD Controller solution
 * @author Energy Micro AS
 * @version 1.17
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2013 Energy Micro AS, http://www.energymicro.com</b>
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
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/

 /* emlib includes */
#include "em_device.h"
#include "em_chip.h"

/* display driver includes */
#include "display.h"
#include "textdisplay.h"



/******************************************************************************
 * @brief  Main function
 * Main is called from _program_start, see assembly startup file
 *****************************************************************************/
int main(void)
{  
  /* Initialize chip */
  CHIP_Init();  
  
  /* Initialize the display module */
  DISPLAY_Init( );
  
  /* Setup a config struct for TEXTDISPLAY */
  TEXTDISPLAY_Config_t conf;
  conf.displayDeviceNo = 0;
  conf.lfToCrLf = true;
  conf.scrollEnable = false;
  
  /* Create a TEXTDISPLAY device */ 
  TEXTDISPLAY_Handle_t  handle;
  TEXTDISPLAY_New(&conf, &handle);
  
  /* Write something to LCD */
  TEXTDISPLAY_WriteString(handle, "HELLO");
  
  /* Stay in this loop forever at end of program */
  while (1) ;
}




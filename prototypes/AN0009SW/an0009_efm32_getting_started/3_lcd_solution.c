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
#include "em_device.h"
#include "em_lcd.h"
#include "segmentlcd.h"
#include "em_chip.h"



/******************************************************************************
 * @brief  Main function
 * Main is called from _program_start, see assembly startup file
 *****************************************************************************/
int main(void)
{  
  /* Initialize chip */
  CHIP_Init();  
  
  /* Initialize LCD controller without boost*/
  SegmentLCD_Init(false);
  
  /* Write something to text field on LCD display */
  SegmentLCD_Write("HELLO");
      
  /* Turn on Gecko symbol */
  SegmentLCD_Symbol(LCD_SYMBOL_GECKO, 1);
  
  /* Set up animation start data */
  LCD->AREGA = 0x01;
  LCD->AREGB = 0x20;
    
  /* Enable and configure animation feature */
  LCD->BACTRL |=  LCD_BACTRL_FCEN |                /* Enable frame counter */
                 (7 << _LCD_BACTRL_FCTOP_SHIFT) |  /* Frame counter period */
                 LCD_BACTRL_AEN |                  /* Enable animation */
                 LCD_BACTRL_ALOGSEL_OR |           /* Logic function */
                 LCD_BACTRL_AREGASC_SHIFTLEFT |    /* Register A Shift direction */
                 LCD_BACTRL_AREGBSC_SHIFTRIGHT;    /* Register B Shift direction */
  
  
  /* Stay in this loop forever at end of program */
  while (1) ;
}




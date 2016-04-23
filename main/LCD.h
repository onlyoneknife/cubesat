

/* System Includes */
#include <stdio.h>
#include <stdint.h>

/* EFM32 EMLIB Includes */
#include "InitDevice.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"

#define LCD_Port gpioPortD
#define LCD_Control_Port gpioPortB
#define MPU_Interface_Port gpioPortF

#define Enable_Pin 7U
#define RW_Pin 6U
#define DC_Pin 5U
#define CS_Pin 1U
#define RES_Pin 2U

#define Blink_DELAY (100 / portTICK_RATE_MS)

void LCD_Blink(void)
{
GPIO->P[LCD_Control_Port].DOUTSET = 1 << Enable_Pin;
   vTaskDelay(Blink_DELAY);
GPIO->P[LCD_Control_Port].DOUTCLR = 1 << Enable_Pin;
}

void LCD_Command(char i)
{
GPIO->P[LCD_Control_Port].DOUTSET = 0 << CS_Pin;
GPIO->P[LCD_Port].DOUTSET = i;
GPIO->P[LCD_Control_Port].DOUTSET = 0 << DC_Pin;
GPIO->P[LCD_Control_Port].DOUTSET = 0 << RW_Pin;
LCD_Blink();
}

void LCD_Data(char i)
{
	GPIO->P[LCD_Control_Port].DOUTSET = 0 << CS_Pin;
	GPIO->P[LCD_Port].DOUTSET = i;
	GPIO->P[LCD_Control_Port].DOUTSET = 1 << DC_Pin;
	GPIO->P[LCD_Control_Port].DOUTSET = 0 << RW_Pin;
	LCD_Blink();

};

void LCD_Data_String(char *i)
{
	while(*i > 0)
	{
	LCD_Data(*i++);
};

void LCD_Int(void)
{
	GPIO->P[MPU_Interface_Port].DOUTSET = 1 << RES_Pin;
   vTaskDelay(Blink_DELAY);
   LCD_Data(0x00);
   LCD_Command(0x08);
   LCD_Command(0x01);
   LCD_Command(0x80);
   LCD_Command(0x0C);
   vTaskDelay(Blink_DELAY)
}






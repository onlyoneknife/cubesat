

/* System Includes */
#include <stdio.h>
#include <stdint.h>

/* EFM32 EMLIB Includes */
#include "InitDevice.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"

#include "FreeRTOS.h"

#define LCD_DATA_PORT gpioPortE
#define LCD_MPUI_Port gpioPortF

void LCD_Command(char i)
{
	GPIO_PinOutClear(CS_PORT,CS_PIN);			//	C_S = 0
	GPIO_PortOutSetVal(LCD_DATA_PORT,i,0xff);	//	P1  = i
	GPIO_PinOutClear(DC_PORT,DC_PIN);			//	DC  = 0
	GPIO_PinOutClear(RW_PORT,RW_PIN);			//	RW  = 0
	GPIO_PinOutSet(E_PORT,E_PIN);				//	E   = 1
	vTaskDelay(1/portTICK_RATE_MS);				//	delayms(1)
	GPIO_PinOutClear(E_PORT,E_PIN);				//  E	= 0
}

void LCD_Data(char i)
{
	GPIO_PinOutClear(CS_PORT,CS_PIN);			//	C_S = 0
	GPIO_PortOutSetVal(LCD_DATA_PORT,i,0xff);	//	P1  = i
	GPIO_PinOutSet(DC_PORT,DC_PIN);				//	DC  = 1
	GPIO_PinOutClear(RW_PORT,RW_PIN);			//	RW  = 0
	GPIO_PinOutSet(E_PORT,E_PIN);				//	E   = 1
	vTaskDelay(1/portTICK_RATE_MS);				//	delayms(1)
	GPIO_PinOutClear(E_PORT,E_PIN);				//  E	= 0
}

void output(char* message, int line, bool clear)
{
	int i;
	char arr[20] = {' '};
	sprintf(arr,"%20s",message);
	if (clear) LCD_Command(0x01);		//clear display
	LCD_Command(0x02);		//return home
	switch(line){
		case 1:
		for(i=0;i<20;i++) {
			LCD_Data(arr[i]);		//write solid blocks
		}
		break;
		case 2:
		LCD_Command(0xA0);		//line 2
		for(i=0;i<20;i++) {
			LCD_Data(arr[i]);		//write solid blocks
		}
		break;
		case 3:
		LCD_Command(0xC0);		//line 3
		for(i=0;i<20;i++) {
			LCD_Data(arr[i]);		//write solid blocks
		}
		break;
		case 4:
		LCD_Command(0xE0);		//line 4
		for(i=0;i<20;i++) {
			LCD_Data(arr[i]);		//write solid blocks
		}
		break;
	}
}


void init(void)
{
	GPIO_PortOutSetVal(LCD_MPUI_Port,0x10,0x1C);
	GPIO_PinOutSet(RES_PORT,RES_PIN);	//reset HIGH – inactive
	vTaskDelay(1/portTICK_RATE_MS);		//delay
	GPIO_PinOutSet(RES_PORT,RES_PIN);	//reset HIGH – inactive
	LCD_Command(0x2A);	//function set (extended LCD_Command set)
	LCD_Command(0x71);	//function selection A
	LCD_Data(0x00);		// disable internal VDD regulator (2.8V I/O). LCD_Data(0x5C) = enable regulator (5V I/O)
	LCD_Command(0x28);	//function set (fundamental LCD_Command set)
	LCD_Command(0x08);	//display off, cursor off, blink off
	LCD_Command(0x2A);	//function set (extended LCD_Command set)
	LCD_Command(0x79);	//OLED 	LCD_Command set enabled
	LCD_Command(0xD5);	//set display clock divide ratio/oscillator frequency
	LCD_Command(0x70);	//set display clock divide ratio/oscillator frequency
	LCD_Command(0x78);	//OLED 	LCD_Command set disabled
	LCD_Command(0x09);	//extended function set (4-lines)
	LCD_Command(0x06);	//COM SEG direction
	LCD_Command(0x72);	//function selection B
	LCD_Data(0x00);		//ROM CGRAM selection
	LCD_Command(0x2A);	//function set (extended LCD_Command set)
	LCD_Command(0x79);	//OLED 	LCD_Command set enabled
	LCD_Command(0xDA);	//set SEG pins hardware configuration
	LCD_Command(0x10);	//set SEG pins hardware configuration
	LCD_Command(0xDC);	//function selection C
	LCD_Command(0x00);	//function selection C
	LCD_Command(0x81);	//set contrast control
	LCD_Command(0x7F);	//set contrast control
	LCD_Command(0xD9);	//set phase length
	LCD_Command(0xF1);	//set phase length
	LCD_Command(0xDB);	//set VCOMH deselect level
	LCD_Command(0x40);	//set VCOMH deselect level
	LCD_Command(0x78);	//OLED LCD_Command set disabled
	LCD_Command(0x28);	//function set (fundamental LCD_Command set)
	LCD_Command(0x01);	//clear display
	LCD_Command(0x80);	//set DDRAM address to 0x00
	LCD_Command(0x0C);	//display ON, cursor OFF, blink OFF
	vTaskDelay(100/portTICK_RATE_MS);	//delay
}







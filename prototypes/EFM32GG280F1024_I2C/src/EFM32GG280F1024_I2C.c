/*****************************************************************************
* @file
* @brief I2C Demo Application
* @author Energy Micro AS
* @version 1.01
******************************************************************************
* @section License
* <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
******************************************************************************
*
* This source code is the property of Energy Micro AS. The source and compiled
* code may only be used on Energy Micro "EFM32" microcontrollers.
*
* This copyright notice may not be removed from the source code nor changed.
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
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_gpio.h"

#define I2C_ADDRESS   0xE2

#define LED_DELAY     (50 / portTICK_RATE_MS)
#define LED_PORT      (gpioPortA)
#define LED_PIN       (7)

uint8_t i2c_Buffer[] = "hello\n";
uint8_t i2c_BufferSize = sizeof(i2c_Buffer);
uint8_t i2c_BufferIndex;

/**************************************************************************//**
 * @brief  Starting oscillators and enabling clocks
 *****************************************************************************/
void setupOscillators(void)
{
  /* Enabling clock to the I2C, GPIO */
  CMU_ClockEnable(cmuClock_I2C0, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
}

/**************************************************************************//**
 * @brief  Setup I2C
 *****************************************************************************/
void setupI2C(void)
{
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  /* Using PD6 (SDA) and PD7 (SCL) */
  GPIO_PinModeSet(gpioPortD, 7, gpioModeInput, 1);
  GPIO_PinModeSet(gpioPortD, 6, gpioModeWiredAnd, 1);

  /* Enable pins at location 1 */
  I2C0->ROUTE = I2C_ROUTE_SDAPEN |
                I2C_ROUTE_SCLPEN |
                (1 << _I2C_ROUTE_LOCATION_SHIFT);

  /* Initializing the I2C */
  I2C_Init(I2C0, &i2cInit);

  /* Setting up to enable slave mode */
  I2C0->SADDR = I2C_ADDRESS;
  I2C0->CTRL |= I2C_CTRL_SLAVE | I2C_CTRL_AUTOACK | I2C_CTRL_AUTOSN;

  I2C0->IFC = ~0;
  I2C0->IEN = I2C_IEN_ADDR | I2C_IEN_SSTOP;
  NVIC_EnableIRQ(I2C0_IRQn);
}

/**************************************************************************//**
 * @brief I2C Interrupt Handler.
 *        The interrupt table is in assembly startup file startup_efm32.s
 *****************************************************************************/
void I2C0_IRQHandler(void)
{
  int status;
  status = I2C0->IF;

  if (status & I2C_IF_ADDR)
  {
    /* Address Match */
    I2C_IntClear(I2C0, I2C_IFC_ADDR);
    if (I2C0->RXDATA & 0x01)
    {
      /* Mater read, enable slave Tx */
      I2C0->IEN |= I2C_IEN_ACK;
      I2C0->TXDATA = i2c_Buffer[i2c_BufferIndex++];
    }
    else
    {
      /* Mater write, enable slave Rx */
      I2C0->IEN |= I2C_IEN_RXDATAV;
    }
  }
  else if (status & I2C_IF_RXDATAV)
  {
    /* Data received */
    i2c_Buffer[i2c_BufferIndex++] = I2C0->RXDATA;
  }
  else if (status & I2C_IF_ACK)
  {
    /* ACK received, send next data */
    I2C_IntClear(I2C0, I2C_IFC_ACK);
    I2C0->TXDATA = i2c_Buffer[i2c_BufferIndex++];
  }
  else
  {
    /* Stop received, Tx/Rx is ended */
    I2C_IntClear(I2C0, I2C_IFC_SSTOP);
    I2C0->IEN &= ~(I2C_IEN_ACK + I2C_IEN_RXDATAV);
    i2c_BufferIndex = 0;
  }
}

/**************************************************************************//**
 * @brief  Main function
 * Main is called from __iar_program_start, see assembly startup file
 *****************************************************************************/
int main(void)
{
  /* Initialize chip */
  CHIP_Init();

  /* Configuring clocks in the Clock Management Unit (CMU) */
  setupOscillators();

  /* Setting up i2c */
  setupI2C();

  /* Pin PA0 is configured to Push-pull */
  GPIO->P[0].MODEL = (GPIO->P[0].MODEL & ~_GPIO_P_MODEL_MODE0_MASK) | GPIO_P_MODEL_MODE0_PUSHPULL;
  GPIO->P[LED_PORT].DOUTSET = 1 << LED_PIN;

  while (1)
  {
    __WFI();
  }
}

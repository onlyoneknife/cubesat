/********************************************************************
 *                 WARNING - DO NOT EDIT THIS FILE                  *
 * This file is automatially generated by the energyAware Designer. *
 * Any changes to this file will be overwritten if the project      *
 * files are generated again by the eADesigner.                     *
 ********************************************************************/

#include "autogen_usart1.h"

void USART1_setup(void)
{
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;

  init.baudrate     = 115200;
  init.oversampling = usartOVS16;
  init.databits     = usartDatabits8;
  init.parity       = usartNoParity;
  init.stopbits     = usartStopbits1;
  init.mvdis        = 0;
  init.prsRxEnable  = 0;

  USART_InitAsync(USART1, &init);
}

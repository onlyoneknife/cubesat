/********************************************************************
 *                 WARNING - DO NOT EDIT THIS FILE                  *
 * This file is automatially generated by the energyAware Designer. *
 * Any changes to this file will be overwritten if the project      *
 * files are generated again by the eADesigner.                     *
 ********************************************************************/

#include "autogen_usart2.h"

void USART2_setup(void)
{
  USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;

  init.baudrate     = 10000000;
  init.databits     = usartDatabits8;
  init.msbf         = 1;
  init.master       = 1;
  init.clockMode    = usartClockMode3;
  init.prsRxEnable  = 0;
  init.autoTx       = 0;

  USART_InitSync(USART2, &init);
  // Enable USART - Will be used as both receiver and transmitter
  USART_Enable(USART2, usartEnable);
}


/********************************************************************
 *                 WARNING - DO NOT EDIT THIS FILE                  *
 * This file is automatially generated by the energyAware Designer. *
 * Any changes to this file will be overwritten if the project      *
 * files are generated again by the eADesigner.                     *
 ********************************************************************/

#include "autogen_usart1.h"

void USART1_setup(void)
{
  USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;

  init.baudrate     = 1000000;
  init.databits     = usartDatabits16;
  init.msbf         = 0;
  init.master       = 1;
  init.clockMode    = usartClockMode0;
  init.prsRxEnable  = 0;
  init.autoTx       = 0;

  USART_InitSync(USART1, &init);
}


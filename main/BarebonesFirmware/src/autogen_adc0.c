/********************************************************************
 *                 WARNING - DO NOT EDIT THIS FILE                  *
 * This file is automatially generated by the energyAware Designer. *
 * Any changes to this file will be overwritten if the project      *
 * files are generated again by the eADesigner.                     *
 ********************************************************************/

#include "autogen_adc0.h"

void
ADC0_setup(void)
{
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;

  init.ovsRateSel = adcOvsRateSel2;
  init.lpfMode = adcLPFilterBypass;
  init.warmUpMode = adcWarmupNormal;
  init.timebase = ADC_TimebaseCalc(0);
  init.prescale = ADC_PrescaleCalc(7000000, 0);
  init.tailgate = 0;

  ADC_Init(ADC0, &init);
}

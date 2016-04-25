//=========================================================
// inc/InitDevice.h: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!
//=========================================================
#ifndef __INIT_DEVICE_H__
#define __INIT_DEVICE_H__

// USER CONSTANTS
// USER PROTOTYPES

// $[Mode Transition Prototypes]
extern void enter_DefaultMode_from_RESET(void);
// [Mode Transition Prototypes]$

// $[Config(Per-Module Mode)Transition Prototypes]
extern void HFXO_enter_DefaultMode_from_RESET(void);
extern void LFXO_enter_DefaultMode_from_RESET(void);
extern void CMU_enter_DefaultMode_from_RESET(void);
extern void ADC0_enter_DefaultMode_from_RESET(void);
extern void ACMP0_enter_DefaultMode_from_RESET(void);
extern void ACMP1_enter_DefaultMode_from_RESET(void);
extern void DAC0_enter_DefaultMode_from_RESET(void);
extern void BURTC_enter_DefaultMode_from_RESET(void);
extern void RTC_enter_DefaultMode_from_RESET(void);
extern void OPAMP0_enter_DefaultMode_from_RESET(void);
extern void OPAMP1_enter_DefaultMode_from_RESET(void);
extern void OPAMP2_enter_DefaultMode_from_RESET(void);
extern void USART0_enter_DefaultMode_from_RESET(void);
extern void USART1_enter_DefaultMode_from_RESET(void);
extern void USART2_enter_DefaultMode_from_RESET(void);
extern void UART0_enter_DefaultMode_from_RESET(void);
extern void UART1_enter_DefaultMode_from_RESET(void);
extern void LEUART0_enter_DefaultMode_from_RESET(void);
extern void LEUART1_enter_DefaultMode_from_RESET(void);
extern void VCMP_enter_DefaultMode_from_RESET(void);
extern void WDOG_enter_DefaultMode_from_RESET(void);
extern void I2C0_enter_DefaultMode_from_RESET(void);
extern void I2C1_enter_DefaultMode_from_RESET(void);
extern void TIMER0_enter_DefaultMode_from_RESET(void);
extern void TIMER1_enter_DefaultMode_from_RESET(void);
extern void TIMER2_enter_DefaultMode_from_RESET(void);
extern void TIMER3_enter_DefaultMode_from_RESET(void);
extern void LETIMER0_enter_DefaultMode_from_RESET(void);
extern void PCNT0_enter_DefaultMode_from_RESET(void);
extern void PCNT1_enter_DefaultMode_from_RESET(void);
extern void PCNT2_enter_DefaultMode_from_RESET(void);
extern void PRS_enter_DefaultMode_from_RESET(void);
extern void ETM_enter_DefaultMode_from_RESET(void);
extern void EBI_enter_DefaultMode_from_RESET(void);
extern void PORTIO_enter_DefaultMode_from_RESET(void);
// [Config(Per-Module Mode)Transition Prototypes]$

#endif

// $[User-defined pin name abstraction]

#define ADC0_CH0_PIN        (0)
#define ADC0_CH0_PORT       (gpioPortD)

#define ADC0_CH2_PIN        (2)
#define ADC0_CH2_PORT       (gpioPortD)

#define BS0_PIN             (2)
#define BS0_PORT            (gpioPortF)

#define BS1_PIN             (3)
#define BS1_PORT            (gpioPortF)

#define BS2_PIN             (4)
#define BS2_PORT            (gpioPortF)

#define BUZZER_PIN          (10)
#define BUZZER_PORT         (gpioPortD)

#define CHARGE_PIN          (10)
#define CHARGE_PORT         (gpioPortA)

#define CS_PIN              (8)
#define CS_PORT             (gpioPortF)

#define CURRENT_PIN         (0)
#define CURRENT_PORT        (gpioPortD)

#define DB0_PIN             (0)
#define DB0_PORT            (gpioPortE)

#define DB1_PIN             (1)
#define DB1_PORT            (gpioPortE)

#define DB2_PIN             (2)
#define DB2_PORT            (gpioPortE)

#define DB3_PIN             (3)
#define DB3_PORT            (gpioPortE)

#define DB4_PIN             (4)
#define DB4_PORT            (gpioPortE)

#define DB5_PIN             (5)
#define DB5_PORT            (gpioPortE)

#define DB6_PIN             (6)
#define DB6_PORT            (gpioPortE)

#define DB7_PIN             (7)
#define DB7_PORT            (gpioPortE)

#define DC_PIN              (5)
#define DC_PORT             (gpioPortF)

#define E_PIN               (7)
#define E_PORT              (gpioPortF)

#define LED_PIN             (4)
#define LED_PORT            (gpioPortC)

#define RES_PIN             (9)
#define RES_PORT            (gpioPortF)

#define RW_PIN              (6)
#define RW_PORT             (gpioPortF)

#define VOLTAGE_PIN         (2)
#define VOLTAGE_PORT        (gpioPortD)

// [User-defined pin name abstraction]$


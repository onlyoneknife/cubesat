/**************************************************************************//**
 * @file
 * @brief Driver for Micrel KSZ8851SNL Ethernet controller
 * @version 3.20.12
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#ifndef _ksz8851snl_H_
#define _ksz8851snl_H_

/**************************************************************************//**
* @addtogroup Drivers
* @{
******************************************************************************/

/**************************************************************************//**
* @addtogroup ksz8851snl
* @{ Detailed description of KSZ8851SNL driver
* Low level non-DMA driver for KSZ8851SNL.
******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Interrupt Enable Register Options */
/** Enable link change interrupt */
#define   KSZ8851SNL_INT_LINK_CHANGE     0x8000
/** Enable transmit done interrupt */
#define   KSZ8851SNL_INT_TX_DONE         0x4000
/** Enable receive interrupt */
#define   KSZ8851SNL_INT_RX_DONE         0x2000
/** Enable receive overrun interrupt */
#define   KSZ8851SNL_INT_RX_OVERRUN      0x0800
/** Enable transmit process stopped interrupt */
#define   KSZ8851SNL_INT_TX_STOPPED      0x0200
/** Enable receive process stopped interrupt */
#define   KSZ8851SNL_INT_RX_STOPPED      0x0100
/** Enable transmit space available interrupt */
#define   KSZ8851SNL_INT_TX_SPACE        0x0040
/** Enable WOL on receive wake-up frame detect interrupt */
#define   KSZ8851SNL_INT_RX_WOL_FRAME    0x0020
/** Enable magic packet detect interrupt */
#define   KSZ8851SNL_INT_MAGIC           0x0010
/** Enable link up detect interrupt */
#define   KSZ8851SNL_INT_LINKUP          0x0008
/** Enable detect interrupt */
#define   KSZ8851SNL_INT_ENERGY          0x0004
/** Enable receive SPI bus error interrupt */
#define   KSZ8851SNL_INT_SPI_ERROR       0x0002

/* Service RX done, link change and error IRQs. */
#define   KSZ8851SNL_INT_ENABLE_MASK     (KSZ8851SNL_INT_RX_DONE | \
                                          KSZ8851SNL_INT_RX_STOPPED | \
                                          KSZ8851SNL_INT_TX_STOPPED | \
                                          KSZ8851SNL_INT_LINK_CHANGE | \
                                          KSZ8851SNL_INT_SPI_ERROR)

typedef struct KSZ8851SLN_mib_s
{
  uint32_t RxByteCnt;
  uint32_t RxUndersizePktCnt;
  uint32_t RxFragmentsCnt;
  uint32_t RxOversizeCnt;
  uint32_t RxJabbersCnt;
  uint32_t RxSymbolErrorCnt;
  uint32_t RxCRCErrorCnt;
  uint32_t RxPausePktsCnt;
  uint32_t RxBroadcastCnt;
  uint32_t RxMulticastCnt;
  uint32_t RxUnicastCnt;
  uint32_t TxByteCnt;
  uint32_t TxPausePktsCnt;
  uint32_t TxBroadcastPktsCnt;
  uint32_t TxMulticastPktsCnt;
  uint32_t TxUnicastPktsCnt;
  uint32_t TxDeferredCnt;
  uint32_t TxTotalCollisionCnt;
} KSZ8851SLN_mib_t;


void     KSZ8851SNL_Init(void);
void     KSZ8851SNL_Enable(void);
uint16_t KSZ8851SNL_Receive(uint8_t *pRXData, uint16_t bufferLength);
bool     KSZ8851SNL_LongTransmitInit(uint16_t TXLength);
void     KSZ8851SNL_LongTransmit(uint16_t TXLength, uint8_t *pTXData);
void     KSZ8851SNL_LongTransmitEnd(uint16_t TXLength, uint8_t *pTXData);

void     KSZ8851SNL_MacAddressGet(uint8_t *macAddress);
void     KSZ8851SNL_MIBCountersRead(char* param);
void     KSZ8851SNL_ISRStatusW1Clear(uint16_t mask);
void     KSZ8851SNL_PMECRStatusRWClear(uint16_t mask);
uint16_t KSZ8851SNL_ISRStatusGet(void);
void     KSZ8851SNL_FrameCounterSet(void);
uint16_t KSZ8851SNL_FrameCounterGet(void);
void     KSZ8851SNL_InteruptsEnable(void);
void     KSZ8851SNL_InteruptsDisable(void);
uint16_t KSZ8851SNL_RXQCRGet(void);
uint16_t KSZ8851SNL_PHYStatusGet(void);
void     KSZ8851SNL_TxQueueReset(void);
void     KSZ8851SNL_RxQueueReset(void);

void     KSZ8851SNL_RegistersDump(void);
void     KSZ8851SNL_AllRegistersDump(void);
void     KSZ8851SNL_MIBCountersDump(void);
void     KSZ8851SNL_MIBCountersUpdate(void);
uint16_t KSZ8851SNL_FrameCounterGet(void);

#ifdef __cplusplus
}
#endif

/** @} (end group ksz8851snl) */
/** @} (end group Drivers) */

#endif

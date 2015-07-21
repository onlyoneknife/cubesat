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
#include <stdio.h>

#include "ksz8851snl.h"
#include "ethspi.h"
#include "em_gpio.h"

#include "lwip/sys.h"

#include "lwipopts.h"
#include "debug.h"


#ifndef LWIP4EFM32
#error "lwiopts.h for EFM32 are not included"
#endif

/* Register definitions */
#define LOW_QMU_MAC_REG              0x10 /**< MAC Address Low */
#define MID_QMU_MAC_REG              0x12 /**< MAC Address Middle*/
#define HIGH_QMU_MAC_REG             0x14 /**< MAC Address High*/
#define OBC_REG                      0x20 /**< On-Chip Bus Control Register */
#define GLOBAL_RESET_REG             0x26 /**< Global Reset Register */
#define TX_FLOW_CTRL_REG             0x70 /**< Transmit Flow Control Register */
#define RX_FLOW_CTRL1_REG            0x74 /**< Receive Flow Control Register 1 */
#define RX_FLOW_CTRL2_REG            0x76 /**< Receive Flow Control Register 2 */
#define TX_MEM_INFO_REG              0x78 /**< TXQ Memory Information Register */
#define RX_FRH_STAT_REG              0x7C /**< Receive Frame Header Status Register */
#define RX_FRH_BC_REG                0x7E /**< Receive Frame Header Bytecount Register */
#define TXQ_CMD_REG                  0x80 /**< TXQ Command Register */
#define RXQ_CMD_REG                  0x82 /**< RXQ Command Register */
#define TX_FD_PTR_REG                0x84 /**< TX Frame Data Pointer Register */
#define RX_FD_PTR_REG                0x86 /**< RX Frame Data Pointer Register */
#define INT_ENABLE_REG               0x90 /**< Interrupt Enable Register */
#define INT_STATUS_REG               0x92 /**< Interrupt Status Register */
#define RX_FRAME_THRES_REG           0x9C /**< RX Frame Count & Threshold Register */
#define TX_NEXT_FRS_REG              0x9E /**< TX Next Frame size register */
#define FLOW_CTRL_LOW_WATERMARK      0xB0 /**< Configure Low Watermark to 6KByte */
#define FLOW_CTRL_HIGH_WATERMARK     0xB2 /**< Configure High Watermark to 4KByte */
#define CIDER_REG                    0xC0 /**< Chip ID and Enable Register */
#define IND_ACC_CTRL_REG             0xC8 /**< Indirect access control Register */
#define IND_ACC_DATA_LOW_REG         0xD0 /**< Indirect access data low Register */
#define IND_ACC_DATA_HIGH_REG        0xD2 /**< Indirect access data low Register */
#define PMECR_REG                    0xD4 /**< Power Managment Event Control Register */
#define PHY_RST_REG                  0xD8 /**< PHY Reset Register  */
#define PHY1_CTRL_REG                0xE4 /**< PHY1 MII-Register Basic Control Register */
#define PORT1_CTRL_REG               0xF6 /**< Port 1 Control Register */
#define P1SR_REG                     0xF8 /**< Port 1 Status Register */

#define KSZ8851SNL_CHIP_ID           0x8870 /**< Default Chip ID for KSZ8851SNL */
#define CHIP_ID_MASK                 0xFFF0 /**< Used to mask the revision ID */
#define ONE_FRAME_THRES              0x0001 /**< RX INT after one frame */
#define FD_PTR_AUTO_INC              0x4000 /**< Used to reset the FD pointer */
#define CLEAR_INT                    0xFFFF /**< Used to clear INT_STATUS_REG */
#define NO_INT                       0x0000 /**< Used to disable the interupts */
#define TX_MEM_AVAIL_MASK            0x1FFF /**< Used to mask the reserved bits */
#define FRAME_ID_MASK                0x003F /**< Used to mask the reserved bits */
#define CHECKSUM_VALID_FRAME_MASK    0x3C17 /**< CRC OK for ICMP, IP, TCP, UDP; /
                                             *   MII error; /
                                             *   Frame too long error */

#define VALID_FRAME_MASK             0x8000

#define RECEIVED_FRAME_VALID_POS     0x0010 /**< Received valid frame byte pos */
#define RX_BYTE_CNT_MASK             0x0FFF /**< Used to mask the reserved bits */
#define LSB_MASK                     0x00FF /**< Used to mask the LSB */
#define MSB_POS                      0x0008 /**< Used to mark the MSB pos */
#define TX_INT_on_COMPLETION         0x8000 /**< TX INT on completion */
#define WORD_SIZE                    0x0004 /**< Word size in # of bytes */
#define EXTRA_SIZE                   0x0008 /**< Needed for the frame header */
#define BLOCKING_RECEIVE             0      /**< Determines if receive will block */
#define WATERMARK_6KB                0x0600 /**< 6KByte Watermark */
#define WATERMARK_4KB                0x0400 /**< 4KByte Watermark */
/* Energy Micro's MAC address space */
#define HIGH_QMU_MAC_H               0xD0   /**< 1st segment of the MAC address */
#define HIGH_QMU_MAC_L               0xCF   /**< 2nd segment of the MAC address */
#define MID_QMU_MAC_H                0x5E   /**< 3rd segment of the MAC address */
#define MID_QMU_MAC_L                0x00   /**< 4th segment of the MAC address */
#define LOW_QMU_MAC_H                0x00   /**< 5th segment of the MAC address */
#define LOW_QMU_MAC_L                0x00   /**< 6th segment of the MAC address */
#define BYTE_MASK                    0x00FF /**< Used to mask the LSB */
#define BYTE_SIZE                    0x0008 /**< Used to mark the MSB pos */

/* TX Flow Control Register Options */

/** Enable Transmit Checksum Generation for ICMP */
#define   TX_FLOW_CTRL_ICMP_CHECKSUM    0x0100
/** Enable Transmit Checksum Generation for UDP */
#define   TX_FLOW_CTRL_UDP_CHECKSUM     0x0080
/** Enable Transmit Checksum Generation for TCP */
#define   TX_FLOW_CTRL_TCP_CHECKSUM     0x0040
/** Enable Transmit Checksum Generation for IP */
#define   TX_FLOW_CTRL_IP_CHECKSUM      0x0020
/** Flush Transmit Queue */
#define   TX_FLOW_CTRL_FLUSH_QUEUE      0x0010
/** Transmit flow control enable*/
#define   TX_FLOW_CTRL_FLOW_ENABLE      0x0008
/** Transmit Padding enable */
#define   TX_FLOW_CTRL_PAD_ENABLE       0x0004
/** Transmit CRC Enable */
#define   TX_FLOW_CTRL_CRC_ENABLE       0x0002
/** Enable tranmsit */
#define   TX_FLOW_CTRL_ENABLE           0x0001

/** TX FLOW CONTROL Initialization collection */
#define   TX_FLOW_CTRL_CONFIG           (TX_FLOW_CTRL_ICMP_CHECKSUM | \
                                         TX_FLOW_CTRL_UDP_CHECKSUM |  \
                                         TX_FLOW_CTRL_TCP_CHECKSUM |  \
                                         TX_FLOW_CTRL_IP_CHECKSUM |   \
                                         TX_FLOW_CTRL_FLOW_ENABLE |   \
                                         TX_FLOW_CTRL_PAD_ENABLE |    \
                                         TX_FLOW_CTRL_CRC_ENABLE)

/* TXQ Command Register Options */
/** Enable Auto-Enqueue TXQ Frame */
#define   TXQ_AUTO_ENQUEUE         0x0004
/** Enable INT generation when TXQ Memory Available */
#define   TXQ_MEM_AVAILABLE_INT    0x0002
/** Enable Manual Engueue TXQ Frame */
#define   TXQ_ENQUEUE              0x0001


/* RX Flow Control Register 1 Options */
/** Flush Receive Queue */
#define   RX_FLOW_CTRL_FLUSH_QUEUE       0x8000
/** Enable Receive UDP Frame Checksum Check */
#define   RX_FLOW_CTRL_UDP_CHECKSUM      0x4000
/** Enable Receive TCP Frame Checksum Check */
#define   RX_FLOW_CTRL_TCP_CHECKSUM      0x2000
/** Enable Receive IP Frame Checksum Check */
#define   RX_FLOW_CTRL_IP_CHECKSUM       0x1000
/** Receive Physical Address Filtering with MAC Address Enable */
#define   RX_FLOW_CTRL_MAC_FILTER        0x0800
/** Enable Receive Flow Control */
#define   RX_FLOW_CTRL_FLOW_ENENABLE     0x0400
/** Enable Receive Error Frames */
#define   RX_FLOW_CTRL_BAD_PACKET        0x0200
/** Enable Receive Broadcast frames */
#define   RX_FLOW_CTRL_BROADCAST_ENABLE  0x0080
/** Enable Receive Multicast frames */
#define   RX_FLOW_CTRL_MULTICAST_ENABLE  0x0040
/** Enable Receive Unicast frames */
#define   RX_FLOW_CTRL_UNICAST_ENABLE    0x0020
/** Receive all incoming frames */
#define   RX_FLOW_CTRL_PROMISCUOUS_MODE  0x0012
/** Receive all frames */
#define   RX_FLOW_CTRL_RX_ALL            0x0010
/** Receive Inverse Filtering */
#define   RX_FLOW_CTRL_INVERSE_FILTER    0x0002
/** Enable receive */
#define   RX_FLOW_CTRL_RX_ENABLE         0x0001

/** RX FLOW CONTROL1 Initialization collection */
#define   RX_FLOW_CTRL1_CONFIG           (RX_FLOW_CTRL_UDP_CHECKSUM     |  \
                                          RX_FLOW_CTRL_TCP_CHECKSUM     |  \
                                          RX_FLOW_CTRL_IP_CHECKSUM      |  \
                                          RX_FLOW_CTRL_MAC_FILTER       |  \
                                          RX_FLOW_CTRL_FLOW_ENENABLE    |  \
                                          RX_FLOW_CTRL_BROADCAST_ENABLE |  \
                                          RX_FLOW_CTRL_UNICAST_ENABLE)

/* RX Flow Control Register 2 Options */
/* SPI Receive Data Burst Length */
/** Receive Flow Control Burst Length mask */
#define   RX_FLOW_CTRL_BURST_LEN_MASK        0x00E0
/** 4 bytes length */
#define   RX_FLOW_CTRL_BURST_LEN_4           0x0000
/** 8 Bytes length */
#define   RX_FLOW_CTRL_BURST_LEN_8           0x0020
/** 16 Bytes length */
#define   RX_FLOW_CTRL_BURST_LEN_16          0x0040
/** 32 Bytes length */
#define   RX_FLOW_CTRL_BURST_LEN_32          0x0060
/** Full frame length */
#define   RX_FLOW_CTRL_BURST_LEN_FRAME       0x0080
/** IPV4/IPV6/UDP Fragment Frame Pass */
#define   RX_FLOW_CTRL_IPV6_UDP_FRAG_PASS    0x0010
/** IPV4/IPV6/UDP Frame Checksum Equal Zero */
#define   RX_FLOW_CTRL_IPV6_UDP_ZERO_PASS    0x0008
/** Enable UDP Lite frame */
#define   RX_FLOW_CTRL_UDP_LITE_CHECKSUM     0x0004
/** Enable ICMP frame */
#define   RX_FLOW_CTRL_ICMP_CHECKSUM         0x0002
/** Receive Source Address Filtering */
#define   RX_FLOW_CTRL_BLOCK_MAC             0x0001

/** RX FLOW CONTROL2 Initialization collection */
#define   RX_FLOW_CTRL2_CONFIG               (RX_FLOW_CTRL_IPV6_UDP_FRAG_PASS | \
                                              RX_FLOW_CTRL_UDP_LITE_CHECKSUM |  \
                                              RX_FLOW_CTRL_ICMP_CHECKSUM |      \
                                              RX_FLOW_CTRL_BURST_LEN_FRAME)

/* RXQ Command Register Options */
/** RX interrupt is occured on timer duration */
#define   RXQ_ON_TIME_INT            0x1000
/** RX interrupt is occured on byte count threshold */
#define   RXQ_ON_BYTE_CNT_INT        0x0800
/** RX interrupt is occured on frame count threshold */
#define   RXQ_ON_FRAME_CNT_INT       0x0400
/** Enable adding 2-bytes offset before IP frame header */
#define   RXQ_TWOBYTE_OFFSET         0x0200
/** Enable RX interrupt on timer duration */
#define   RXQ_EN_ON_TIME_INT         0x0080
/** Enable RX interrupt on byte count threshold */
#define   RXQ_EN_ON_BYTE_CNT_INT     0x0040
/** Enable RX interrupt on frame count threshold */
#define   RXQ_EN_ON_FRAME_CNT_INT    0x0020
/** Enable Auto Dequeue RXQ Frame */
#define   RXQ_AUTO_DEQUEUE           0x0010
/** Start QMU transfer operation */
#define   RXQ_START                  0x0008
/** Release RX Error Frame */
#define   RXQ_RELEASE_ERROR_FRAME    0x0001

/** RX COMMAND Initialization collection */
#define   RXQ_CMD_CONFIG             (RXQ_TWOBYTE_OFFSET |      \
                                      RXQ_EN_ON_FRAME_CNT_INT | \
                                      RXQ_AUTO_DEQUEUE)

/* Port 1 Status Register */
/** Auto-neg done */
#define PORT1_AN_DONE                 0x0040
/** Link good */
#define PORT1_LINK_GOOD               0x0020

/* Port 1 Control Register Options */
/** Turn off port LEDs */
#define   PORT1_LED_OFF               0x8000
/** Disable port transmit */
#define   PORT1_TX_DISABLE            0x4000
/** Restart auto-negotiation */
#define   PORT1_AUTO_NEG_RESTART      0x2000
/** Set port power-down */
#define   PORT1_POWER_DOWN            0x0800
/** Disable auto MDI/MDI-X */
#define   PORT1_AUTO_MDIX_DISABLE     0x0400
/** Force MDI-X */
#define   PORT1_FORCE_MDIX            0x0200
/** Enable auto-negotiation */
#define   PORT1_AUTO_NEG_ENABLE       0x0080
/** Force PHY 100Mbps */
#define   PORT1_FORCE_100_MBIT        0x0040
/** Force PHY in full duplex mode */
#define   PORT1_FORCE_FULL_DUPLEX     0x0020
/** Advertise flow control capability */
#define   PORT1_AUTO_NEG_SYM_PAUSE    0x0010
/** Advertise 100BT full-duplex capability */
#define   PORT1_AUTO_NEG_100BTX_FD    0x0008
/** Advertise 100BT half-duplex capability */
#define   PORT1_AUTO_NEG_100BTX       0x0004
/** Advertise 10BT full-duplex capability  */
#define   PORT1_AUTO_NEG_10BT_FD      0x0002
/** Advertise 10BT half-duplex capability  */
#define   PORT1_AUTO_NEG_10BT         0x0001

/* Global Reset Register Options */
/** QMU Reset */
#define QMU_MODULE_SOFT_RESET    0x0002
/** Global reset */
#define GLOBAL_SOFT_RESET        0x0001

/** PHY Reset Register Options */
#define PHY_RESET                0x0001

/* P1MBCR register */
/** Enable Digital loopback mode */
#define DIGITAL_LOOPBACK     0x4000
/** Force the speed to 100MBps */
#define FORCE_100            0x2000
/** Force auto negotiation */
#define AUTO_NEG             0x1000
/** Restart auto negotiation */
#define RESTART_AUTO_NEG     0x0200
/** Force full duplex */
#define FORCE_FULL_DUPLEX    0x0100

/* wait time in ms for TX memory to be available */
#define TX_MEMORY_WAIT_MS    500
/* wait time in ms for TX memory to be available */

/* Management information base registers */
#define MIB_MASK                    0x1C00       /**< MIB Mask */
#define MIB_RxByte                  0x00         /**< # of received bytes */
#define MIB_XXX                     0x01         /**< MIB Reserved byte */
#define MIB_RxUndersizePkt          0x02         /**< # of received undersized packets */
#define MIB_RxFragments             0x03         /**< # of received fragments */
#define MIB_RxOversize              0x04         /**< # of received oversized packets */
#define MIB_RxJabbers               0x05         /**< # of received jabbers */
#define MIB_RxSymbolError           0x06         /**< # of received error symbols */
#define MIB_RxCRCError              0x07         /**< # of received packets with CRC error */
#define MIB_RxAlignmentError        0x08         /**< # of received missaligned packets */
#define MIB_RxControl8808Pkts       0x09         /**< # of received control packets */
#define MIB_RxPausePkts             0x0A         /**< # of received pause packets */
#define MIB_RxBroadcast             0x0B         /**< # of received broadcast packets */
#define MIB_RxMulticast             0x0C         /**< # of received multicast packets */
#define MIB_RxUnicast               0x0D         /**< # of received unicast packets */
#define MIB_Rx64Octets              0x0E         /**< # of received packets with size of 64 bytes */
#define MIB_Rx65to127Octets         0x0F         /**< # of received packets with size between 65 and 127 bytes */
#define MIB_Rx128to255Octets        0x10         /**< # of received packets with size between 128 and 255 bytes */
#define MIB_Rx256to511Octets        0x11         /**< # of received packets with size between 256 and 511 bytes */
#define MIB_Rx512to1023Octets       0x12         /**< # of received packets with size between 512 and 1023 bytes */
#define MIB_Rx1024to1521Octets      0x13         /**< # of received packets with size between 1024 and 1521 bytes */
#define MIB_Rx1522to2000Octets      0x14         /**< # of received packets with size between 1522 and 2000 bytes */
#define MIB_TxByte                  0x15         /**< # of transmitted bytes */
#define MIB_TxLateCollision         0x16         /**< # of transmitted late collision packets */
#define MIB_TxPausePkts             0x17         /**< # of transmitted pause packets */
#define MIB_TxBroadcastPkts         0x18         /**< # of transmitted broadcast packets */
#define MIB_TxMulticastPkts         0x19         /**< # of transmitted multicast packets */
#define MIB_TxUnicastPkts           0x1A         /**< # of transmitted unicast packets */
#define MIB_TxDeferred              0x1B         /**< # of transmitted deferred packets */
#define MIB_TxTotalCollision        0x1C         /**< # of transmitted total collisions */
#define MIB_TxExcessiveCollision    0x1D         /**< # of transmitted excessive collisions */
#define MIB_TxSingleCollision       0x1E         /**< # of transmitted single collisions */
#define MIB_TxMultipleCollision     0x1F         /**< # of transmitted multiple collisions */

#define READ_UNSAFE_REGISTERS       0

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
static uint16_t frameId = 0;        /**< Raw ethernet frame sent over the network */
static uint8_t  macAddress[6];      /**< Unique MAC address */
static uint16_t rxFrameCount;
static uint32_t interrputCnt = 0;

static void     ReleaseIncosistentFrame(void);
static uint32_t MIBCountersRead(uint16_t offset);

/** @endcond */

KSZ8851SLN_mib_t mibCounters;

/***************************************************************************//**
 * @brief helper function for KSZ8851SNL_UpdateMIBCounters
 *****************************************************************************/
static uint32_t MIBCountersRead(uint16_t offset)
{
  uint16_t data, dataLow, dataHigh;
  uint32_t counter;

  data = MIB_MASK | offset;
  ETHSPI_WriteRegister(IND_ACC_CTRL_REG, 2, &data);
  ETHSPI_ReadRegister(IND_ACC_DATA_LOW_REG, 2, &dataLow);
  ETHSPI_ReadRegister(IND_ACC_DATA_HIGH_REG, 2, &dataHigh);
  counter = (dataHigh << 16) | (dataLow & 0x0000FFFF);

  return counter;
}

/***************************************************************************//**
 * @brief Update the Management Information Base Counters
 * @note  Support method used for debugging.
 *****************************************************************************/
void KSZ8851SNL_MIBCountersUpdate(void)
{
  mibCounters.RxByteCnt           += MIBCountersRead(MIB_RxByte);
  mibCounters.RxUndersizePktCnt   += MIBCountersRead(MIB_RxUndersizePkt);
  mibCounters.RxFragmentsCnt      += MIBCountersRead(MIB_RxFragments);
  mibCounters.RxOversizeCnt       += MIBCountersRead(MIB_RxOversize);
  mibCounters.RxJabbersCnt        += MIBCountersRead(MIB_RxJabbers);
  mibCounters.RxSymbolErrorCnt    += MIBCountersRead(MIB_RxSymbolError);
  mibCounters.RxCRCErrorCnt       += MIBCountersRead(MIB_RxCRCError);
  mibCounters.RxPausePktsCnt      += MIBCountersRead(MIB_RxPausePkts);
  mibCounters.RxBroadcastCnt      += MIBCountersRead(MIB_RxBroadcast);
  mibCounters.RxMulticastCnt      += MIBCountersRead(MIB_RxMulticast);
  mibCounters.RxUnicastCnt        += MIBCountersRead(MIB_RxUnicast);
  mibCounters.TxByteCnt           += MIBCountersRead(MIB_TxByte);
  mibCounters.TxPausePktsCnt      += MIBCountersRead(MIB_TxPausePkts);
  mibCounters.TxBroadcastPktsCnt  += MIBCountersRead(MIB_TxBroadcastPkts);
  mibCounters.TxMulticastPktsCnt  += MIBCountersRead(MIB_TxMulticastPkts);
  mibCounters.TxUnicastPktsCnt    += MIBCountersRead(MIB_TxUnicastPkts);
  mibCounters.TxDeferredCnt       += MIBCountersRead(MIB_TxDeferred);
  mibCounters.TxTotalCollisionCnt += MIBCountersRead(MIB_TxTotalCollision);
}

/***************************************************************************//**
 * @brief Dumps the Management Information Base Counters
 * @note  Support method used for debugging.
 *
 *****************************************************************************/
void KSZ8851SNL_MIBCountersDump(void)
{
  printf("####################### MIB COUNTER DUMP ########################\n");
  printf("MIB_RxByteCnt           = %lu\n", mibCounters.RxByteCnt);
  printf("MIB_RxUndersizePktCnt   = %lu\n", mibCounters.RxUndersizePktCnt);
  printf("MIB_RxFragmentsCnt      = %lu\n", mibCounters.RxFragmentsCnt);
  printf("MIB_RxOversizeCnt       = %lu\n", mibCounters.RxOversizeCnt);
  printf("MIB_RxJabbersCnt        = %lu\n", mibCounters.RxJabbersCnt);
  printf("MIB_RxSymbolErrorCnt    = %lu\n", mibCounters.RxSymbolErrorCnt);
  printf("MIB_RxCRCErrorCnt       = %lu\n", mibCounters.RxCRCErrorCnt);
  printf("MIB_RxPausePktsCnt      = %lu\n", mibCounters.RxPausePktsCnt);
  printf("MIB_RxBroadcastCnt      = %lu\n", mibCounters.RxBroadcastCnt);
  printf("MIB_RxMulticastCnt      = %lu\n", mibCounters.RxMulticastCnt);
  printf("MIB_RxUnicastCnt        = %lu\n", mibCounters.RxUnicastCnt);
  printf("MIB_TxByteCnt           = %lu\n", mibCounters.TxByteCnt);
  printf("MIB_TxPausePktsCnt      = %lu\n", mibCounters.TxPausePktsCnt);
  printf("MIB_TxBroadcastPktsCnt  = %lu\n", mibCounters.TxBroadcastPktsCnt);
  printf("MIB_TxMulticastPktsCnt  = %lu\n", mibCounters.TxMulticastPktsCnt);
  printf("MIB_TxUnicastPktsCnt    = %lu\n", mibCounters.TxUnicastPktsCnt);
  printf("MIB_TxDeferredCnt       = %lu\n", mibCounters.TxDeferredCnt);
  printf("MIB_TxTotalCollisionCnt = %lu\n", mibCounters.TxTotalCollisionCnt);
  printf("#################################################################\n");
}

/***************************************************************************//**
 * @brief Prints the value of the registers of the ethernet controller.
 * @note  Support method used for debugging.
 *****************************************************************************/
void KSZ8851SNL_AllRegistersDump(void)
{
  uint16_t data;

  printf("###################### ALL REGISTER DUMP ########################\n");
  int i;
  for (i = 0x00; i < 0xFF; i += 0x02)
  {
    if ((i % 8 == 0) && (i > 0))
    {
      printf("\n");
    }
    ETHSPI_ReadRegister(i, 2, &data);
    printf("REG[0x%02X]=0x%04X ", i, data);
  }
  printf("\n");
  printf("#################################################################\n");
}

/***************************************************************************//**
 * @brief Prints the value of the registers of the ethernet controller.
 * @note  Support method used for debugging.
 *****************************************************************************/
void KSZ8851SNL_RegistersDump(void)
{
  uint16_t data;

  printf("##################### SPECIAL REGISTER DUMP ######################\n");
  ETHSPI_ReadRegister(LOW_QMU_MAC_REG, 2, &data);
  printf("LOW_QMU_MAC_REG    REG[0x%02X]=0x%04X\n", LOW_QMU_MAC_REG, data);
  ETHSPI_ReadRegister(MID_QMU_MAC_REG, 2, &data);
  printf("MID_QMU_MAC_REG    REG[0x%02X]=0x%04X\n", MID_QMU_MAC_REG, data);
  ETHSPI_ReadRegister(HIGH_QMU_MAC_REG, 2, &data);
  printf("HIGH_QMU_MAC_REG   REG[0x%02X]=0x%04X\n", HIGH_QMU_MAC_REG, data);
  ETHSPI_ReadRegister(OBC_REG, 2, &data);
  printf("OBC_REG            REG[0x%02X]=0x%04X\n", OBC_REG, data);
  ETHSPI_ReadRegister(GLOBAL_RESET_REG, 2, &data);
  printf("GLOBAL_RESET_REG   REG[0x%02X]=0x%04X\n", GLOBAL_RESET_REG, data);
  ETHSPI_ReadRegister(TX_FLOW_CTRL_REG, 2, &data);
  printf("TX_FLOW_CTRL_REG   REG[0x%02X]=0x%04X\n", TX_FLOW_CTRL_REG, data);
  ETHSPI_ReadRegister(RX_FLOW_CTRL1_REG, 2, &data);
  printf("RX_FLOW_CTRL1_REG  REG[0x%02X]=0x%04X\n", RX_FLOW_CTRL1_REG, data);
  ETHSPI_ReadRegister(RX_FLOW_CTRL2_REG, 2, &data);
  printf("RX_FLOW_CTRL2_REG  REG[0x%02X]=0x%04X\n", RX_FLOW_CTRL2_REG, data);
  ETHSPI_ReadRegister(TX_MEM_INFO_REG, 2, &data);
  printf("TX_MEM_INFO_REG    REG[0x%02X]=0x%04X\n", TX_MEM_INFO_REG, data);
#if (READ_UNSAFE_REGISTERS)
  ETHSPI_ReadRegister(RX_FRH_STAT_REG, 2, &data);
  printf("RX_FRH_STAT_REG    REG[0x%02X]=0x%04X\n", RX_FRH_STAT_REG, data);
#endif
  ETHSPI_ReadRegister(TXQ_CMD_REG, 2, &data);
  printf("TXQ_CMD_REG        REG[0x%02X]=0x%04X\n", TXQ_CMD_REG, data);
  ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &data);
  printf("RXQ_CMD_REG        REG[0x%02X]=0x%04X\n", RXQ_CMD_REG, data);
  ETHSPI_ReadRegister(TX_FD_PTR_REG, 2, &data);
  printf("TX_FD_PTR_REG      REG[0x%02X]=0x%04X\n", TX_FD_PTR_REG, data);
  ETHSPI_ReadRegister(RX_FD_PTR_REG, 2, &data);
  printf("RX_FD_PTR_REG      REG[0x%02X]=0x%04X\n", RX_FD_PTR_REG, data);
  ETHSPI_ReadRegister(INT_ENABLE_REG, 2, &data);
  printf("INT_ENABLE_REG     REG[0x%02X]=0x%04X\n", INT_ENABLE_REG, data);
  ETHSPI_ReadRegister(INT_STATUS_REG, 2, &data);
  printf("INT_STATUS_REG     REG[0x%02X]=0x%04X\n", INT_STATUS_REG, data);
  ETHSPI_ReadRegister(RX_FRAME_THRES_REG, 2, &data);
  printf("RX_FRAME_THRES_REG REG[0x%02X]=0x%04X\n", RX_FRAME_THRES_REG, data);
#if (READ_UNSAFE_REGISTERS)
  ETHSPI_ReadRegister(TX_NEXT_FRS_REG, 2, &data);
  printf("TX_NEXT_FRS_REG    REG[0x%02X]=0x%04X\n", TX_NEXT_FRS_REG, data);
#endif
  ETHSPI_ReadRegister(CIDER_REG, 2, &data);
  printf("CIDER_REG          REG[0x%02X]=0x%04X\n", CIDER_REG, data);
  ETHSPI_ReadRegister(PHY_RST_REG, 2, &data);
  printf("PHY_RST_REG        REG[0x%02X]=0x%04X\n", PHY_RST_REG, data);
  ETHSPI_ReadRegister(PHY1_CTRL_REG, 2, &data);
  printf("PHY1_CTRL_REG      REG[0x%02X]=0x%04X\n", PHY1_CTRL_REG, data);
  ETHSPI_ReadRegister(PORT1_CTRL_REG, 2, &data);
  printf("PORT1_CTRL_REG     REG[0x%02X]=0x%04X\n", PORT1_CTRL_REG, data);
  printf("#################################################################\n");
}

/**************************************************************************//**
 * @brief enables the chip interrupts
 *****************************************************************************/
void KSZ8851SNL_InteruptsEnable(void)
{
  uint16_t data;

  if (interrputCnt)
  {
    interrputCnt--;
  }
  if (interrputCnt == 0)
  {
    /* Enable interrupts */
    data = KSZ8851SNL_INT_ENABLE_MASK;
    ETHSPI_WriteRegister(INT_ENABLE_REG, 2, &data);
  }
}

/**************************************************************************//**
 * @brief disables the chip interrupts
 *****************************************************************************/
void KSZ8851SNL_InteruptsDisable(void)
{
  uint16_t data;

  data = NO_INT;
  ETHSPI_WriteRegister(INT_ENABLE_REG, 2, &data);
  interrputCnt++;
}

/**************************************************************************//**
 * @brief clear interrupts
 *****************************************************************************/
void KSZ8851SNL_ISRStatusW1Clear(uint16_t mask)
{
  ETHSPI_WriteRegister(INT_STATUS_REG, 2, &mask);
}

/**************************************************************************//**
 * @brief PMECR flags
 *****************************************************************************/
void KSZ8851SNL_PMECRStatusRWClear(uint16_t mask)
{
  uint16_t status;

  ETHSPI_ReadRegister(PMECR_REG, 2, &status);
  status |= mask;
  ETHSPI_WriteRegister(PMECR_REG, 2, &status);
}

/**************************************************************************//**
 * @brief Get interrupts
 *****************************************************************************/
uint16_t KSZ8851SNL_ISRStatusGet(void)
{
  uint16_t ISR_stat;

  ETHSPI_ReadRegister(INT_STATUS_REG, 2, &ISR_stat);
  return ISR_stat;
}


/**************************************************************************//**
 * @brief Get RXQCR register
 *****************************************************************************/
uint16_t KSZ8851SNL_RXQCRGet(void)
{
  uint16_t data;

  ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &data);
  return data;
}

/**************************************************************************//**
 * @brief FrameCounter
 *****************************************************************************/
void KSZ8851SNL_FrameCounterSet(void)
{
  uint16_t rxftr;

  /* Read the frame count and threshold register */
  ETHSPI_ReadRegister(RX_FRAME_THRES_REG, 2, &rxftr);
  /* Extract the actual number of frames from RX_FRAME_THRES_REG*/
  rxFrameCount = rxftr >> MSB_POS;
}

/**************************************************************************//**
 * @brief Reset TxQueue
 *****************************************************************************/
void KSZ8851SNL_TxQueueReset(void)
{
  uint16_t data;

  ETHSPI_ReadRegister(TX_FLOW_CTRL_REG, 2, &data);
  /* Disable TX */
  data &= ~TX_FLOW_CTRL_ENABLE;
  ETHSPI_WriteRegister(TX_FLOW_CTRL_REG, 2, &data);
  /* Flush */
  data |= TX_FLOW_CTRL_FLUSH_QUEUE;
  ETHSPI_WriteRegister(TX_FLOW_CTRL_REG, 2, &data);
  /* normal op - no flush */
  data &= ~TX_FLOW_CTRL_FLUSH_QUEUE;
  ETHSPI_WriteRegister(TX_FLOW_CTRL_REG, 2, &data);
  /* Enable TX */
  data |= TX_FLOW_CTRL_ENABLE;
  ETHSPI_WriteRegister(TX_FLOW_CTRL_REG, 2, &data);
}

/**************************************************************************//**
 * @brief Reset RxQueue
 *****************************************************************************/
void KSZ8851SNL_RxQueueReset(void)
{
  uint16_t data;

  ETHSPI_ReadRegister(RX_FLOW_CTRL1_REG, 2, &data);
  /* Disable RX */
  data &= ~RX_FLOW_CTRL_RX_ENABLE;
  ETHSPI_WriteRegister(RX_FLOW_CTRL1_REG, 2, &data);
  /* Flush */
  ETHSPI_WriteRegister(RX_FLOW_CTRL1_REG, 2, &data);
  /* Clear flush */
  data &= ~RX_FLOW_CTRL_FLUSH_QUEUE;
  ETHSPI_WriteRegister(RX_FLOW_CTRL1_REG, 2, &data);
  /* Write default config with enable set */
  data |= RX_FLOW_CTRL_RX_ENABLE;
  ETHSPI_WriteRegister(RX_FLOW_CTRL1_REG, 2, &data);

  /* Re-enable interrupts */
  data = KSZ8851SNL_INT_ENABLE_MASK;
  ETHSPI_WriteRegister(INT_ENABLE_REG, 2, &data);
}

/**************************************************************************//**
 * @brief FrameCounter
 *****************************************************************************/
uint16_t KSZ8851SNL_FrameCounterGet(void)
{
  return rxFrameCount;
}


/***************************************************************************//**
 * @brief Initialize the registers of the ethernet controller.
 *****************************************************************************/
void KSZ8851SNL_Init(void)
{
  uint16_t data;
  int      i;

  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Init: started \n"));
  /* Initialize SPI Interface */
  ETHSPI_Init();

  /* Reset PHY module */
  data = PHY_RESET;
  ETHSPI_WriteRegister(PHY_RST_REG, 2, &data);

  /* Reset Soft (clear registers of PHY, MAC, QMU, DMA) */
  ETHSPI_ReadRegister(GLOBAL_RESET_REG, 2, &data);
  data &= ~GLOBAL_SOFT_RESET;
  ETHSPI_WriteRegister(GLOBAL_RESET_REG, 2, &data);

  /* Reset Soft (clear registers of PHY, MAC, QMU, DMA) */
  ETHSPI_ReadRegister(GLOBAL_RESET_REG, 2, &data);
  data &= ~GLOBAL_SOFT_RESET;
  ETHSPI_WriteRegister(GLOBAL_RESET_REG, 2, &data);

  /* Read the chip ID and check if that is correct */
  ETHSPI_ReadRegister(CIDER_REG, 2, &data);

  /* The CIDER lower bits [3..1] are defined as revision number,
   *   thus a mask needs to be applied
   */

  /* LWIP_ASSERT might be soft - not blocking */
  LWIP_ASSERT("KSZ8851SNL_Init: Incorrect Device ID", ((data & CHIP_ID_MASK) == KSZ8851SNL_CHIP_ID));
  /* this is a hard assert - abort  */
  EFM_ASSERT((data & CHIP_ID_MASK) == KSZ8851SNL_CHIP_ID);

  /* Write the Queue Management Unit MAC Address */
  KSZ8851SNL_MacAddressGet(macAddress);
  /* Write the appropriate KSZ8851SNL MAC registers
   *   starting from the HIGH part towards the lower one
   *   going with a step of 2
   */
  for (i = 0; (i < 6); i += 2)
  {
    data = (macAddress[i] << MSB_POS) | macAddress[i + 1];
    ETHSPI_WriteRegister(HIGH_QMU_MAC_REG - i, 2, &data);
  }

  /* Enable QMU Transmit Frame Data Pointer Auto Increment */
  data = FD_PTR_AUTO_INC;
  ETHSPI_WriteRegister(TX_FD_PTR_REG, 2, &data);

  /* Enable QMU Transmit:
   *  flow control,
   *  padding,
   *  CRC,
   *  IP/TCP/UDP/ICMP checksum generation.
   */
  data = TX_FLOW_CTRL_CONFIG;
  ETHSPI_WriteRegister(TX_FLOW_CTRL_REG, 2, &data);

  /* Enable QMU Receive Frame Data Pointer Auto Increment */
  data = FD_PTR_AUTO_INC;
  ETHSPI_WriteRegister(RX_FD_PTR_REG, 2, &data);

  /* Configure Receive Frame Threshold for one frame */
  data = 1;
  ETHSPI_WriteRegister(RX_FRAME_THRES_REG, 2, &data);

  /* Set RX queue low watermark to 10240 bytes for issuing of
     stop PAUSE frames (flow control) */
  data = 0xA00;
  ETHSPI_WriteRegister(FLOW_CTRL_LOW_WATERMARK, 2 , &data);

  /* Enable QMU Receive:
   *  flow control,
   *  receive all broadcast frame,
   *  receive unicast frame,
   *  IP/TCP/UDP/ICMP checksum generation.
   */
  data = RX_FLOW_CTRL1_CONFIG;
  ETHSPI_WriteRegister(RX_FLOW_CTRL1_REG, 2, &data);

  /* Enable QMU Receive:
   *  ICMP/UDP Lite frame checksum verification,
   *  UDP Lite frame checksum generation,
   *  IPv6 UDP fragment frame pass.
   */
  data = RX_FLOW_CTRL2_CONFIG;
  ETHSPI_WriteRegister(RX_FLOW_CTRL2_REG, 2, &data);

  /* Enable QMU Receive:
   *  IP Header Two-Byte Offset,
   *  Receive Frame Count Threshold,
   *  RXQ Auto-Dequeue frame.
   */
  data = RXQ_CMD_CONFIG;
  ETHSPI_WriteRegister(RXQ_CMD_REG, 2, &data);

  /* Restart Port 1 auto-negotiation */
  ETHSPI_ReadRegister(PORT1_CTRL_REG, 2, &data);
  /* Advertise 10MBIT full duplex with flow control. */
  data &= ~(0x6D);
  data |= PORT1_AUTO_NEG_RESTART;
  ETHSPI_WriteRegister(PORT1_CTRL_REG, 2, &data);

  ETHSPI_ReadRegister(P1SR_REG, 2, &data);
  while (!(data & PORT1_AN_DONE)) {
    ETHSPI_ReadRegister(P1SR_REG, 2, &data);
  }

  if (!(data & PORT1_LINK_GOOD))
  {
    LWIP_DEBUGF(NETIF_DEBUG | DBG_3, ("KSZ8851SNL_Init: AN failed.\n"));
  }

  /* Clear interrupts */
  data = CLEAR_INT;
  ETHSPI_WriteRegister(INT_STATUS_REG, 2, &data);

  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Init: ended \n"));
}


/***************************************************************************//**
 * @brief Enable RX and TX
 *****************************************************************************/
void KSZ8851SNL_Enable(void)
{
  uint16_t data;

  data = KSZ8851SNL_INT_ENABLE_MASK;
  ETHSPI_WriteRegister(INT_ENABLE_REG, 2, &data);

  /* Enable QMU Transmit */
  ETHSPI_ReadRegister(TX_FLOW_CTRL_REG, 2, &data);
  data |= TX_FLOW_CTRL_ENABLE;
  ETHSPI_WriteRegister(TX_FLOW_CTRL_REG, 2, &data);

  /* Enable QMU Receive */
  ETHSPI_ReadRegister(RX_FLOW_CTRL1_REG, 2, &data);
  data |= RX_FLOW_CTRL_RX_ENABLE;
  ETHSPI_WriteRegister(RX_FLOW_CTRL1_REG, 2, &data);
}


/***************************************************************************//**
 * @brief Performs the initialisation of the transmission of a long raw frame
 *        over the network.
 *
 * @param pTXLength
 *     the length of the transmitted frame
 *****************************************************************************/
bool KSZ8851SNL_LongTransmitInit(uint16_t TXLength)
{
  uint16_t txmir;
  uint16_t data, reqSize;
  uint8_t  outbuf[4];

  reqSize = TXLength + 12; /* ToDo: 4 + 4 + 4 - Figure out if it is with CRC  ? */
  ETHSPI_ReadRegister(TX_MEM_INFO_REG, 2, &data);
  txmir = data & TX_MEM_AVAIL_MASK;
  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_LongTransmitInit: txmir =%hu  reqSize = %hu \n", txmir, reqSize));

  if (txmir < reqSize)
  {
    /* PHY is out of memory */
    return false;
  }

  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_LongTransmitInit: Memory available >  txmir =%hu  reqSize = %hu \n", txmir, reqSize));
  /* Enable TXQ write access */
  ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &data);
  data |= RXQ_START;
  ETHSPI_WriteRegister(RXQ_CMD_REG, 2, &data);

  /* Write frame ID, control word and byte count */
  outbuf[0] = (frameId++ & FRAME_ID_MASK);
  outbuf[1] = 0x80; /*  TX_INT_on_COMPLETION */
  outbuf[2] = TXLength & LSB_MASK;
  outbuf[3] = TXLength >> MSB_POS;

  /* Start the SPI Transfer */
  ETHSPI_StartWriteFIFO();
  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_LongTransmitInit: frameHeader =0x%02X|0x%02X|0x%02X|0x%02X \n", outbuf[0], outbuf[1], outbuf[2], outbuf[3]));
  /* Send the frame header info */
  ETHSPI_WriteFifoContinue(4, outbuf);
  return true;
}


/***************************************************************************//**
 * @brief Performs the actual transmission of a long raw frame over the network.
 *
 * @param pTXLength
 *     the length of the transmitted frame
 * @param pTXData
 *     the data of the transmitted frame
 *****************************************************************************/
void KSZ8851SNL_LongTransmit(uint16_t TXLength, uint8_t *pTXData)
{
  EFM_ASSERT(pTXData != NULL);
  /* Send the actual data */
  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_LongTransmit: pTXLength=%hu \n", TXLength));
  ETHSPI_WriteFifoContinue(TXLength, pTXData);
}


/***************************************************************************//**
 * @brief Performs the clean up procedures after the transmission of a long raw
 *        frame over the network.
 *
 * @param pTXLength
 *     the length of the transmitted frame
 * @param pTXData
 *     the data of the transmitted frame
 *****************************************************************************/
void KSZ8851SNL_LongTransmitEnd(uint16_t TXLength, uint8_t *pTXData)
{
  EFM_ASSERT(pTXData != NULL);

  uint16_t data, extraBytes;

  /* calculate extra bytes to have number of bytes to write at double word boundary */
  if (TXLength % 4)
  {
    extraBytes = 4 - (TXLength % 4);
  }
  else
  {
    extraBytes = 0;
  }

  /* Send dummy bytes to align data to DWORD  */
  ETHSPI_WriteFifoContinue(extraBytes, pTXData);

  /* Stop the SPI Transfer */
  ETHSPI_StopFIFO();

  /* Disable TXQ write access */
  ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &data);
  data &= ~RXQ_START;
  ETHSPI_WriteRegister(RXQ_CMD_REG, 2, &data);

  /* Start TXQ Manual enqueue */
  ETHSPI_ReadRegister(TXQ_CMD_REG, 2, &data);
  data |= TXQ_ENQUEUE;
  ETHSPI_WriteRegister(TXQ_CMD_REG, 2, &data);
  /* Wait until transmit command clears */
  while (1)
  {
    ETHSPI_ReadRegister(TXQ_CMD_REG, 2, &data);
    if (!(data & TXQ_ENQUEUE))
      break;
  }
  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_LongTransmitEnd: TXQ_CMD_REG =0x%04X \n", data));
}


/***************************************************************************//**
 * @brief Realease the current frame if it is inconsistent.
 * @note  Support method used for minimizing the code size.
 *****************************************************************************/
static void ReleaseIncosistentFrame(void)
{
  uint16_t data;
  /* Issue the Release error frame command */
  ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &data);
  data |= RXQ_RELEASE_ERROR_FRAME;
  ETHSPI_WriteRegister(RXQ_CMD_REG, 2, &data);

  /* Wait for PHY to clear the command/flag */
  while (data & RXQ_RELEASE_ERROR_FRAME)
  {
    ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &data);
  }

  LWIP_DEBUGF(NETIF_DEBUG | DBG_2, ("ReleaseIncosistentFrame: frame is inconsistent - dropped !!!\n"));
}

/***************************************************************************//**
 * @brief Performs the actual receive of a raw frame over the network.
 *
 * @param pRXLength
 *     the length of the received frame
 * @param bufferLength
 *     size of allocated frame
 *
 * @return
 *     received packet length, 0 in case of failure
 *****************************************************************************/
uint16_t KSZ8851SNL_Receive(uint8_t *pRXData, uint16_t bufferLength)
{
  uint16_t data;
  uint16_t rxStatus;
  uint16_t rxPacketLength;
  uint16_t frameLength;
  uint16_t bytesToRead;
  uint16_t offsetSetFlag;

  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Receive: ENTER\n"));
  EFM_ASSERT(pRXData != NULL);

  /* read the RXIPHTOE - 2 bytes offset flag */
  ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &offsetSetFlag);
  offsetSetFlag &= RXQ_TWOBYTE_OFFSET;

  while (rxFrameCount > 0)
  {
    rxFrameCount--;
    /* Read the received frame status */
    ETHSPI_ReadRegister(RX_FRH_STAT_REG, 2, &rxStatus);

    /* Check the consistency of the frame */
    if ((!(rxStatus & VALID_FRAME_MASK)) || (rxStatus & CHECKSUM_VALID_FRAME_MASK))
    {
      /* Issue the Release error frame command */
      ReleaseIncosistentFrame();
      /* continue to next frame */
      continue;
    }
    else
    {
      /* Read the byte size of the received frame */
      ETHSPI_ReadRegister(RX_FRH_BC_REG, 2, &rxPacketLength);
      rxPacketLength &= RX_BYTE_CNT_MASK;
      /* round to dword boundary */
      bytesToRead = 4 * ((rxPacketLength + 3) >> 2);
      LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Receive: rxPacketLength=%u, bytesToRead=%u \n", rxPacketLength, bytesToRead));
      if ((bytesToRead > bufferLength) || (rxPacketLength <= 4))
      {
        /* Issue the Release error frame command */
        ReleaseIncosistentFrame();
        /* continue to next frame */
        continue;
      }
      /* Reset QMU RXQ frame pointer to zero */
      data = FD_PTR_AUTO_INC;
      ETHSPI_WriteRegister(RX_FD_PTR_REG, 2, &data);

      /* Start QMU DMA transfer */
      ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &data);
      data |= RXQ_START;
      ETHSPI_WriteRegister(RXQ_CMD_REG, 2, &data);

      /* Start the SPI transfer */
      ETHSPI_StartReadFIFO();
      /* skip 4 bytes- dummy */
      ETHSPI_ReadFifoContinue(2, (uint8_t *) &data);
      ETHSPI_ReadFifoContinue(2, (uint8_t *) &data);
      ETHSPI_ReadFifoContinue(2, (uint8_t *) &data);
      LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Receive: StatusWord=0x%04X \n", data));
      ETHSPI_ReadFifoContinue(2, (uint8_t *) &data);
      LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Receive: ByteCount=%hu \n", data));
      /* offset will not land in the buffer anyway */
      if (offsetSetFlag)
      {
        ETHSPI_ReadFifoContinue(2, (uint8_t *) &data);
        LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Receive: 2 bytes offset data=0x%04X\n", data));
        bytesToRead -= 2;
      }
      /* Read raw frame without header and offset  */
      ETHSPI_ReadFifoContinue(bytesToRead, pRXData);
      /* Stoping the SPI transfer */
      ETHSPI_StopFIFO();
      /* Stop QMU DMA transfer */
      ETHSPI_ReadRegister(RXQ_CMD_REG, 2, &data);
      data &= ~RXQ_START;
      ETHSPI_WriteRegister(RXQ_CMD_REG, 2, &data);
      if (offsetSetFlag)
      {
        /* without offset and CRC */
        frameLength = rxPacketLength - 6;
      }
      else
      {
        /* without CRC */
        frameLength = rxPacketLength - 4;
      }
      LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Receive: EXIT with len= %u\n", frameLength));
      return frameLength;
    }
  }
  LWIP_DEBUGF(NETIF_DEBUG, ("KSZ8851SNL_Receive: EXIT with no frame  len=0 \n"));
  return 0;
}

/***************************************************************************//**
 * @brief Get the MAC address of the current board.
 * @note  Support method used for minimizing the code size.
 * Todo:  Get MAC based on actual MAC and not on the CMU unique ID
 * @param[out] macAddress
 *     data buffer to store the macAddress
 *****************************************************************************/
void KSZ8851SNL_MacAddressGet(uint8_t *macAddress)
{
  int i;

  EFM_ASSERT(macAddress != NULL);

  /* set the first 3 bytes given by the EM MAC Address space */
  macAddress[0] = HIGH_QMU_MAC_H;
  macAddress[1] = HIGH_QMU_MAC_L;
  macAddress[2] = MID_QMU_MAC_H;
  /* set the next 3 bytes given by the CMU unique ID */

  for (i = 0; i < 3; i++)
  {
    macAddress[5 - i] = (DEVINFO->UNIQUEL & (BYTE_MASK << i * BYTE_SIZE)) >> i * BYTE_SIZE;
  }
}

/***************************************************************************//**
 * @brief Get the PHY status
 *****************************************************************************/
uint16_t KSZ8851SNL_PHYStatusGet(void)
{
  uint16_t data;

  ETHSPI_ReadRegister(P1SR_REG, 2, &data);
  return(data);
}

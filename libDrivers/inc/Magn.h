/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : LSM303DLHC.h
* Author             : MSH Application Team
* Author             : Fabio Tota
* Version            : $Revision:$
* Date               : $Date:$
* Description        : LSM303D driver file
*
* HISTORY:
* Date               |	Modification                    |	Author
* 02/08/2011         |	Initial Revision                |	abio Tota
* 07/03/2015		|	Modified to LSM303D 			|   Peng Zhang
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOFTWARE IS SPECIFICALLY DESIGNED FOR EXCLUSIVE USE WITH ST PARTS.
*
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LSM303DLHC_DRIVER__H
#define __LSM303DLHC_DRIVER__H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

//these could change accordingly with the architecture
typedef unsigned char u8_t;
typedef unsigned short int u16_t;
typedef short int i16_t;
typedef u8_t IntPinConf_t;
typedef u8_t Axis_t;
typedef u8_t IntConf_t;

typedef enum {
  MEMS_SUCCESS                  =		0x01,
  MEMS_ERROR			=		0x00
} status_t;

typedef enum {
  MEMS_ENABLE			=		0x01,
  MEMS_DISABLE			=		0x00
} State_t;

typedef enum {
  ODR_1Hz		        =		0x01,
  ODR_10Hz                      =		0x02,
  ODR_25Hz		        =		0x03,
  ODR_50Hz		        =		0x04,
  ODR_100Hz		        =		0x05,
  ODR_200Hz		        =		0x06,
  ODR_400Hz		        =		0x07,
  ODR_1620Hz_LP		        =		0x08,
  ODR_1344Hz_NP_5367HZ_LP       =		0x09
} ODR_t;

typedef enum {
  ODR_0_75Hz_M		        =		0x00,
  ODR_1_5Hz_M                   =		0x01,
  ODR_3_0Hz_M		        =		0x02,
  ODR_7_5Hz_M		        =		0x03,
  ODR_15Hz_M		        =		0x04,
  ODR_30Hz_M		        =		0x05,
  ODR_75Hz_M		        =		0x06,
  ODR_220Hz_M		        =		0x07
} ODR_M_t;

typedef enum {
  GAIN_1100_M		        =		0x01,
  GAIN_855_M                    =		0x02,
  GAIN_670_M		        =		0x03,
  GAIN_450_M		        =		0x04,
  GAIN_400_M		        =		0x05,
  GAIN_330_M		        =		0x06,
  GAIN_230_M		        =		0x07
} GAIN_M_t;

typedef enum {
  CONTINUOUS_MODE               =		0x00,
  SINGLE_MODE 			=		0x01,
  SLEEP_MODE			=		0x02
} Mode_M_t;

typedef enum {
  POWER_DOWN                    =		0x00,
  LOW_POWER 			=		0x01,
  NORMAL			=		0x02
} Mode_t;

typedef enum {
  HPM_NORMAL_MODE_RES           =               0x00,
  HPM_REF_SIGNAL                =               0x01,
  HPM_NORMAL_MODE               =               0x02,
  HPM_AUTORESET_INT             =               0x03
} HPFMode_t;

typedef enum {
  HPFCF_0                       =               0x00,
  HPFCF_1                       =               0x01,
  HPFCF_2                       = 		0x02,
  HPFCF_3                       =               0x03
} HPFCutOffFreq_t;

typedef struct {
  i16_t AXIS_X;
  i16_t AXIS_Y;
  i16_t AXIS_Z;
} AccAxesRaw_t;

typedef struct {
  i16_t AXIS_X;
  i16_t AXIS_Y;
  i16_t AXIS_Z;
}MagAxesRaw_t;

typedef enum {
  FULLSCALE_2                   =               0x00,
  FULLSCALE_4                   =               0x01,
  FULLSCALE_8                   =               0x02,
  FULLSCALE_16                  =               0x03
} Fullscale_t;

typedef enum {
  BLE_LSB			=		0x00,
  BLE_MSB			=		0x01
} Endianess_t;

typedef enum {
  SELF_TEST_DISABLE             =               0x00,
  SELF_TEST_0                   =               0x01,
  SELF_TEST_1                   =               0x02
} SelfTest_t;

typedef enum {
  FIFO_BYPASS_MODE              =               0x00,
  FIFO_MODE                     =               0x01,
  FIFO_STREAM_MODE              =               0x02,
  FIFO_TRIGGER_MODE             =               0x03,
  FIFO_DISABLE                  =               0x04
} FifoMode_t;

typedef enum {
  TRIG_INT1                     =		0x00,
  TRIG_INT2 			=		0x01
} TrigInt_t;

typedef enum {
  SPI_4_WIRE                    =               0x00,
  SPI_3_WIRE                    =               0x01
} SPIMode_t;

typedef enum {
  X_ENABLE                      =               0x01,
  X_DISABLE                     =               0x00,
  Y_ENABLE                      =               0x02,
  Y_DISABLE                     =               0x00,
  Z_ENABLE                      =               0x04,
  Z_DISABLE                     =               0x00
} AXISenable_t;

typedef enum {
  INT1_6D_4D_DISABLE            =               0x00,
  INT1_6D_ENABLE                =               0x01,
  INT1_4D_ENABLE                =               0x02
} INT_6D_4D_t;

typedef enum {
  UP_SX                         =               0x44,
  UP_DX                         =               0x42,
  DW_SX                         =               0x41,
  DW_DX                         =               0x48,
  TOP                           =               0x60,
  BOTTOM                        =               0x50
} POSITION_6D_t;

typedef enum {
  INT_MODE_OR                   =               0x00,
  INT_MODE_6D_MOVEMENT          =               0x01,
  INT_MODE_AND                  =               0x02,
  INT_MODE_6D_POSITION          =               0x03
} Int1Mode_t;








#define	I2C_AUTO_INCREMENT	(0x80)
#define MS_TO_NS(x)		(x*1000000L)

#define	ACC_G_MAX_POS		1495040	/** max positive value acc [ug] */
#define	ACC_G_MAX_NEG		1495770	/** max negative value acc [ug] */
#define	MAG_G_MAX_POS		983520	/** max positive value mag [ugauss] */
#define	MAG_G_MAX_NEG		983040	/** max negative value mag [ugauss] */

#define FUZZ			0
#define FLAT			0

/* Address registers */
#define REG_WHOAMI_ADDR		(0x0F)	/** Who am i address register */
#define REG_CNTRL0_ADDR		(0x1F)	/** CNTRL0 address register */
#define REG_CNTRL1_ADDR		(0x20)	/** CNTRL1 address register */
#define REG_CNTRL2_ADDR		(0x21)	/** CNTRL2 address register */
#define REG_CNTRL3_ADDR		(0x22)	/** CNTRL3 address register */
#define REG_CNTRL4_ADDR		(0x23)	/** CNTRL4 address register */
#define REG_CNTRL5_ADDR		(0x24)	/** CNTRL5 address register */
#define REG_CNTRL6_ADDR		(0x25)	/** CNTRL6 address register */
#define REG_CNTRL7_ADDR		(0x26)	/** CNTRL7 address register */

#define REG_ACC_DATA_ADDR	(0x28)	/** Acc. data low address register */
#define REG_MAG_DATA_ADDR	(0x08)	/** Mag. data low address register */
#define REG_TEMP_DATA_ADDR	(0x05)	/** Temp. data low address register */

#define REG_GEN_MAG_ADDR	(0x12)	/** INT_CTRL_REG_M address register */
#define INT_SRC_REG_M_ADDR	(0x13)	/** INT_SRC_REG_M address register */
#define REG_GEN_MAG_THR_ADDR	(0x14)	/** INT_THS_L_M address register */
#define MIG_THRESHOLD_ADDR_H	(0x15)	/** INT_THS_H_M address register */
#define REG_GEN1_AXIS_ADDR	(0x30)	/** INT_GEN1_REG address register */
#define INT_GEN1_SRC_ADDR	(0x31)	/** INT_GEN1_SRC address register */
#define REG_GEN1_THR_ADDR	(0x32)	/** INT_GEN1_THS address register */
#define REG_GEN1_DUR_ADDR	(0x33)	/** INT_GEN1_DUR address register */
#define REG_GEN2_AXIS_ADDR	(0x34)	/** INT_GEN2_REG address register */
#define INT_GEN2_SRC_ADDR	(0x35)	/** INT_GEN2_SRC address register */
#define REG_GEN2_THR_ADDR	(0x36)	/** INT_GEN2_THS address register */
#define REG_GEN2_DUR_ADDR	(0x37)	/** INT_GEN2_DUR address register */

/* Sensitivity */
#define SENSITIVITY_ACC_2G	60	/**	ug/LSB	*/
#define SENSITIVITY_ACC_4G	120	/**	ug/LSB	*/
#define SENSITIVITY_ACC_8G	240	/**	ug/LSB	*/
#define SENSITIVITY_ACC_16G	730	/**	ug/LSB	*/

#define SENSITIVITY_MAG_2G	80	/**	ugauss/LSB	*/
#define SENSITIVITY_MAG_4G	160	/**	ugauss/LSB	*/
#define SENSITIVITY_MAG_8G	320	/**	ugauss/LSB	*/
#define SENSITIVITY_MAG_12G	480	/**	ugauss/LSB	*/

/* ODR */
#define ODR_ACC_MASK		(0XF0)	/* Mask for odr change on acc */
#define LSM303D_ACC_ODR_OFF	(0x00)  /* Power down */
#define LSM303D_ACC_ODR3_125	(0x10)  /* 3.25Hz output data rate */
#define LSM303D_ACC_ODR6_25	(0x20)  /* 6.25Hz output data rate */
#define LSM303D_ACC_ODR12_5	(0x30)  /* 12.5Hz output data rate */
#define LSM303D_ACC_ODR25	(0x40)  /* 25Hz output data rate */
#define LSM303D_ACC_ODR50	(0x50)  /* 50Hz output data rate */
#define LSM303D_ACC_ODR100	(0x60)  /* 100Hz output data rate */
#define LSM303D_ACC_ODR200	(0x70)  /* 200Hz output data rate */
#define LSM303D_ACC_ODR400	(0x80)  /* 400Hz output data rate */
#define LSM303D_ACC_ODR800	(0x90)  /* 800Hz output data rate */
#define LSM303D_ACC_ODR1600	(0xA0)  /* 1600Hz output data rate */

#define ODR_MAG_MASK		(0X1C)	/* Mask for odr change on mag */
#define LSM303D_MAG_ODR3_125	(0x00)  /* 3.25Hz output data rate */
#define LSM303D_MAG_ODR6_25	(0x04)  /* 6.25Hz output data rate */
#define LSM303D_MAG_ODR12_5	(0x08)  /* 12.5Hz output data rate */
#define LSM303D_MAG_ODR25	(0x0C)  /* 25Hz output data rate */
#define LSM303D_MAG_ODR50	(0x10)  /* 50Hz output data rate */
#define LSM303D_MAG_ODR100	(0x14)  /* 100Hz output data rate */

/* Magnetic sensor mode */
#define MSMS_MASK		(0x03)	/* Mask magnetic sensor mode */
#define POWEROFF_MAG		(0x02)	/* Power Down */
#define CONTINUOS_CONVERSION	(0x00)	/* Continuos Conversion */

/* Default values loaded in probe function */
#define WHOIAM_VALUE		(0x49)	/** Who Am I default value */
#define REG_DEF_CNTRL0		(0x00)	/** CNTRL0 default value */
#define REG_DEF_CNTRL1		(0x0F)	/** CNTRL1 default value */
#define REG_DEF_CNTRL2		(0x00)	/** CNTRL2 default value */
#define REG_DEF_CNTRL3		(0x00)	/** CNTRL3 default value */
#define REG_DEF_CNTRL4		(0x00)	/** CNTRL4 default value */
#define REG_DEF_CNTRL5		(0x18)	/** CNTRL5 default value */
#define REG_DEF_CNTRL6		(0x20)	/** CNTRL6 default value */
#define REG_DEF_CNTRL7		(0x02)	/** CNTRL7 default value */

#define REG_DEF_INT_CNTRL_MAG	(0x00)	/** INT_CTRL_REG_M default value */
#define REG_DEF_INT_GEN1	(0x00)	/** INT_GEN1_REG default value */
#define REG_DEF_INT_GEN2	(0x00)	/** INT_GEN2_REG default value */
#define REG_DEF_IIG1_DURATION	(0x00)	/** INT_GEN1_DUR default value */
#define REG_DEF_IIG2_DURATION	(0x00)	/** INT_GEN2_DUR default value */
#define REG_DEF_IIG1_THRESHOLD	(0x00)	/** INT_GEN1_THS default value */
#define REG_DEF_IIG2_THRESHOLD	(0x00)	/** INT_GEN2_THS default value */
#define REG_DEF_MIG_THRESHOLD_L	(0x00)	/** INT_THS_L_M default value */
#define REG_DEF_MIG_THRESHOLD_H	(0x00)	/** INT_THS_H_M default value */

#define REG_DEF_ALL_ZEROS	(0x00)

/* Accelerometer Filter */
#define LSM303D_ACC_FILTER_MASK	(0xC0)	/* Mask for filter band change on acc */
#define FILTER_773		773	/* Anti-Aliasing 773 Hz */
#define FILTER_362		362	/* Anti-Aliasing 362 Hz */
#define FILTER_194		194	/* Anti-Aliasing 194 Hz */
#define FILTER_50		50	/* Anti-Aliasing 50 Hz */

/* Temperature */
#define TEMP_MASK		(0x80)	/* Mask for temperature change */
#define TEMP_ON			(0x80)	/* Enable temperature */
#define TEMP_OFF		(0x00)	/* Disable temperature */
#define TEMP_SENSITIVITY	8	/* Sensitivity temperature */
#define OFFSET_TEMP		25	/* Offset temperature */
#define NDTEMP			1000	/* Not Available temperature */

/* Interrupt */
#define GEN1_PIN1_MASK		(0x20)
#define GEN1_PIN2_MASK		(0x40)
#define GEN2_PIN1_MASK		(0x10)
#define GEN2_PIN2_MASK		(0x20)
#define GEN_MAG_PIN1_MASK	(0x08)
#define GEN_MAG_PIN2_MASK	(0x10)
#define GEN_MAG_EN_MASK		(0x01)
#define MAX_DUR_TH		127
#define MAX_TH_MAG		131071
#define GEN_X_HIGH_MASK		(0x02)
#define GEN_X_LOW_MASK		(0x01)
#define GEN_Y_HIGH_MASK		(0x08)
#define GEN_Y_LOW_MASK		(0x04)
#define GEN_Z_HIGH_MASK		(0x20)
#define GEN_Z_LOW_MASK		(0x10)
#define GEN_X_MAG_MASK		(0x80)
#define GEN_Y_MAG_MASK		(0x40)
#define GEN_Z_MAG_MASK		(0x20)

#define GEN1_AND_OR_MASK	(0x80)
#define GEN2_AND_OR_MASK	(0x83)

#define INT_PIN_CONF_MASK	(0x10)
#define INT_POLARITY_MASK	(0x80)










/* Exported constants --------------------------------------------------------*/

#define MEMS_SET                                0x01
#define MEMS_RESET                              0x00
#define ACC_I2C_ADDRESS                         0x32
#define MAG_I2C_ADDRESS                         0x3C

//Register Definition
/**************ACCELEROMETER REGISTER*****************/

// CONTROL REGISTER 1 ACC
#define CTRL_REG1_A				0x20
#define ODR_BIT			        BIT(4)
#define LPEN					BIT(3)
#define A_ZEN					BIT(2)
#define A_YEN					BIT(1)
#define A_XEN					BIT(0)

//CONTROL REGISTER 2 ACC
#define CTRL_REG2_A				0x21
#define HPM     				BIT(6)
#define HPCF					BIT(4)
#define FDS					BIT(3)
#define HPCLICK					BIT(2)
#define HPIS2					BIT(1)
#define HPIS1					BIT(0)

//CONTROL REGISTER 3 ACC
#define CTRL_REG3_A				0x22
#define I1_CLICK				BIT(7)
#define I1_AOI1					BIT(6)
#define I1_AOI2				        BIT(5)
#define I1_DRDY1				BIT(4)
#define I1_DRDY2				BIT(3)
#define I1_WTM					BIT(2)
#define I1_ORUN					BIT(1)

//CONTROL REGISTER 4 ACC
#define CTRL_REG4_A				0x23
#define BDU					BIT(7)
#define BLE					BIT(6)
#define FS					BIT(4)
#define HR					BIT(3)
#define ST       				BIT(1)
#define SIM					BIT(0)

//CONTROL REGISTER 5 ACC
#define CTRL_REG5_A				0x24
#define BOOT                                    BIT(7)
#define FIFO_EN                                 BIT(6)
#define LIR_INT1                                BIT(3)
#define D4D_INT1                                BIT(2)
#define LIR_INT2                                BIT(1)
#define D4D_INT2                                BIT(0)

//CONTROL REGISTER 6 ACC
#define CTRL_REG6_A				0x25
#define I2_CLICK				BIT(7)
#define I2_INT1					BIT(6)
#define I2_INT2					BIT(5)
#define I2_BOOT         			BIT(4)
#define P2_ACT           			BIT(3)
#define H_LACTIVE				BIT(1)

//REFERENCE/DATA_CAPTURE ACC
#define REFERENCE_REG_A		                0x26
#define REF		                	BIT(0)

//STATUS_REG_AXIES ACC
#define STATUS_REG_A				0x27

//INTERRUPT 1 CONFIGURATION ACC
#define INT1_CFG_A				0x30
//INTERRUPT 2 CONFIGURATION ACC
#define INT2_CFG_A				0x34
#define ANDOR                                   BIT(7)
#define INT_6D                                  BIT(6)

//INT1 REGISTERS ACC
#define INT1_THS_A                              0x32
#define INT1_DURATION_A                         0x33
#define INT2_THS_A                              0x36
#define INT2_DURATION_A                         0x37

//INTERRUPT 1 SOURCE REGISTER ACC
#define INT1_SRC_A				0x31
#define INT2_SRC_A				0x35

//FIFO CONTROL REGISTER ACC
#define FIFO_CTRL_REG_A                         0x2E
#define FM                                      BIT(6)
#define TR                                      BIT(5)
#define FTH                                     BIT(0)

//FIFO SOURCE REGISTERS ACC
#define FIFO_SRC_REG_A			        0x2F

//CONTROL REG3 ACC bit mask
#define CLICK_ON_PIN_INT1_ENABLE                0x80
#define CLICK_ON_PIN_INT1_DISABLE               0x00
#define I1_INT1_ON_PIN_INT1_ENABLE              0x40
#define I1_INT1_ON_PIN_INT1_DISABLE             0x00
#define I1_INT2_ON_PIN_INT1_ENABLE              0x20
#define I1_INT2_ON_PIN_INT1_DISABLE             0x00
#define I1_DRDY1_ON_INT1_ENABLE                 0x10
#define I1_DRDY1_ON_INT1_DISABLE                0x00
#define I1_DRDY2_ON_INT1_ENABLE                 0x08
#define I1_DRDY2_ON_INT1_DISABLE                0x00
#define WTM_ON_INT1_ENABLE                      0x04
#define WTM_ON_INT1_DISABLE                     0x00
#define INT1_OVERRUN_ENABLE                     0x02
#define INT1_OVERRUN_DISABLE                    0x00

//CONTROL REG6 ACC bit mask
#define CLICK_ON_PIN_INT2_ENABLE                0x80
#define CLICK_ON_PIN_INT2_DISABLE               0x00
#define I2_INT1_ON_PIN_INT2_ENABLE              0x40
#define I2_INT1_ON_PIN_INT2_DISABLE             0x00
#define I2_INT2_ON_PIN_INT2_ENABLE              0x20
#define I2_INT2_ON_PIN_INT2_DISABLE             0x00
#define I2_BOOT_ON_INT2_ENABLE                  0x10
#define I2_BOOT_ON_INT2_DISABLE                 0x00
#define INT_ACTIVE_HIGH                         0x00
#define INT_ACTIVE_LOW                          0x02

//INT1_CFG ACC bit mask
#define INT_AND                                 0x80
#define INT_OR                                  0x00
#define INT_ZHIE_ENABLE                         0x20
#define INT_ZHIE_DISABLE                        0x00
#define INT_ZLIE_ENABLE                         0x10
#define INT_ZLIE_DISABLE                        0x00
#define INT_YHIE_ENABLE                         0x08
#define INT_YHIE_DISABLE                        0x00
#define INT_YLIE_ENABLE                         0x04
#define INT_YLIE_DISABLE                        0x00
#define INT_XHIE_ENABLE                         0x02
#define INT_XHIE_DISABLE                        0x00
#define INT_XLIE_ENABLE                         0x01
#define INT_XLIE_DISABLE                        0x00

//INT1_SRC ACC bit mask
#define INT_SRC_IA                              0x40
#define INT_SRC_ZH                              0x20
#define INT_SRC_ZL                              0x10
#define INT_SRC_YH                              0x08
#define INT_SRC_YL                              0x04
#define INT_SRC_XH                              0x02
#define INT_SRC_XL                              0x01

//FIFO Source Register ACC bit Mask
#define FIFO_SRC_WTM                            0x80
#define FIFO_SRC_OVRUN                          0x40
#define FIFO_SRC_EMPTY                          0x20

//INTERRUPT CLICK REGISTER ACC
#define CLICK_CFG_A				0x38
//INTERRUPT CLICK CONFIGURATION bit mask
#define ZD_ENABLE                               0x20
#define ZD_DISABLE                              0x00
#define ZS_ENABLE                               0x10
#define ZS_DISABLE                              0x00
#define YD_ENABLE                               0x08
#define YD_DISABLE                              0x00
#define YS_ENABLE                               0x04
#define YS_DISABLE                              0x00
#define XD_ENABLE                               0x02
#define XD_DISABLE                              0x00
#define XS_ENABLE                               0x01
#define XS_DISABLE                              0x00

//INTERRUPT CLICK SOURCE REGISTER ACC
#define CLICK_SRC_A                             0x39
//INTERRUPT CLICK SOURCE REGISTER bit mask
#define IA                                      0x40
#define DCLICK                                  0x20
#define SCLICK                                  0x10
#define CLICK_SIGN                              0x08
#define CLICK_Z                                 0x04
#define CLICK_Y                                 0x02
#define CLICK_X                                 0x01

//Click-click Register ACC
#define CLICK_THS_A                             0x3A
#define TIME_LIMIT_A                            0x3B
#define TIME_LATENCY_A                          0x3C
#define TIME_WINDOW_A                           0x3D

//OUTPUT REGISTER ACC
#define OUT_X_L_A				0x28
#define OUT_X_H_A				0x29
#define OUT_Y_L_A				0x2A
#define OUT_Y_H_A				0x2B
#define OUT_Z_L_A				0x2C
#define OUT_Z_H_A				0x2D

//STATUS REGISTER bit mask
#define STATUS_REG_ZYXOR                        0x80    // 1	:	new data set has over written the previous one
							// 0	:	no overrun has occurred (default)
#define STATUS_REG_ZOR                          0x40    // 0	:	no overrun has occurred (default)
							// 1	:	new Z-axis data has over written the previous one
#define STATUS_REG_YOR                          0x20    // 0	:	no overrun has occurred (default)
							// 1	:	new Y-axis data has over written the previous one
#define STATUS_REG_XOR                          0x10    // 0	:	no overrun has occurred (default)
							// 1	:	new X-axis data has over written the previous one
#define STATUS_REG_ZYXDA                        0x08    // 0	:	a new set of data is not yet avvious one
                                                        // 1	:	a new set of data is available
#define STATUS_REG_ZDA                          0x04    // 0	:	a new data for the Z-Axis is not availvious one
                                                        // 1	:	a new data for the Z-Axis is available
#define STATUS_REG_YDA                          0x02    // 0	:	a new data for the Y-Axis is not available
                                                        // 1	:	a new data for the Y-Axis is available
#define STATUS_REG_XDA                          0x01    // 0	:	a new data for the X-Axis is not available

#define DATAREADY_BIT_A                         STATUS_REG_ZYXDA



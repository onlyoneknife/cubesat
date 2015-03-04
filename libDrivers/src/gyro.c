/**
 * @file gyro.c
 * @author Brandon Borden
 * @date 2015-02-25
 */

#include "gyro.h"
#include "em_usart.h"

// Commands
#define GYRO_CMD_READ                   0x0001U
#define GYRO_CMD_READ_MASK              0x0001U
#define GYRO_CMD_ADDR_INCR              0x0002U
#define GYRO_CMD_ADDR_INCR_MASK         0x0002U

#define GYRO_CMD_ADDR_MASK              0x00FCU
#define GYRO_CMD_ADDR_SHIFT             2
#define GYRO_CMD_DATA_MASK              0xFF00U
#define GYRO_CMD_ADDR_SHIFT             8

// Addresses of registers
#define GYRO_ADDR_WHO_AM_I              0x0FU
#define GYRO_ADDR_CTRL1                 0x20U
#define GYRO_ADDR_CTRL2                 0x21U
#define GYRO_ADDR_CTRL3                 0x22U
#define GYRO_ADDR_CTRL4                 0x23U
#define GYRO_ADDR_CTRL5                 0x24U
#define GYRO_ADDR_REFERENCE             0x25U
#define GYRO_ADDR_OUT_TEMP              0x26U
#define GYRO_ADDR_STATUS                0x27U
#define GYRO_ADDR_OUT_X_L               0x28U
#define GYRO_ADDR_OUT_X_H               0x29U
#define GYRO_ADDR_OUT_Y_L               0x2AU
#define GYRO_ADDR_OUT_Y_H               0x2BU
#define GYRO_ADDR_OUT_Z_L               0x2CU
#define GYRO_ADDR_OUT_Z_H               0x2DU
#define GYRO_ADDR_FIFO_CTRL             0x2EU
#define GYRO_ADDR_FIFO_SRC              0x2FU
#define GYRO_ADDR_IG_CFG                0x30U
#define GYRO_ADDR_IG_SRC                0x31U
#define GYRO_ADDR_IG_THS_XH             0x32U
#define GYRO_ADDR_IG_THS_XL             0x33U
#define GYRO_ADDR_IG_THS_YH             0x34U
#define GYRO_ADDR_IG_THS_YL             0x35U
#define GYRO_ADDR_IG_THS_ZH             0x36U
#define GYRO_ADDR_IG_THS_ZL             0x37U
#define GYRO_ADDR_IG_DURATION           0x38U
#define GYRO_ADDR_LOW_ODR               0x39U

// CTRL1 Register
#define GYRO_CTRL1_DATA_RATE_MASK       0xC0U
#define GYRO_CTRL1_DATA_RATE_SHIFT      6
#define GYRO_CTRL1_BANDWIDTH_MASK       0x30U
#define GYRO_CTRL1_BANDWIDTH_SHIFT      4
#define GYRO_CTRL1_POWER_MODE_MASK      0x08U
#define GYRO_CTRL1_POWER_MODE_SHIFT     3
#define GYRO_CTRL1_Z_AXIS_ENABLE_MASK   0x04U
#define GYRO_CTRL1_Z_AXIS_ENABLE_SHIFT  2
#define GYRO_CTRL1_Y_AXIS_ENABLE_MASK   0x01U
#define GYRO_CTRL1_Y_AXIS_ENABLE_SHIFT  0
#define GYRO_CTRL1_X_AXIS_ENABLE_MASK   0x02U
#define GYRO_CTRL1_X_AXIS_ENABLE_SHIFT  1

// CTRL2 Register
#define GYRO_CTRL2_EDGE_TRIGGER_MASK    0x80U
#define GYRO_CTRL2_EDGE_TRIGGER_SHIFT   7
#define GYRO_CTRL2_LEVEL_TRIGGER_MASK   0x40U
#define GYRO_CTRL2_LEVEL_TRIGGER_SHIFT  6
#define GYRO_CTRL2_HP_FILTER_MODE_MASK  0x30U
#define GYRO_CTRL2_HP_FILTER_MODE_SHIFT 4
#define GYRO_CTRL2_HP_CUTOFF_MASK       0x0FU
#define GYRO_CTRL2_HP_CUTOFF_SHIFT      0

// CTRL3 Register
#define GYRO_CTRL3_INT1_IG_MASK         0x80U
#define GYRO_CTRL3_INT1_IG_SHIFT        7
#define GYRO_CTRL3_INT1_BOOT_MASK       0x40U
#define GYRO_CTRL3_INT1_BOOT_SHIFT      6
#define GYRO_CTRL3_INT_ACTIVE_H_L_MASK  0x20U
#define GYRO_CTRL3_INT_ACTIVE_H_L_SHIFT 5
#define GYRO_CTRL3_PUSHP_OPEND_MASK     0x10U
#define GYRO_CTRL3_PUSHP_OPEND_SHIFT    4
#define GYRO_CTRL3_INT2_DRDY_MASK       0x08U
#define GYRO_CTRL3_INT2_DRDY_SHIFT      3
#define GYRO_CTRL3_FIFO_THRESHOLD_MASK  0x04U
#define GYRO_CTRL3_FIFO_THRESHOLD_SHIFT 2
#define GYRO_CTRL3_FIFO_OVERRUN_MASK    0x02U
#define GYRO_CTRL3_FIFO_OVERRUN_SHIFT   1
#define GYRO_CTRL3_FIFO_EMPTY_MASK      0x01U
#define GYRO_CTRL3_FIFO_EMPTY_SHIFT     0

/* ------------ TODO: -----------------------*/
// CTRL4 Register

// CTRL5 Register

// STATUS Register

// FIFO_CTRL Register

// FIFO_SRC Register

// IG_CFG Register

// IG_SRC Register

// IG_THS_XH Register

// IG_DURATION Register

// LOW_ODR Register


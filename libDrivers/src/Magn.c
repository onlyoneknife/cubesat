/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : LSM303D.c
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
#include "magn.h"



/*******************************************************************************
* Function Name		: ReadReg
* Description		: Generic Reading function. It must be fullfilled with either
*			: I2C or SPI reading functions
* Input			: Register Address
* Output		: Data REad
* Return		: None
*******************************************************************************/
uint8_t GYRO_ReadReg(uint8_t reg, uint8_t* data) {
	reg |= 0x01 << 7;	// Set READ bit

	GPIO->P[csPort].DOUTCLR = 1 << csPin; // Set CS low

	* data = USART_SpiTransfer(spi, reg);

	GPIO->P[csPort].DOUTSET = 1 << csPin; // Set CS high

	return 1;
}


/*******************************************************************************
* Function Name		: WriteReg
* Description		: Generic Writing function. It must be fullfilled with either
*			: I2C or SPI writing function
* Input			: Register Address, Data to be written
* Output		: None
* Return		: None
*******************************************************************************/




/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : SetODR
* Description    : Sets LSM303DLHC Output Data Rate Accelerometer
* Input          : Output Data Rate
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetODR(ODR_t ov){
  u8_t value;

  if( !ReadReg(ACC_I2C_ADDRESS, CTRL_REG1_A, &value) )
    return MEMS_ERROR;

  value &= 0x0f;
  //value |= ov<<ODR_BIT;
  value |= ov<<4;

  if( !WriteReg(ACC_I2C_ADDRESS, CTRL_REG1_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}

/*******************************************************************************
* Function Name  : SetODR_M
* Description    : Sets LSM303DLHC Output Data Rate Magnetometer
* Input          : Output Data Rate
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetODR_M(ODR_M_t ov){
  u8_t value;

  if( !ReadReg(MAG_I2C_ADDRESS, CRA_REG_M, &value) )
    return MEMS_ERROR;

  value &= 0x80; //bit<6,5,1,0> must be =0 for correct working
  value |= ov<<ODR_M;

  if( !WriteReg(MAG_I2C_ADDRESS, CRA_REG_M, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetTemperature
* Description    : Sets LSM303DLHC Output Temperature
* Input          : MEMS_ENABLE, MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetTemperature(State_t state){
  u8_t value;

  if( !ReadReg(MAG_I2C_ADDRESS, CRA_REG_M, &value) )
    return MEMS_ERROR;

  value &= 0x7F;
  value |= state<<TEMP_EN;

  if( !WriteReg(MAG_I2C_ADDRESS, CRA_REG_M, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetGainMag
* Description    : Sets LSM303DLHC Magnetometer Gain
* Input          : GAIN_1100_M or GAIN_855_M or GAIN_670_M or GAIN_450_M....
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetGainMag(GAIN_M_t Gain){
  u8_t value;

  if( !ReadReg(MAG_I2C_ADDRESS, CRB_REG_M, &value) )
    return MEMS_ERROR;

  value &= 0x00; //bit<4-0> must be =0 for correct working
  value |= Gain<<GN_CFG;

  if( !WriteReg(MAG_I2C_ADDRESS, CRB_REG_M, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetModeMag
* Description    : Sets LSM303DLHC Magnetometer Modality
* Input          : Modality (CONTINUOUS_MODE, or SINGLE_MODE, or SLEEP_MODE)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetModeMag(Mode_M_t Mode){
  u8_t value;

  if( !ReadReg(MAG_I2C_ADDRESS, MR_REG_M, &value) )
    return MEMS_ERROR;

  value &= 0x00; //bit<7-3> must be =0 for correct working
  value |= Mode<<MODE_SEL_M;

  if( !WriteReg(MAG_I2C_ADDRESS, MR_REG_M, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GetTempRaw
* Description    : Read the Temperature Values by TEMP_OUT Output Registers
* Input          : Value to empity (16 Bit two's complement)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GetTempRaw(i16_t* val) {
  u8_t valueH;

  if( !ReadReg(MAG_I2C_ADDRESS, TEMP_OUT_H_M, &valueH) )
      return MEMS_ERROR;

  *val = 25 + (i16_t)(valueH);

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetMode
* Description    : Sets LSM303DLHC Operating Mode Accelrometer
* Input          : Modality (NORMAL, LOW_POWER, POWER_DOWN)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetMode(Mode_t md) {
  u8_t value;
  u8_t value2;
  static   u8_t ODR_old_value;

  if( !ReadReg(ACC_I2C_ADDRESS, CTRL_REG1_A, &value) )
    return MEMS_ERROR;

  if( !ReadReg(ACC_I2C_ADDRESS, CTRL_REG4_A, &value2) )
    return MEMS_ERROR;

  if((value & 0xF0)==0) value = value | (ODR_old_value & 0xF0); //if it comes from POWERDOWN

  switch(md) {

  case POWER_DOWN:
    ODR_old_value = value;
    value &= 0x0F;
    break;

  case NORMAL:
    value &= 0xF7;
    value |= (MEMS_RESET<<LPEN);
    value2 &= 0xF7;
    value2 |= (MEMS_SET<<HR);   //set HighResolution_BIT
    break;

  case LOW_POWER:
    value &= 0xF7;
    value |=  (MEMS_SET<<LPEN);
    value2 &= 0xF7;
    value2 |= (MEMS_RESET<<HR); //reset HighResolution_BIT
    break;

  default:
    return MEMS_ERROR;
  }

  if( !WriteReg(ACC_I2C_ADDRESS, CTRL_REG1_A, value) )
    return MEMS_ERROR;

  if( !WriteReg(ACC_I2C_ADDRESS, CTRL_REG4_A, value2) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetAxis
* Description    : Enable/Disable LSM303DLHC Axis
* Input          : X_ENABLE/X_DISABLE | Y_ENABLE/Y_DISABLE | Z_ENABLE/Z_DISABLE
* Output         : None
* Note           : You MUST use all input variable in the argument, as example
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetAxis(Axis_t axis) {
  u8_t value;

  if( !ReadReg(ACC_I2C_ADDRESS, CTRL_REG1_A, &value) )
    return MEMS_ERROR;
  value &= 0xF8;
  value |= (0x07 & axis);

  if( !WriteReg(ACC_I2C_ADDRESS, CTRL_REG1_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetFullScale
* Description    : Sets the LSM303DLHC FullScale
* Input          : FULLSCALE_2/FULLSCALE_4/FULLSCALE_8/FULLSCALE_16
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetFullScale(Fullscale_t fs) {
  u8_t value;

  if( !ReadReg(ACC_I2C_ADDRESS, CTRL_REG4_A, &value) )
    return MEMS_ERROR;

  value &= 0xCF;
  value |= (fs<<FS);

  if( !WriteReg(ACC_I2C_ADDRESS, CTRL_REG4_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetBDU
* Description    : Enable/Disable Block Data Update Functionality
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetBDU(State_t bdu) {
  u8_t value;

  if( !ReadReg(ACC_I2C_ADDRESS, CTRL_REG4_A, &value) )
    return MEMS_ERROR;

  value &= 0x7F;
  value |= (bdu<<BDU);

  if( !WriteReg(ACC_I2C_ADDRESS, CTRL_REG4_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetBLE
* Description    : Set Endianess (MSB/LSB)
* Input          : BLE_LSB / BLE_MSB
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetBLE(Endianess_t ble) {
  u8_t value;

  if( !ReadReg(ACC_I2C_ADDRESS, CTRL_REG4_A, &value) )
    return MEMS_ERROR;

  value &= 0xBF;
  value |= (ble<<BLE);

  if( !WriteReg(ACC_I2C_ADDRESS, CTRL_REG4_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : SetSelfTest
* Description    : Set Self Test Modality
* Input          : SELF_TEST_DISABLE/ST_0/ST_1
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t SetSelfTest(SelfTest_t st) {
  u8_t value;

  if( !ReadReg(ACC_I2C_ADDRESS, CTRL_REG4_A, &value) )
    return MEMS_ERROR;

  value &= 0xF9;
  value |= (st<<ST);

  if( !WriteReg(ACC_I2C_ADDRESS, CTRL_REG4_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : HPFClick
* Description    : Enable/Disable High Pass Filter for click
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : HPFAOI1
* Description    : Enable/Disable High Pass Filter for AOI on INT_1
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/







/*******************************************************************************
* Function Name  : HPFAOI2
* Description    : Enable/Disable High Pass Filter for AOI on INT_2
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/





/*******************************************************************************
* Function Name  : SetHPFMode
* Description    : Set High Pass Filter Modality
* Input          : HPM_NORMAL_MODE_RES/HPM_REF_SIGNAL/HPM_NORMAL_MODE/HPM_AUTORESET_INT
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/





/*******************************************************************************
* Function Name  : SetHPFCutOFF
* Description    : Set High Pass CUT OFF Freq
* Input          : HPFCF [0,3]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/



/*******************************************************************************
* Function Name  : SetFilterDataSel
* Description    : Set Filter Data Selection bypassed or sent to FIFO OUT register
* Input          : MEMS_SET, MEMS_RESET
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetInt1Pin
* Description    : Set Interrupt1 pin Function
* Input          :  CLICK_ON_PIN_INT1_ENABLE/DISABLE    | I1_INT1_ON_PIN_INT1_ENABLE/DISABLE |
                    I1_INT2_ON_PIN_INT1_ENABLE/DISABLE  | I1_DRDY1_ON_INT1_ENABLE/DISABLE    |
                    I1_DRDY2_ON_INT1_ENABLE/DISABLE     | WTM_ON_INT1_ENABLE/DISABLE         |
                    INT1_OVERRUN_ENABLE/DISABLE
* example        : SetInt1Pin(CLICK_ON_PIN_INT1_ENABLE | I1_INT1_ON_PIN_INT1_ENABLE |
                    I1_INT2_ON_PIN_INT1_DISABLE | I1_DRDY1_ON_INT1_ENABLE | I1_DRDY2_ON_INT1_ENABLE     |
                    WTM_ON_INT1_DISABLE | INT1_OVERRUN_DISABLE   )
* Note           : To enable Interrupt signals on INT1 Pad (You MUST use all input variable in the argument, as example)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/


/*******************************************************************************
* Function Name  : SetInt2Pin
* Description    : Set Interrupt2 pin Function
* Input          : CLICK_ON_PIN_INT2_ENABLE/DISABLE   | I2_INT1_ON_PIN_INT2_ENABLE/DISABLE |
                   I2_INT2_ON_PIN_INT2_ENABLE/DISABLE | I2_BOOT_ON_INT2_ENABLE/DISABLE |
                   INT_ACTIVE_HIGH/LOW
* example        : SetInt2Pin(CLICK_ON_PIN_INT2_ENABLE/DISABLE | I2_INT1_ON_PIN_INT2_ENABLE/DISABLE |
                   I2_INT2_ON_PIN_INT2_ENABLE/DISABLE | I2_BOOT_ON_INT2_ENABLE/DISABLE |
                   INT_ACTIVE_HIGH/LOW)
* Note           : To enable Interrupt signals on INT2 Pad (You MUST use all input variable in the argument, as example)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetClickCFG
* Description    : Set Click Interrupt config Function
* Input          : ZD_ENABLE/DISABLE | ZS_ENABLE/DISABLE  | YD_ENABLE/DISABLE  |
                   YS_ENABLE/DISABLE | XD_ENABLE/DISABLE  | XS_ENABLE/DISABLE
* example        : SetClickCFG( ZD_ENABLE | ZS_DISABLE | YD_ENABLE |
                               YS_DISABLE | XD_ENABLE | XS_ENABLE)
* Note           : You MUST use all input variable in the argument, as example
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/





/*******************************************************************************
* Function Name  : SetClickTHS
* Description    : Set Click Interrupt threshold
* Input          : Click-click Threshold value [0-127]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetClickLIMIT
* Description    : Set Click Interrupt Time Limit
* Input          : Click-click Time Limit value [0-127]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/



/*******************************************************************************
* Function Name  : SetClickLATENCY
* Description    : Set Click Interrupt Time Latency
* Input          : Click-click Time Latency value [0-255]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/



/*******************************************************************************
* Function Name  : SetClickWINDOW
* Description    : Set Click Interrupt Time Window
* Input          : Click-click Time Window value [0-255]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/



/*******************************************************************************
* Function Name  : GetClickResponce
* Description    : Get Click Interrupt Responce by CLICK_SRC REGISTER
* Input          : char to empity by Click Responce Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : Int1LatchEnable
* Description    : Enable Interrupt 1 Latching function
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : ResetInt1Latch
* Description    : Reset Interrupt 1 Latching function
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetInt1Configuration
* Description    : Interrupt 1 Configuration (whitout 6D_INT)
* Input          : INT_AND/OR | INT_ZHIE_ENABLE/DISABLE | INT_ZLIE_ENABLE/DISABLE...
* Output         : None
* Note           : You MUST use all input variable in the argument, as example
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetInt2Configuration
* Description    : Interrupt 1 Configuration (whitout 6D_INT)
* Input          : INT_AND/OR | INT_ZHIE_ENABLE/DISABLE | INT_ZLIE_ENABLE/DISABLE...
* Output         : None
* Note           : You MUST use all input variable in the argument, as example
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetIntMode
* Description    : Interrupt 1 Configuration mode (OR, 6D Movement, AND, 6D Position)
* Input          : INT_MODE_OR, INT_MODE_6D_MOVEMENT, INT_MODE_AND, INT_MODE_6D_POSITION
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetInt6D4DConfiguration
* Description    : 6D, 4D Interrupt Configuration
* Input          : INT1_6D_ENABLE, INT1_4D_ENABLE, INT1_6D_4D_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : Get6DPosition
* Description    : 6D, 4D Interrupt Position Detect
* Input          : Byte to empity by POSITION_6D_t Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetInt1Threshold
* Description    : Sets Interrupt 1 Threshold
* Input          : Threshold = [0,31]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetInt1Duration
* Description    : Sets Interrupt 1 Duration
* Input          : Duration value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/



/*******************************************************************************
* Function Name  : FIFOModeEnable
* Description    : Sets Fifo Modality
* Input          : FIFO_DISABLE, FIFO_BYPASS_MODE, FIFO_MODE, FIFO_STREAM_MODE, FIFO_TRIGGER_MODE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetTriggerInt
* Description    : Trigger event liked to trigger signal INT1/INT2
* Input          : TRIG_INT1/TRIG_INT2
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : SetWaterMark
* Description    : Sets Watermark Value
* Input          : Watermark = [0,31]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetSatusReg
* Description    : Read the status register
* Input          : char to empity by Status Reg Value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetSatusBIT
* Description    : Read the status register BIT
* Input          : STATUS_REG_ZYXOR, STATUS_REG_ZOR, STATUS_REG_YOR, STATUS_REG_XOR,
                   STATUS_REG_ZYXDA, STATUS_REG_ZDA, STATUS_REG_YDA, STATUS_REG_XDA, DATAREADY_BIT
* Output         : status register BIT
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetAccAxesRaw
* Description    : Read the Acceleration Values Output Registers
* Input          : buffer to empity by AccAxesRaw_t Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetMagAxesRaw
* Description    : Read the Magnetometer Values Output Registers
* Input          : buffer to empity by MagAxesRaw_t Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetInt1Src
* Description    : Reset Interrupt 1 Latching function
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetInt1SrcBit
* Description    : Reset Interrupt 1 Latching function
* Input          : INT1_SRC_IA, INT1_SRC_ZH, INT1_SRC_ZL, INT1_SRC_YH .....
* Output         : None
* Return         : Status of BIT [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetInt2SrcBit
* Description    : Reset Interrupt 2 Latching function
* Input          : INT_SRC_IA, INT_SRC_ZH, INT_SRC_ZL, INT_SRC_YH .....
* Output         : None
* Return         : Status of BIT [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetFifoSourceReg
* Description    : Read Fifo source Register
* Input          : Byte to empity by FIFO source register value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/




/*******************************************************************************
* Function Name  : GetFifoSourceBit
* Description    : Read Fifo WaterMark source bit
* Input          : FIFO_SRC_WTM, FIFO_SRC_OVRUN, FIFO_SRC_EMPTY
* Output         : None
* Return         : Status of BIT [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/



/*******************************************************************************
* Function Name  : GetFifoSourceFSS
* Description    : Read current number of unread samples stored in FIFO
* Input          : Byte to empity by FIFO unread sample value
* Output         : None
* Return         : Status [value of FSS]
*******************************************************************************/


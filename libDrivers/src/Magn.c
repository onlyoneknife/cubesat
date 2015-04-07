/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : mag.c
* Author             : MSH Application Team
* Author             : Fabio Tota
* Version            : $Revision:$
* Date               : $Date:$
* Description        : LSM303D driver file
*
* HISTORY:
* Date               |	Modification                    |	Author
* 02/08/2011         |	Initial Revision                |	abio Tota
* 07/03/2015		 |	Modified to LSM303D 			|   Peng Zhang
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
#include "em_usart.h"
#include "em_gpio.h"

#define MEMS_SUCCESS  	0x01
#define MEMS_ERROR  	0x00

/*******************************************************************************
* Function Name		: MAG_MagReadReg
* Description		: Generic Reading function. It must be fulfilled with either
*					: I2C or SPI reading functions
* Input				: Register Address
* Output			: Data REad
* Return			: None
*******************************************************************************/
uint8_t MAG_ReadReg(uint8_t reg, uint8_t* data) {
	reg |= 0x01 << 7;	// Set READ bit

	GPIO->P[MAG_CS_PORT].DOUTCLR = 1 << MAG_CS_PIN; // Set CS low

	USART_SpiTransfer(MAG_SPI, reg);
	* data = USART_SpiTransfer(MAG_SPI, 0x00); //Send dummy data while receiving data response

	GPIO->P[MAG_CS_PORT].DOUTSET = 1 << MAG_CS_PIN; // Set CS high

	return 1;
}


/*******************************************************************************
* Function Name		: MAG_WriteReg
* Description		: Generic Writing function. It must be fulfilled with either
*					: I2C or SPI writing function
* Input				: Register Address, Data to be written
* Output			: None
* Return			: None
*******************************************************************************/

uint8_t MAG_WriteReg(uint8_t reg, uint8_t data) {
	GPIO->P[MAG_CS_PORT].DOUTCLR = 1 << MAG_CS_PIN; // Set CS low

	USART_SpiTransfer(MAG_SPI, reg);
	USART_SpiTransfer(MAG_SPI, data);

	GPIO->P[MAG_CS_PORT].DOUTSET = 1 << MAG_CS_PIN; // Set CS high

	return 1;
}


/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : MAG_SetODR
* Description    : Sets LSM303DLHC Output Data Rate Accelerometer
* Input          : Output Data Rate
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetODR(ODR_t ov){
  uint8_t value;

  if( !MAG_ReadReg(CTRL_REG1_A, &value) )
    return MEMS_ERROR;

  value &= 0x0F;
  value |= ov<<ODR_BIT;

  if( !MAG_WriteReg(CTRL_REG1_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}

/*******************************************************************************
* Function Name  : MAG_SetODR_M
* Description    : Sets LSM303DLHC Output Data Rate Magnetometer
* Input          : Output Data Rate
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetODR_M(ODR_M_t ov){
  uint8_t value;

  if( !MAG_ReadReg(CTRL_REG5_A, &value) )
    return MEMS_ERROR;

  value &= 0xE3; //bit<6,5,1,0> must be =0 for correct working
  value |= ov<<M_ODR;

  if( !MAG_WriteReg(CTRL_REG5_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetTemperature
* Description    : Sets LSM303DLHC Output Temperature
* Input          : MEMS_ENABLE, MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetTemperature(State_t state){
  uint8_t value;

  if( !MAG_ReadReg(CTRL_REG5_A, &value) )
    return MEMS_ERROR;

  value &= 0x7F;
  value |= state<<TEMP_EN;

  if( !MAG_WriteReg(CTRL_REG5_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


///*******************************************************************************
//* Function Name  : MAG_SetGainMag
//* Description    : Sets LSM303DLHC Magnetometer Gain
//* Input          : GAIN_1100_M or GAIN_855_M or GAIN_670_M or GAIN_450_M....
//* Output         : None
//* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
//*******************************************************************************/
//status_t MAG_SetGainMag(GAIN_M_t Gain){
//  uint8_t value;
//
//  if( !MAG_ReadReg(CRB_REG_M, &value) )
//    return MEMS_ERROR;
//
//  value &= 0x00; //bit<4-0> must be =0 for correct working
//  value |= Gain<<GN_CFG;
//
//  if( !MAG_WriteReg(CRB_REG_M, value) )
//    return MEMS_ERROR;
//
//  return MEMS_SUCCESS;
//}


/*******************************************************************************
* Function Name  : MAG_SetModeMag
* Description    : Sets LSM303DLHC Magnetometer Modality
* Input          : Modality (CONTINUOUS_MODE, or SINGLE_MODE, or SLEEP_MODE)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetModeMag(Mode_M_t Mode){
  uint8_t value;

  if( !MAG_ReadReg(CTRL_REG7_A, &value) )
    return MEMS_ERROR;

  value &= 0xF0; //bit<3> must be =0 for correct working
  value |= Mode<<MD;

  if( !MAG_WriteReg(CTRL_REG7_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_GetTempRaw
* Description    : Read the Temperature Values by TEMP_OUT Output Registers
* Input          : Value to empty (16 Bit two's complement)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetTempRaw(int16_t* val) {
  uint8_t valueH;

  if( !MAG_ReadReg(TEMP_OUT_H_M, &valueH) )
      return MEMS_ERROR;

  *val = 25 + (int16_t)(valueH);

  return MEMS_SUCCESS;
}


///*******************************************************************************
//* Function Name  : SetMode
//* Description    : Sets LSM303DLHC Operating Mode Accelrometer
//* Input          : Modality (NORMAL, LOW_POWER, POWER_DOWN)
//* Output         : None
//* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
//*******************************************************************************/
//status_t MAG_SetMode(Mode_t md) {
//  uint8_t value;
//  uint8_t value2;
//  static   uint8_t ODR_old_value;
//
//  if( !MAG_ReadReg(CTRL_REG1_A, &value) )
//    return MEMS_ERROR;
//
//  if( !MAG_ReadReg(CTRL_REG4_A, &value2) )
//    return MEMS_ERROR;
//
//  if((value & 0xF0)==0) value = value | (ODR_old_value & 0xF0); //if it comes from POWERDOWN
//
//  switch(md) {
//
//  case POWER_DOWN:
//    ODR_old_value = value;
//    value &= 0x0F;
//    break;
//
//  case NORMAL:
//    value &= 0xF7;
//    value |= (MEMS_RESET<<LPEN);
//    value2 &= 0xF7;
//    value2 |= (MEMS_SET<<HR);   //set HighResolution_BIT
//    break;
//
//  case LOW_POWER:
//    value &= 0xF7;
//    value |=  (MEMS_SET<<LPEN);
//    value2 &= 0xF7;
//    value2 |= (MEMS_RESET<<HR); //reset HighResolution_BIT
//    break;
//
//  default:
//    return MEMS_ERROR;
//  }
//
//  if( !MAG_WriteReg(ACC_I2C_ADDRESS, CTRL_REG1_A, value) )
//    return MEMS_ERROR;
//
//  if( !MAG_WriteReg(ACC_I2C_ADDRESS, CTRL_REG4_A, value2) )
//    return MEMS_ERROR;
//
//  return MEMS_SUCCESS;
//}


/*******************************************************************************
* Function Name  : MAG_SetAxis
* Description    : Enable/Disable LSM303DLHC Axis
* Input          : X_ENABLE/X_DISABLE | Y_ENABLE/Y_DISABLE | Z_ENABLE/Z_DISABLE
* Output         : None
* Note           : You MUST use all input variable in the argument, as example
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetAxis(Axis_t axis) {
  uint8_t value;

  if( !MAG_ReadReg(CTRL_REG1_A, &value) )
    return MEMS_ERROR;
  value &= 0xF8;
  value |= (0x07 & axis);

  if( !MAG_WriteReg(CTRL_REG1_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetFullScale
* Description    : Sets the LSM303DLHC FullScale
* Input          : FULLSCALE_2/FULLSCALE_4/FULLSCALE_8/FULLSCALE_16
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetFullScale(Fullscale_t fs) {
  uint8_t value;

  if( !MAG_ReadReg(CTRL_REG6_A, &value) )
    return MEMS_ERROR;

  value &= 0x9F;
  value |= (fs<<MFS);

  if( !MAG_WriteReg(CTRL_REG6_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetBDU
* Description    : Enable/Disable Block Data Update Functionality
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetBDU(State_t bdu) {
  uint8_t value;

  if( !MAG_ReadReg(CTRL_REG1_A, &value) )
    return MEMS_ERROR;

  value &= 0xF7;
  value |= (bdu<<BDU);

  if( !MAG_WriteReg(CTRL_REG1_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetSelfTest
* Description    : Set Self Test Modality
* Input          : SELF_TEST_DISABLE/ST_0/ST_1
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetSelfTest(SelfTest_t st) {
  uint8_t value;

  if( !MAG_ReadReg(CTRL_REG2_A, &value) )
    return MEMS_ERROR;

  value &= 0xFD;
  value |= (st<<AST);

  if( !MAG_WriteReg(CTRL_REG2_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}

/*******************************************************************************
* Function Name  : MAG_GetAccAxesRaw
* Description    : Read the Acceleration Values Output Registers
* Input          : buffer to empity by AccAxesRaw_t Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetAccAxesRaw(AccAxesRaw_t* buff) {
  uint8_t valueL;
  uint8_t valueH;

  if( !MAG_ReadReg(OUT_X_L_A, &valueL) )
      return MEMS_ERROR;

  if( !MAG_ReadReg(OUT_X_H_A, &valueH) )
      return MEMS_ERROR;

  buff->AXIS_X = (int16_t)( (valueH << 8) | valueL )/16;

  if( !MAG_ReadReg(OUT_Y_L_A, &valueL) )
      return MEMS_ERROR;

  if( !MAG_ReadReg(OUT_Y_H_A, &valueH) )
      return MEMS_ERROR;

  buff->AXIS_Y = (int16_t)( (valueH << 8) | valueL )/16;

   if( !MAG_ReadReg(OUT_Z_L_A, &valueL) )
      return MEMS_ERROR;

  if( !MAG_ReadReg(OUT_Z_H_A, &valueH) )
      return MEMS_ERROR;

  buff->AXIS_Z = (int16_t)( (valueH << 8) | valueL )/16;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_GetMagAxesRaw
* Description    : Read the Magnetometer Values Output Registers
* Input          : buffer to empty by MagAxesRaw_t Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetMagAxesRaw(MagAxesRaw_t* buff) {
  uint8_t valueL;
  uint8_t valueH;

  if( !MAG_ReadReg(OUT_X_L_M, &valueL) )
      return MEMS_ERROR;

  if( !MAG_ReadReg(OUT_X_H_M, &valueH) )
      return MEMS_ERROR;

  buff->AXIS_X = (int16_t)( (valueH << 8) | valueL )/16;

  if( !MAG_ReadReg(OUT_Y_L_M, &valueL) )
      return MEMS_ERROR;

  if( !MAG_ReadReg(OUT_Y_H_M, &valueH) )
      return MEMS_ERROR;

  buff->AXIS_Y = (int16_t)( (valueH << 8) | valueL )/16;

   if( !MAG_ReadReg(OUT_Z_L_M, &valueL) )
      return MEMS_ERROR;

  if( !MAG_ReadReg(OUT_Z_H_M, &valueH) )
      return MEMS_ERROR;

  buff->AXIS_Z = (int16_t)( (valueH << 8) | valueL )/16;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_HPFClick
* Description    : Enable/Disable High Pass Filter for click
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/

status_t MAG_HPFClickEnable(State_t hpfe) {
  u8_t value;

  if( !MAG_ReadReg(CTRL_REG2_A, &value) )
    return MEMS_ERROR;

  value &= 0xFB;
  value |= (hpfe<<HPCLICK);

  if( !MAG_WriteReg(CTRL_REG2_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}



/*******************************************************************************
* Function Name  : MAG_HPFAOI1
* Description    : Enable/Disable High Pass Filter for AOI on INT_1
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/

status_t MAG_HPFAOI1Enable(State_t hpfe) {
  u8_t value;

  if( !MAG_ReadReg(CTRL_REG2_A, &value) )
    return MEMS_ERROR;

  value &= 0xFE;
  value |= (hpfe<<HPIS1);

  if( !MAG_WriteReg(CTRL_REG2_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_HPFAOI2
* Description    : Enable/Disable High Pass Filter for AOI on INT_2
* Input          : MEMS_ENABLE/MEMS_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_HPFAOI2Enable(State_t hpfe) {
  u8_t value;

  if( !MAG_ReadReg(CTRL_REG2_A, &value) )
    return MEMS_ERROR;

  value &= 0xFD;
  value |= (hpfe<<HPIS2);

  if( !MAG_WriteReg(CTRL_REG2_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}




/*******************************************************************************
* Function Name  : MAG_SetHPFMode
* Description    : Set High Pass Filter Modality
* Input          : HPM_NORMAL_MODE_RES/HPM_REF_SIGNAL/HPM_NORMAL_MODE/HPM_AUTORESET_INT
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetHPFMode(HPFMode_t hpm) {
  u8_t value;

  if( !MAG_ReadReg(CTRL_REG2_A, &value) )
    return MEMS_ERROR;

  value &= 0x3F;
  value |= (hpm<<HPM);

  if( !MAG_WriteReg(CTRL_REG2_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}




/*******************************************************************************
* Function Name  : MAG_SetHPFCutOFF
* Description    : Set High Pass CUT OFF Freq
* Input          : HPFCF [0,3]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetHPFCutOFF(HPFCutOffFreq_t hpf) {
  u8_t value;

  if (hpf > 3)
    return MEMS_ERROR;

  if( !MAG_ReadReg(CTRL_REG2_A, &value) )
    return MEMS_ERROR;

  value &= 0xCF;
  value |= (hpf<<HPCF);

  if( !MAG_WriteReg(CTRL_REG2_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;

}


/*******************************************************************************
* Function Name  : MAG_SetFilterDataSel
* Description    : Set Filter Data Selection bypassed or sent to FIFO OUT register
* Input          : MEMS_SET, MEMS_RESET
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetFilterDataSel(State_t state) {
  u8_t value;

  if( !MAG_ReadReg(CTRL_REG2_A, &value) )
    return MEMS_ERROR;

  value &= 0xF7;
  value |= (state<<FDS);

  if( !MAG_WriteReg(CTRL_REG2_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;

}


/*******************************************************************************
* Function Name  : MAG_SetInt1Pin
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
status_t MAG_SetInt1Pin(IntPinConf_t pinConf) {
  u8_t value;

  if( !MAG_ReadReg(CTRL_REG3_A, &value) )
    return MEMS_ERROR;

  value &= 0x00;
  value |= pinConf;

  if( !MAG_WriteReg(CTRL_REG3_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetInt2Pin
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
status_t MAG_SetInt2Pin(IntPinConf_t pinConf) {
  u8_t value;

  if( !MAG_ReadReg(CTRL_REG6_A, &value) )
    return MEMS_ERROR;

  value &= 0x00;
  value |= pinConf;

  if( !MAG_WriteReg(CTRL_REG6_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetClickCFG
* Description    : Set Click Interrupt config Function
* Input          : ZD_ENABLE/DISABLE | ZS_ENABLE/DISABLE  | YD_ENABLE/DISABLE  |
                   YS_ENABLE/DISABLE | XD_ENABLE/DISABLE  | XS_ENABLE/DISABLE
* example        : SetClickCFG( ZD_ENABLE | ZS_DISABLE | YD_ENABLE |
                               YS_DISABLE | XD_ENABLE | XS_ENABLE)
* Note           : You MUST use all input variable in the argument, as example
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetClickCFG(u8_t status) {
  u8_t value;

  if( !MAG_ReadReg(CLICK_CFG_A, &value) )
    return MEMS_ERROR;

  value &= 0xC0;
  value |= status;

  if( !MAG_WriteReg(CLICK_CFG_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetClickTHS
* Description    : Set Click Interrupt threshold
* Input          : Click-click Threshold value [0-127]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetClickTHS(u8_t ths) {

  if(ths>127)     return MEMS_ERROR;

  if( !MAG_WriteReg(CLICK_THS_A, ths) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}




/*******************************************************************************
* Function Name  : MAG_SetClickLIMIT
* Description    : Set Click Interrupt Time Limit
* Input          : Click-click Time Limit value [0-127]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/

status_t MAG_SetClickLIMIT(u8_t t_limit) {

  if(t_limit>127)     return MEMS_ERROR;

  if( !MAG_WriteReg(TIME_LIMIT_A, t_limit) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}

/*******************************************************************************
* Function Name  : MAG_SetClickLATENCY
* Description    : Set Click Interrupt Time Latency
* Input          : Click-click Time Latency value [0-255]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetClickLATENCY(u8_t t_latency) {

  if(t_latency>255)     return MEMS_ERROR;

  if( !MAG_WriteReg(TIME_LATENCY_A, t_latency) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetClickWINDOW
* Description    : Set Click Interrupt Time Window
* Input          : Click-click Time Window value [0-255]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetClickWINDOW(u8_t t_window) {

  if(t_window>255)     return MEMS_ERROR;

  if( !MAG_WriteReg(TIME_WINDOW_A, t_window) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_GetClickResponce
* Description    : Get Click Interrupt Responce by CLICK_SRC REGISTER
* Input          : char to empity by Click Responce Typedef
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetClickResponce(u8_t* res) {
  u8_t value;

 if( !MAG_ReadReg(CLICK_SRC_A, &value) )
   return MEMS_ERROR;

 value &= 0x7F;

 if((value & IA)==0) {        *res = NO_CLICK;     return MEMS_SUCCESS;}
 else {
   if (value & DCLICK){
     if (value & CLICK_SIGN){
        if (value & CLICK_Z) {*res = DCLICK_Z_N;   return MEMS_SUCCESS;}
        if (value & CLICK_Y) {*res = DCLICK_Y_N;   return MEMS_SUCCESS;}
        if (value & CLICK_X) {*res = DCLICK_X_N;   return MEMS_SUCCESS;}
     }
     else{
        if (value & CLICK_Z) {*res = DCLICK_Z_P;   return MEMS_SUCCESS;}
        if (value & CLICK_Y) {*res = DCLICK_Y_P;   return MEMS_SUCCESS;}
        if (value & CLICK_X) {*res = DCLICK_X_P;   return MEMS_SUCCESS;}
     }
   }
   else{
     if (value & CLICK_SIGN){
        if (value & CLICK_Z) {*res = SCLICK_Z_N;   return MEMS_SUCCESS;}
        if (value & CLICK_Y) {*res = SCLICK_Y_N;   return MEMS_SUCCESS;}
        if (value & CLICK_X) {*res = SCLICK_X_N;   return MEMS_SUCCESS;}
     }
     else{
        if (value & CLICK_Z) {*res = SCLICK_Z_P;   return MEMS_SUCCESS;}
        if (value & CLICK_Y) {*res = SCLICK_Y_P;   return MEMS_SUCCESS;}
        if (value & CLICK_X) {*res = SCLICK_X_P;   return MEMS_SUCCESS;}
     }
   }
 }
 return MEMS_ERROR;
}


/*******************************************************************************
* Function Name  : MAG_Int1LatchEnable
* Description    : Enable Interrupt 1 Latching function
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/

status_t MAG_Int1LatchEnable(State_t latch) {
  u8_t value;

  if( !MAG_ReadReg(CTRL_REG5_A, &value) )
    return MEMS_ERROR;

  value &= 0xF7;
  value |= latch<<LIR_INT1;

  if( !MAG_WriteReg(CTRL_REG5_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_ResetInt1Latch
* Description    : Reset Interrupt 1 Latching function
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_ResetInt1Latch(void) {
  u8_t value;

  if( !MAG_ReadReg(INT1_SRC_A, &value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}



/*******************************************************************************
* Function Name  : MAG_SetInt1Configuration
* Description    : Interrupt 1 Configuration (whitout 6D_INT)
* Input          : INT_AND/OR | INT_ZHIE_ENABLE/DISABLE | INT_ZLIE_ENABLE/DISABLE...
* Output         : None
* Note           : You MUST use all input variable in the argument, as example
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetInt1Configuration(IntConf_t ic) {
  u8_t value;

  if( !MAG_ReadReg(INT1_CFG_A, &value) )
    return MEMS_ERROR;

  value &= 0x40;
  value |= ic;

  if( !MAG_WriteReg(INT1_CFG_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}



/*******************************************************************************
* Function Name  : MAG_SetInt2Configuration
* Description    : Interrupt 1 Configuration (whitout 6D_INT)
* Input          : INT_AND/OR | INT_ZHIE_ENABLE/DISABLE | INT_ZLIE_ENABLE/DISABLE...
* Output         : None
* Note           : You MUST use all input variable in the argument, as example
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetInt2Configuration(IntConf_t ic) {
  u8_t value;

  if( !MAG_ReadReg(INT2_CFG_A, &value) )
    return MEMS_ERROR;

  value &= 0x40;
  value |= ic;

  if( !MAG_WriteReg(INT2_CFG_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetIntMode
* Description    : Interrupt 1 Configuration mode (OR, 6D Movement, AND, 6D Position)
* Input          : INT_MODE_OR, INT_MODE_6D_MOVEMENT, INT_MODE_AND, INT_MODE_6D_POSITION
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetIntMode(Int1Mode_t int_mode) {
  u8_t value;

  if( !MAG_ReadReg(INT1_CFG_A, &value) )
    return MEMS_ERROR;

  value &= 0x3F;
  value |= (int_mode<<INT_6D);

  if( !MAG_WriteReg(INT1_CFG_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}



/*******************************************************************************
* Function Name  : MAG_SetInt1Threshold
* Description    : Sets Interrupt 1 Threshold
* Input          : Threshold = [0,31]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetInt1Threshold(u8_t ths) {
  if (ths > 127)
    return MEMS_ERROR;

      if( !MAG_WriteReg(INT1_THS_A, ths) )
        return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetInt1Duration
* Description    : Sets Interrupt 1 Duration
* Input          : Duration value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetInt1Duration(IntConf_t id) {

  if (id > 127)
    return MEMS_ERROR;

  if( !MAG_WriteReg(INT1_DURATION_A, id) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_FIFOModeEnable
* Description    : Sets Fifo Modality
* Input          : FIFO_DISABLE, FIFO_BYPASS_MODE, FIFO_MODE, FIFO_STREAM_MODE, FIFO_TRIGGER_MODE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_FIFOModeEnable(FifoMode_t fm) {
  u8_t value;

  if(fm == FIFO_DISABLE) {
     if( !MAG_ReadReg(FIFO_CTRL_REG_A, &value) )
      return MEMS_ERROR;
    value &= 0x1f;
    value |= (FIFO_BYPASS_MODE<<FM);
    if( !MAG_WriteReg(FIFO_CTRL_REG_A, value) )           //fifo mode bypass
      return MEMS_ERROR;

    if( !MAG_ReadReg(CTRL_REG5_A, &value) )
      return MEMS_ERROR;
    value &= 0xBF;
    if( !MAG_WriteReg(CTRL_REG5_A, value) )               //fifo disable
      return MEMS_ERROR;
  }

  if(fm == FIFO_BYPASS_MODE)   {
    if( !MAG_ReadReg(CTRL_REG5_A, &value) )
      return MEMS_ERROR;
    value &= 0xBF;
    value |= MEMS_SET<<FIFO_EN;
    if( !MAG_WriteReg(CTRL_REG5_A, value) )               //fifo enable
      return MEMS_ERROR;

    if( !MAG_ReadReg(FIFO_CTRL_REG_A, &value) )
      return MEMS_ERROR;
    value &= 0x1f;
    value |= (fm<<FM);                     //fifo mode configuration
    if( !MAG_WriteReg(FIFO_CTRL_REG_A, value) )
      return MEMS_ERROR;
  }

  if(fm == FIFO_MODE)   {
    if( !MAG_ReadReg(CTRL_REG5_A, &value) )
      return MEMS_ERROR;
    value &= 0xBF;
    value |= MEMS_SET<<FIFO_EN;
    if( !MAG_WriteReg(CTRL_REG5_A, value) )               //fifo enable
      return MEMS_ERROR;

    if( !MAG_ReadReg(FIFO_CTRL_REG_A, &value) )
      return MEMS_ERROR;
    value &= 0x1f;
    value |= (fm<<FM);                      //fifo mode configuration
    if( !MAG_WriteReg(FIFO_CTRL_REG_A, value) )
      return MEMS_ERROR;
  }

  if(fm == FIFO_STREAM_MODE)   {
    if( !MAG_ReadReg(CTRL_REG5_A, &value) )
      return MEMS_ERROR;
    value &= 0xBF;
    value |= MEMS_SET<<FIFO_EN;
    if( !MAG_WriteReg(CTRL_REG5_A, value) )               //fifo enable
      return MEMS_ERROR;

    if( !MAG_ReadReg(FIFO_CTRL_REG_A, &value) )
      return MEMS_ERROR;
    value &= 0x1f;
    value |= (fm<<FM);                      //fifo mode configuration
    if( !MAG_WriteReg(FIFO_CTRL_REG_A, value) )
      return MEMS_ERROR;
  }

  if(fm == FIFO_STREAM_TO_FIFO_MODE)   {
    if( !MAG_ReadReg(CTRL_REG5_A, &value) )
      return MEMS_ERROR;
    value &= 0xBF;
    value |= MEMS_SET<<FIFO_EN;
    if( !MAG_WriteReg(CTRL_REG5_A, value) )               //fifo enable
      return MEMS_ERROR;

    if( !MAG_ReadReg(FIFO_CTRL_REG_A, &value) )
      return MEMS_ERROR;
    value &= 0x1f;
    value |= (fm<<FM);                      //fifo mode configuration
    if( !MAG_WriteReg(FIFO_CTRL_REG_A, value) )
      return MEMS_ERROR;
  }

  if(fm == FIFO_BYPASS_TO_STREAM_MODE)   {
     if( !MAG_ReadReg(CTRL_REG5_A, &value) )
       return MEMS_ERROR;
     value &= 0xBF;
     value |= MEMS_SET<<FIFO_EN;
     if( !MAG_WriteReg(CTRL_REG5_A, value) )               //fifo enable
       return MEMS_ERROR;

     if( !MAG_ReadReg(FIFO_CTRL_REG_A, &value) )
       return MEMS_ERROR;
     value &= 0x1f;
     value |= (fm<<FM);                      //fifo mode configuration
     if( !MAG_WriteReg(FIFO_CTRL_REG_A, value) )
       return MEMS_ERROR;
   }
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_SetWaterMark
* Description    : Sets Watermark Value
* Input          : Watermark = [0,31]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_SetWaterMark(u8_t wtm) {
  u8_t value;

  if(wtm > 31)
    return MEMS_ERROR;

  if( !MAG_ReadReg(FIFO_CTRL_REG_A, &value) )
    return MEMS_ERROR;

  value &= 0xE0;
  value |= wtm;

  if( !MAG_WriteReg(FIFO_CTRL_REG_A, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}



/*******************************************************************************
* Function Name  : MAG_GetSatusReg
* Description    : Read the status register
* Input          : char to empity by Status Reg Value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetSatusReg(u8_t* val) {
  if( !MAG_ReadReg(STATUS_REG_A, val) )
      return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : MAG_GetSatusBIT
* Description    : Read the status register BIT
* Input          : STATUS_REG_ZYXOR, STATUS_REG_ZOR, STATUS_REG_YOR, STATUS_REG_XOR,
                   STATUS_REG_ZYXDA, STATUS_REG_ZDA, STATUS_REG_YDA, STATUS_REG_XDA, DATAREADY_BIT
* Output         : status register BIT
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetSatusBit(u8_t statusBIT) {
  u8_t value;

  if( !MAG_ReadReg(STATUS_REG_A, &value) )
      return MEMS_ERROR;

  switch (statusBIT){
    case STATUS_REG_ZYXOR:     if(value &= STATUS_REG_ZYXOR) return MEMS_SUCCESS;
                               else  return MEMS_ERROR;
    case STATUS_REG_ZOR:       if(value &= STATUS_REG_ZOR) return MEMS_SUCCESS;
                               else  return MEMS_ERROR;
    case STATUS_REG_YOR:       if(value &= STATUS_REG_YOR) return MEMS_SUCCESS;
                               else  return MEMS_ERROR;
    case STATUS_REG_XOR:       if(value &= STATUS_REG_XOR) return MEMS_SUCCESS;
                               else  return MEMS_ERROR;
    case STATUS_REG_ZYXDA:     if(value &= STATUS_REG_ZYXDA) return MEMS_SUCCESS;
                               else  return MEMS_ERROR;
    case STATUS_REG_ZDA:       if(value &= STATUS_REG_ZDA) return MEMS_SUCCESS;
                               else  return MEMS_ERROR;
    case STATUS_REG_YDA:       if(value &= STATUS_REG_YDA) return MEMS_SUCCESS;
                               else  return MEMS_ERROR;
    case STATUS_REG_XDA:       if(value &= STATUS_REG_XDA) return MEMS_SUCCESS;
                               else  return MEMS_ERROR;

  }
return MEMS_ERROR;
}


/*******************************************************************************
* Function Name  : MAG_GetInt1Src
* Description    : Reset Interrupt 1 Latching function
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetInt1Src(u8_t* val) {

  if( !MAG_ReadReg(INT1_SRC_A, val) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}

/*******************************************************************************
* Function Name  : MAG_GetInt1SrcBit
* Description    : Reset Interrupt 1 Latching function
* Input          : INT1_SRC_IA, INT1_SRC_ZH, INT1_SRC_ZL, INT1_SRC_YH .....
* Output         : None
* Return         : Status of BIT [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetInt1SrcBit(u8_t statusBIT) {
  u8_t value;

  if( !MAG_ReadReg(INT1_SRC_A, &value) )
      return MEMS_ERROR;

  if(statusBIT == INT_SRC_IA){
    if(value &= INT_SRC_IA)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_ZH){
    if(value &= INT_SRC_ZH)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_ZL){
    if(value &= INT_SRC_ZL)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_YH){
    if(value &= INT_SRC_YH)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_YL){
    if(value &= INT_SRC_YL)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_XH){
    if(value &= INT_SRC_XH)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_XL){
    if(value &= INT_SRC_XL)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }
return MEMS_ERROR;
}

/*******************************************************************************
* Function Name  : MAG_GetInt2SrcBit
* Description    : Reset Interrupt 2 Latching function
* Input          : INT_SRC_IA, INT_SRC_ZH, INT_SRC_ZL, INT_SRC_YH .....
* Output         : None
* Return         : Status of BIT [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetInt2SrcBit(u8_t statusBIT) {
  u8_t value;

  if( !MAG_ReadReg(INT2_SRC_A, &value) )
      return MEMS_ERROR;

  if(statusBIT == INT_SRC_IA){
    if(value &= INT_SRC_IA)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_ZH){
    if(value &= INT_SRC_ZH)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_ZL){
    if(value &= INT_SRC_ZL)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_YH){
    if(value &= INT_SRC_YH)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_YL){
    if(value &= INT_SRC_YL)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_XH){
    if(value &= INT_SRC_XH)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == INT_SRC_XL){
    if(value &= INT_SRC_XL)    return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }
return MEMS_ERROR;
}

/*******************************************************************************
* Function Name  : MAG_GetFifoSourceReg
* Description    : Read Fifo source Register
* Input          : Byte to empity by FIFO source register value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetFifoSourceReg(u8_t* val) {

  if( !MAG_ReadReg(FIFO_SRC_REG_A, val) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}

/*******************************************************************************
* Function Name  : MAG_GetFifoSourceBit
* Description    : Read Fifo WaterMark source bit
* Input          : FIFO_SRC_WTM, FIFO_SRC_OVRUN, FIFO_SRC_EMPTY
* Output         : None
* Return         : Status of BIT [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t MAG_GetFifoSourceBit(u8_t statusBIT){
  u8_t value;

  if( !MAG_ReadReg(FIFO_SRC_REG_A, &value) )
      return MEMS_ERROR;

  if(statusBIT == FIFO_SRC_WTM){
    if(value &= FIFO_SRC_WTM)     return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == FIFO_SRC_OVRUN){
    if(value &= FIFO_SRC_OVRUN)   return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }

  if(statusBIT == FIFO_SRC_EMPTY){
    if(value &= FIFO_SRC_EMPTY)   return MEMS_SUCCESS;
    else  return MEMS_ERROR;
  }
return MEMS_ERROR;
}

/*******************************************************************************
* Function Name  : MAG_GetFifoSourceFSS
* Description    : Read current number of unread samples stored in FIFO
* Input          : Byte to empity by FIFO unread sample value
* Output         : None
* Return         : Status [value of FSS]
*******************************************************************************/
status_t MAG_GetFifoSourceFSS(u8_t* val){
  u8_t value;

  if( !MAG_ReadReg(FIFO_SRC_REG_A, &value) )
    return MEMS_ERROR;

  value &= 0x1F;
  *val = value;

  return MEMS_SUCCESS;
}

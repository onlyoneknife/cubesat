/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : gyro.c
* Author             : MSH Application Team
* Author             : Andrea Labombarda
* Version            : $Revision:$
* Date               : $Date:$
* Description        : L3GD20(H) driver file
*                      
* HISTORY:
* Date              |	Modification                    				|	Author
* 25/01/2012        |	Initial Revision                				|	Andrea Labombarda
* 27/08/2012		|	Modified to support multiple drivers in the same program                |	Antonio Micali
* 07/03/2015		|	Modified to L3GD20H driver for EFM32GG280F1024	|	Brandon Borden
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

/* Includes ------------------------------------------------------------------*/
#include "gyro.h"
#include "spi_mems.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*******************************************************************************
* Function Name		: GYRO_ReadReg
* Description		: Generic Reading function. It must be fullfilled with either
*					: I2C or SPI reading functions					
* Input				: Register Address
* Output			: Data REad
* Return			: None
*******************************************************************************/
u8_t GYRO_ReadReg(u8_t Reg, u8_t* Data) {
  
  //To be completed with either I2c or SPI reading function
  //i.e.: *Data = SPI_Mems_Read_Reg( Reg );
  
  return 1;
}

/*******************************************************************************
* Function Name		: GYRO_WriteReg
* Description		: Generic Writing function. It must be fullfilled with either
*					: I2C or SPI writing function
* Input				: Register Address, Data to be written
* Output			: None
* Return			: None
*******************************************************************************/
u8_t GYRO_WriteReg(u8_t Reg, u8_t Data) {
    
  //To be completed with either I2c or SPI writing function
  //i.e.: SPI_Mems_Write_Reg(Reg, Data);
  
  return 1;
}
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Function Name  : GYRO_SetODR
* Description    : Sets GYRO Output Data Rate
* Input          : Output Data Rate
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetODR(GYRO_ODR_t ov){
  u8_t value;

  if( !GYRO_ReadReg(GYRO_CTRL_REG1, &value) )
    return MEMS_ERROR;

  value &= 0x0f;
  value |= ov<<4;

  if( !GYRO_WriteReg(GYRO_CTRL_REG1, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetMode
* Description    : Sets GYRO Operating Mode
* Input          : Modality (NORMAL, SLEEP, POWER_DOWN)
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetMode(GYRO_Mode_t md) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG1, &value) )
    return MEMS_ERROR;
                  
  switch(md) {
  
  case GYRO_POWER_DOWN:
    value &= 0xF7;
    value |= (MEMS_RESET<<GYRO_PD);
    break;
          
  case GYRO_NORMAL:
    value &= 0xF7;
    value |= (MEMS_SET<<GYRO_PD);
    break;
          
  case GYRO_SLEEP:
    value &= 0xF0;
    value |= ( (MEMS_SET<<GYRO_PD) | (MEMS_RESET<<GYRO_ZEN) | (MEMS_RESET<<GYRO_YEN) | (MEMS_RESET<<GYRO_XEN) );
    break;
          
  default:
    return MEMS_ERROR;
  }
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG1, value) )
    return MEMS_ERROR;
                  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetAxis
* Description    : Enable/Disable GYRO Axis
* Input          : X_ENABLE/X_DISABLE | Y_ENABLE/Y_DISABLE | Z_ENABLE/Z_DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetAxis(GYRO_Axis_t axis) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG1, &value) )
    return MEMS_ERROR;
    
  value &= 0xf8;
  value |= axis;
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG1, value) )
    return MEMS_ERROR;  
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetFullScale
* Description    : Sets the GYRO FullScale
* Input          : FS_250/FS_500/FS_2000
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetFullScale(GYRO_Fullscale_t fs) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG4, &value) )
    return MEMS_ERROR;
                  
  value &= 0xCF;	
  value |= (fs<<GYRO_FS);
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetBDU
* Description    : Enable/Disable Block Data Update Functionality
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetBDU(State_t bdu) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG4, &value) )
    return MEMS_ERROR;
 
  value &= 0x7F;
  value |= (bdu<<GYRO_BDU);

  if( !GYRO_WriteReg(GYRO_CTRL_REG4, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetBLE
* Description    : Set Endianess (MSB/LSB)
* Input          : BLE_LSB / BLE_MSB
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetBLE(GYRO_Endianess_t ble) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG4, &value) )
    return MEMS_ERROR;
                  
  value &= 0xBF;	
  value |= (ble<<GYRO_BLE);
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_HPFEnable
* Description    : Enable/Disable High Pass Filter
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_HPFEnable(State_t hpf) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG5, &value) )
    return MEMS_ERROR;
                  
  value &= 0xEF;
  value |= (hpf<<GYRO_HPEN);
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG5, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetHPFMode
* Description    : Set High Pass Filter Modality
* Input          : HPM_NORMAL_MODE_RES/HPM_REF_SIGNAL/HPM_NORMAL_MODE/HPM_AUTORESET_INT
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetHPFMode(GYRO_HPFMode_t hpf) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG2, &value) )
    return MEMS_ERROR;
                  
  value &= 0xCF;
  value |= (hpf<<GYRO_HPM);
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG2, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetHPFCutOFF
* Description    : Set High Pass CUT OFF Freq
* Input          : HPFCF_0,HPFCF_1,HPFCF_2... See Table 27 of the datasheet
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetHPFCutOFF(GYRO_HPFCutOffFreq_t hpf) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG2, &value) )
    return MEMS_ERROR;
                  
  value &= 0xF0;
  value |= (hpf<<GYRO_HPFC0);
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG2, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
  
}


/*******************************************************************************
* Function Name  : GYRO_SetIntPinMode
* Description    : Set Interrupt Pin Modality (push pull or Open drain)
* Input          : PUSH_PULL/OPEN_DRAIN
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetIntPinMode(GYRO_IntPinMode_t pm) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG3, &value) )
    return MEMS_ERROR;
                  
  value &= 0xEF;
  value |= (pm<<GYRO_PP_OD);
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetInt1Pin
* Description    : Set Interrupt1 pin Function
* Input          : GYRO_I1_ON_PIN_INT1_ENABLE | GYRO_I1_BOOT_ON_INT1 | GYRO_INT1_ACTIVE_HIGH
* example        : GYRO_SetInt1Pin(GYRO_I1_ON_PIN_INT1_ENABLE | GYRO_I1_BOOT_ON_INT1_ENABLE | GYRO_INT1_ACTIVE_LOW)
* to enable Interrupt 1 or Bootsatus on interrupt 1 pin
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetInt1Pin(GYRO_Int1PinConf_t pinConf) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG3, &value) )
    return MEMS_ERROR;
                  
  value &= 0x1F;
  value |= pinConf;
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetInt2Pin
* Description    : Set Interrupt2 pin Function
* Input          : GYRO_I2_DRDY_ON_INT2_ENABLE/DISABLE |
                   GYRO_WTM_ON_INT2_ENABLE/DISABLE |
                   GYRO_OVERRUN_ON_INT2_ENABLE/DISABLE |
                   GYRO_EMPTY_ON_INT2_ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetInt2Pin(GYRO_Int2PinConf_t pinConf) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG3, &value) )
    return MEMS_ERROR;
                  
  value &= 0xF0;
  value |= pinConf;
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG3, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;  
}


/*******************************************************************************
* Function Name  : GYRO_Int1LatchEnable
* Description    : Enable Interrupt 1 Latching function
* Input          : ENABLE/DISABLE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_Int1LatchEnable(State_t latch) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_INT1_CFG, &value) )
    return MEMS_ERROR;
                  
  value &= 0xBF;
  value |= latch<<GYRO_LIR;
  
  if( !GYRO_WriteReg(GYRO_INT1_CFG, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_ResetInt1Latch
* Description    : Reset Interrupt 1 Latching function
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_ResetInt1Latch(void) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_INT1_SRC, &value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetIntConfiguration
* Description    : Interrupt 1 Configuration
* Input          : AND/OR, INT1_LIR ZHIE_ENABLE/DISABLE | INT1_ZLIE_ENABLE/DISABLE...
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetIntConfiguration(GYRO_Int1Conf_t ic) {
  u8_t value;
  
  value = ic;

  if( !GYRO_WriteReg(GYRO_INT1_CFG, value) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetInt1Threshold
* Description    : Sets Interrupt 1 Threshold
* Input          : Threshold = [0,31]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetInt1Threshold(GYRO_IntThsAxis axis, u16_t ths) {
  u8_t value;
  
  switch (axis) {
    
    case GYRO_THS_X:
      //write the threshold LSB
      value = (u8_t)( ths & 0x00ff); 
      if( !GYRO_WriteReg(GYRO_INT1_THS_XL, value) )
        return MEMS_ERROR;
      
      //write the threshold LSB
      value = (u8_t)( ths >> 8); 
      if( !GYRO_WriteReg(GYRO_INT1_THS_XH, value) )
        return MEMS_ERROR;
      
      break;
      
    case GYRO_THS_Y:
      //write the threshold LSB
      value = (u8_t)( ths & 0x00ff); 
      if( !GYRO_WriteReg(GYRO_INT1_THS_YL, value) )
        return MEMS_ERROR;
      
      //write the threshold LSB
      value = (u8_t)( ths >> 8); 
      if( !GYRO_WriteReg(GYRO_INT1_THS_YH, value) )
        return MEMS_ERROR;
      
      break;
      
    case GYRO_THS_Z:
      //write the threshold LSB
      value = (u8_t)( ths & 0x00ff); 
      if( !GYRO_WriteReg(GYRO_INT1_THS_ZL, value) )
        return MEMS_ERROR;
      
      //write the threshold LSB
      value = (u8_t)( ths >> 8); 
      if( !GYRO_WriteReg(GYRO_INT1_THS_ZH, value) )
        return MEMS_ERROR;
      
      break;     

        
  }

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetInt1Duration
* Description    : Sets Interrupt 1 Duration
* Input          : Duration value
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetInt1Duration(GYRO_Int1Conf_t id) {
 
  if (id > 127)
    return MEMS_ERROR;

  if( !GYRO_WriteReg(GYRO_INT1_DURATION, id) )
    return MEMS_ERROR;

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_FIFOModeEnable
* Description    : Sets Fifo Modality
* Input          : 
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_FIFOModeEnable(GYRO_FifoMode_t fm) {
  u8_t value;  
  
  if(fm == GYRO_FIFO_DISABLE) {
    
    if( !GYRO_ReadReg(GYRO_CTRL_REG5, &value) )
      return MEMS_ERROR;
                    
    value &= 0xBF;    
    
    if( !GYRO_WriteReg(GYRO_CTRL_REG5, value) )
      return MEMS_ERROR;
    
  }
  else {
    
    if( !GYRO_ReadReg(GYRO_CTRL_REG5, &value) )
      return MEMS_ERROR;
                    
    value &= 0xBF;
    value |= MEMS_SET<<GYRO_FIFO_EN;
    
    if( !GYRO_WriteReg(GYRO_CTRL_REG5, value) )
      return MEMS_ERROR;
    
    
    if( !GYRO_ReadReg(GYRO_FIFO_CTRL_REG, &value) )
      return MEMS_ERROR;
    
    value &= 0x1f;
    value |= (fm<<GYRO_FM0);
    
    if( !GYRO_WriteReg(GYRO_FIFO_CTRL_REG, value) )
      return MEMS_ERROR;
  }

  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetWaterMark
* Description    : Sets Watermark Value
* Input          : Watermark = [0,31]
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetWaterMark(u8_t wtm) {
  u8_t value;
  
  if(wtm > 31)
    return MEMS_ERROR;  
  
  if( !GYRO_ReadReg(GYRO_FIFO_CTRL_REG, &value) )
    return MEMS_ERROR;
                  
  value &= 0xE0;
  value |= wtm; 
  
  if( !GYRO_WriteReg(GYRO_FIFO_CTRL_REG, value) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_GetSatusReg
* Description    : Read the status register
* Input          : None
* Output         : status register buffer
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_GetSatusReg(u8_t* buff) {
  if( !GYRO_ReadReg(GYRO_STATUS_REG, buff) )
      return MEMS_ERROR;
  
  return MEMS_SUCCESS;  
}


/*******************************************************************************
* Function Name  : GYRO_GetAngRateRaw
* Description    : Read the Angular Rate Registers
* Input          : None
* Output         : Angular Rate Registers buffer
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_GetAngRateRaw(AxesRaw_t* buff) {
  u8_t valueL;
  u8_t valueH;
  

  if( !GYRO_ReadReg(GYRO_OUT_X_L, &valueL) )
      return MEMS_ERROR;
  
  if( !GYRO_ReadReg(GYRO_OUT_X_H, &valueH) )
      return MEMS_ERROR;
  
  buff->AXIS_X = (i16_t)( (valueH << 8) | valueL );
  
  if( !GYRO_ReadReg(GYRO_OUT_Y_L, &valueL) )
      return MEMS_ERROR;
  
  if( !GYRO_ReadReg(GYRO_OUT_Y_H, &valueH) )
      return MEMS_ERROR;
  
  buff->AXIS_Y = (i16_t)( (valueH << 8) | valueL );
  
   if( !GYRO_ReadReg(GYRO_OUT_Z_L, &valueL) )
      return MEMS_ERROR;
  
  if( !GYRO_ReadReg(GYRO_OUT_Z_H, &valueH) )
      return MEMS_ERROR;
  
  buff->AXIS_Z = (i16_t)( (valueH << 8) | valueL );
  
  return MEMS_SUCCESS;  
}


/*******************************************************************************
* Function Name  : GYRO_GetInt1Src
* Description    : Reset Interrupt 1 Latching function
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_GetInt1Src(u8_t* buff) {
  
  if( !GYRO_ReadReg(GYRO_INT1_SRC, buff) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_GetFifoSourceReg
* Description    : Read Fifo source Register
* Input          : None
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_GetFifoSourceReg(u8_t* buff) {
  
  if( !GYRO_ReadReg(GYRO_FIFO_SRC_REG, buff) )
    return MEMS_ERROR;
  
  return MEMS_SUCCESS;
}


/*******************************************************************************
* Function Name  : GYRO_SetOutputDataAndFifoFilters
* Description    : ENABLE/DISABLE HIGH PASS and LOW PASS filters applied to output and fifo registers
*                : See Table 8 of AN3393 for more details
* Input          : GYRO_NONE, GYRO_HPH, GYRO_LPF2, GYRO_HPFLPF2
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetOutputDataAndFifoFilters(GYRO_HPF_LPF2_Enable hpf){
  u8_t value;
  
  //HPF
  if( !GYRO_ReadReg(GYRO_CTRL_REG5, &value) )
    return MEMS_ERROR;
  
  switch(hpf) {
    
  case GYRO_NONE:
    value &= 0xfc;
    value |= 0x00; //hpen = x, Out_sel_1 = 0, Out_sel_0 = 0
    break;
    
  case GYRO_HPF:
    value &= 0xfc;
    value |= 0x01; //hpen = x, Out_sel_1 = 0, Out_sel_0 = 1
    break;

  case GYRO_LPF2:
    value &= 0xed;
    value |= 0x02; //hpen = 0, Out_sel_1 = 1, Out_sel_0 = x
    break;    
   
  case GYRO_HPFLPF2:
    value &= 0xed;
    value |= 0x12; //hpen = 1, Out_sel_1 = 1, Out_sel_0 = x
    break;    
  }
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG5, value) )
    return MEMS_ERROR;
  
  
  return MEMS_SUCCESS;
  
}


/*******************************************************************************
* Function Name  : GYRO_SetInt1Filters
* Description    : ENABLE/DISABLE HIGH PASS and LOW PASS filters applied to Int1 circuitery
*                : See Table 9 of AN3393 for more details
* Input          : NONE, HPH, LPF2, HPFLPF2
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetInt1Filters(GYRO_HPF_LPF2_Enable hpf){
  u8_t value;
  
  //HPF
  if( !GYRO_ReadReg(GYRO_CTRL_REG5, &value) )
    return MEMS_ERROR;
  
  switch(hpf) {
    
  case GYRO_NONE:
    value &= 0xf3;
    value |= 0x00<<GYRO_INT1_SEL0; //hpen = x, Int1_sel_1 = 0, Int1_sel_0 = 0
    break;
    
  case GYRO_HPF:
    value &= 0xf3;
    value |= 0x01<<GYRO_INT1_SEL0; //hpen = x, Int1_sel_1 = 0, Int1_sel_0 = 1
    break;

  case GYRO_LPF2:
    value &= 0xe7;
    value |= 0x02<<GYRO_INT1_SEL0; //hpen = 0, Int1_sel_1 = 1, Int1_sel_0 = x
    break;    
   
  case GYRO_HPFLPF2:
    value &= 0xe7;
    value |= 0x01<<GYRO_HPEN;
    value |= 0x02<<GYRO_INT1_SEL0; //hpen = 1, Int1_sel_1 = 1, Int1_sel_0 = x
    break;    
  }
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG5, value) )
    return MEMS_ERROR;
  
  
  return MEMS_SUCCESS;
  
}


/*******************************************************************************
* Function Name  : GYRO_SetSPIInterface
* Description    : Set SPI mode: 3 Wire Interface OR 4 Wire Interface
* Input          : GYRO_SPI_3_WIRE, GYRO_SPI_4_WIRE
* Output         : None
* Return         : Status [MEMS_ERROR, MEMS_SUCCESS]
*******************************************************************************/
status_t GYRO_SetSPIInterface(GYRO_SPIMode_t spi) {
  u8_t value;
  
  if( !GYRO_ReadReg(GYRO_CTRL_REG4, &value) )
    return MEMS_ERROR;
                  
  value &= 0xFE;
  value |= spi<<GYRO_SIM;
  
  if( !GYRO_WriteReg(GYRO_CTRL_REG4, value) )
    return MEMS_ERROR;
  
  
  return MEMS_SUCCESS;
}

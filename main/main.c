/* System Includes */
#include <stdio.h>
#include <stdint.h>

/* EFM32 EMLIB Includes */
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_usart.h"

/* EFM32 Driver Includes */
#include "diskio.h"
#include "microsd.h"
#include "ff.h"

/* Ram buffers
 * BUFFERSIZE should be between 512 and 1024, depending on available ram *****/
#define  BUFFERSIZE      1024
/* Filename to open/write/read from SD-card */
#define   TEST_FILENAME    "test.txt"

FIL fsrc;			            	  /* File objects */
FATFS    Fatfs;			        	  /* File system specific */
FRESULT  res;				          /* FatFs function common result code */
UINT     br, bw;			          /* File read/write count */
DSTATUS  resCard;		              /* SDcard status */
int8_t   ramBufferWrite[BUFFERSIZE];  /* Temporary buffer for write file */
int8_t   ramBufferRead[BUFFERSIZE];	  /* Temporary buffer for read file */
int8_t   StringBuffer[] = "hello";

/***************************************************************************//**
 * @brief
 *   This function is required by the FAT file system in order to provide
 *   timestamps for created files. Since this example does not include a
 *   reliable clock we hardcode a value here.
 *
 *   Refer to drivers/fatfs/doc/en/fattime.html for the format of this DWORD.
 * @return
 *    A DWORD containing the current time and date as a packed datastructure.
 ******************************************************************************/
DWORD get_fattime(void)
{
  return (28 << 25) | (2 << 21) | (1 << 16);
}

/**************************************************************************//**
 * @brief Initialize drivers
 *****************************************************************************/
void DRIVERS_Init(void)
{

  /* Using HFRCO at 14MHz as high frequency clock, HFCLK */
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);

  /* Enable clock for USART1 */
  CMU_ClockEnable(cmuClock_USART1, true);

  /* Enable clock for GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Initialize USART1 */
  USART_InitSync_TypeDef initsync = USART_INITSYNC_DEFAULT;

  initsync.baudrate              = 115200;
  initsync.databits              = usartDatabits8;
  initsync.master                = 1;
  initsync.msbf                  = 1;
  initsync.clockMode             = usartClockMode0;
#if defined( USART_INPUT_RXPRS ) && defined( USART_TRIGCTRL_AUTOTXTEN )
  initsync.prsRxEnable           = 0;
  initsync.prsRxCh               = 0;
  initsync.autoTx                = 0;
#endif

  USART_InitSync(USART1, &initsync);

  USART_PrsTriggerInit_TypeDef initprs = USART_INITPRSTRIGGER_DEFAULT;

  initprs.rxTriggerEnable        = 0;
  initprs.txTriggerEnable        = 0;
  initprs.prsTriggerChannel      = usartPrsTriggerCh0;

  USART_InitPrsTrigger(USART1, &initprs);

  /* Port B Configuration */
  /* Pin PB7 is configured to Push-pull */
  GPIO->P[1].MODEL = (GPIO->P[1].MODEL & ~_GPIO_P_MODEL_MODE7_MASK) | GPIO_P_MODEL_MODE7_PUSHPULL;
  GPIO->P[1].DOUT |= (1 << 7);

  /* Pin PB8 is configured to Push-pull */
  GPIO->P[1].MODEH = (GPIO->P[1].MODEH & ~_GPIO_P_MODEH_MODE8_MASK) | GPIO_P_MODEH_MODE8_PUSHPULL;
  GPIO->P[1].DOUT |= (1 << 8);

  /* Port C Configuration */
  /* Pin PC0 is configured to Push-pull */
  GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE0_MASK) | GPIO_P_MODEL_MODE0_PUSHPULL;
  GPIO->P[2].DOUT |= (1 << 0);

  /* Pin PC1 is configured to Input enabled with filter */
  GPIO->P[2].MODEL = (GPIO->P[2].MODEL & ~_GPIO_P_MODEL_MODE1_MASK) | GPIO_P_MODEL_MODE1_INPUT;
  GPIO->P[2].DOUT |= (1 << 1);

  /*Route Configuration */
  USART1->ROUTE |= USART_ROUTE_CLKPEN | USART_ROUTE_CSPEN | USART_ROUTE_RXPEN |
	  USART_ROUTE_TXPEN;

}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{

  int16_t i;
  int16_t filecounter;

  /* Initialize EFM32 Chip Settings */
  CHIP_Init();

  /* Initialize Hardware Drivers */
  DRIVERS_Init();

  /* Initialize filesystem */
  res = f_mount(0, &Fatfs);
  if (res != FR_OK)
  {
    /* Error.No micro-SD with FAT32 is present */
    while(1);
  }

  /*Step4*/
  /* Open  the file for write */
  res = f_open(&fsrc, TEST_FILENAME,  FA_WRITE);
  if (res != FR_OK)
  {
    /*  If file does not exist create it*/
    res = f_open(&fsrc, TEST_FILENAME, FA_CREATE_ALWAYS | FA_WRITE );
    if (res != FR_OK)
    {
      /* Error. Cannot create the file */
      while(1);
    }
  }

  /*Step5*/
  /*Set the file write pointer to first location */
  res = f_lseek(&fsrc, 0);
  if (res != FR_OK)
  {
    /* Error. Cannot set the file write pointer */
    while(1);
  }

  /*Step6*/
  /*Write a buffer to file*/
  res = f_write(&fsrc, ramBufferWrite, filecounter, &bw);
  if ((res != FR_OK) || (filecounter != bw))
  {
    /* Error. Cannot write the file */
  while(1);
  }

  /*Step7*/
  /* Close the file */
  f_close(&fsrc);
  if (res != FR_OK)
  {
    /* Error. Cannot close the file */
    while(1);
  }

  /*Step8*/
  /* Open the file for read */
  res = f_open(&fsrc, TEST_FILENAME,  FA_READ);
  if (res != FR_OK)
  {
    /* Error. Cannot create the file */
    while(1);
  }

  /*Step9*/
  /*Set the file read pointer to first location */
  res = f_lseek(&fsrc, 0);
  if (res != FR_OK)
  {
    /* Error. Cannot set the file pointer */
    while(1);
  }

  /*Step10*/
  /* Read some data from file */
  res = f_read(&fsrc, ramBufferRead, filecounter, &br);
  if ((res != FR_OK) || (filecounter != br))
  {
    /* Error. Cannot read the file */
    while(1);
  }

  /*Step11*/
  /* Close the file */
  f_close(&fsrc);
  if (res != FR_OK)
  {
    /* Error. Cannot close the file */
    while(1);
  }

  /*Step12*/
  /*Compare ramBufferWrite and ramBufferRead */
  for(i = 0; i < filecounter ; i++)
  {
    if ((ramBufferWrite[i]) != (ramBufferRead[i]))
    {
      /* Error compare buffers*/
      while(1);
    }
  }

  /* Infinite loop */
  /*If trapped here then write and read functions were passed */
  for( ;; ) { /* do nothing */ }

}
















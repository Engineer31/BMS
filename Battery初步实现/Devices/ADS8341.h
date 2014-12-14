/*******************************************************************************
* 文件名	: ADS8341.h
* 作者		: Yang
* 版本		: V1.0.0
* 创建时间	: 09/23/1992
* 描述		: 
*******************************************************************************/

#ifndef _ADS8341_H
#define _ADS8341_H

/* Includes ------------------------------------------------------------------*/
#include "Stm32_Driver.h"

/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

//platform
#define ADS8341_CS_PORT GPIOC
#define ADS8341_CS_PIN	GPIO_Pin_7
#define ADS8341_SPI_CHANNEL 1

#define ADS8341_CS_INIT	PortPin_Init(ADS8341_CS_PORT,ADS8341_CS_PIN)
#define ADS8341_CS_HIGH PortPin_Write(ADS8341_CS_PORT,ADS8341_CS_PIN,1)
#define ADS8341_CS_LOW PortPin_Write(ADS8341_CS_PORT,ADS8341_CS_PIN,0)

#define ADS8341_VREF 4096 //Vref 电压 单位mv

/* Exported functions ------------------------------------------------------- */
extern void ADS8341_Init(void);
extern U16 ADS8341_GetChannelData(U8 ch);

#endif

/*****************************END OF FILE**************************************/

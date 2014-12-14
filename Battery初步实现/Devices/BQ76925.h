/*******************************************************************************
* 文件名       	: BQ76925.h
* 作者		: Yang
* 版本		: V1.0.0
* 创建时间	: 10/13/2014
* 描述		: 
*******************************************************************************/

#ifndef _BQ76925_H
#define _BQ76925_H

/* Includes ------------------------------------------------------------------*/
#include"Stm32_Driver.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	U8 VC_GC_4[6];
	U8 VC_OC_4[6];
	
	U8 VC_GAIN_CORR[6];
	U8 VC_OFFSET_CORR[6];
	
	U8 VREF_GC_4;
	U8 VREF_OC_4;
	U8 VREF_OC_5;

	U8 VREF_GAIN_CORR;
	U8 VREF_OFFSET_CORR;
			
}BQ76925_CALStruct;

/* Exported macro ------------------------------------------------------------*/
#define BQ76925_I2C_CHANNEL	1

#define BQ76925_I2C_GROUP_ADDR	0x0100
#define BQ76925_I2C_READ_ADDR	0x0001
#define BQ76925_I2C_WRITE_ADDR 	0x0000

#define BQ76925_STATUS_ADDR	0x00
#define BQ76925_CELL_CTL_ADDR 0x01
#define BQ76925_BAT_CTL_ADDR 0x02
#define BQ76925_CONFIG_1_CTL_ADDR 0x03
#define BQ76925_CONFIG_2_CTL_ADDR 0x04
#define BQ76925_POWER_CTL_ADDR 0x05
#define BQ76925_CHIP_ID_ADDR 0x07
#define BQ76925_VREF_CAL_ADDR 0x10
#define BQ76925_VC1_CAL_ADDR 0x11
#define BQ76925_VC2_CAL_ADDR 0x12
#define BQ76925_VC3_CAL_ADDR 0x13
#define BQ76925_VC4_CAL_ADDR 0x14
#define BQ76925_VC5_CAL_ADDR 0x15
#define BQ76925_VC6_CAL_ADDR 0x16
#define BQ76925_VC_CAL_EXT_1_ADDR 0x17
#define BQ76925_VC_CAL_EXT_2_ADDR 0x18
#define BQ76925_VREF_CAL_EXT_ADDR 0x1B

#define BQ76925_STATUS_POWERON	0x00 //Power ON

#define BQ76925_CELL_CTL_VSS 0x00 //Vcout Pin output VSS
#define BQ76925_CELL_CTL_VC1 0x10 //Vcout Pin output VC1
#define BQ76925_CELL_CTL_VC2 0x11 //Vcout Pin output VC2
#define BQ76925_CELL_CTL_VC3 0x12 //Vcout Pin output VC3
#define BQ76925_CELL_CTL_VC4 0x13 //Vcout Pin output VC4
#define BQ76925_CELL_CTL_VC5 0x14 //Vcout Pin output VC5
#define BQ76925_CELL_CTL_VC6 0x15 //Vcout Pin output VC6
#define BQ76925_CELL_CTL_VTEMP 0x16 //Vcout Pin output VTemp
#define BQ76925_CELL_CTL_HIZ 0x17 //Vcout Pin output HIZ
#define BQ76925_CELL_CTL_VREF1 0x20 //Vcout Pin output Vref X 0.5
#define BQ76925_CELL_CTL_VREF2 0x30 //Vcout Pin output Vref X 0.85

#define BQ76925_BAT_CTL_WRITE 0x00 //CELL Blance set
#define BQ76925_CONFIG_1_CTL_WRITE 0x00 //I Config
#define BQ76925_CONFIG_2_CTL_REF30 0x01  //Set Vref 3.0V
#define BQ76925_CONFIG_2_CTL_CRC 0x00 //Diable  CRC
#define BQ76925_POWER_CTL_SLEEP 0x80 //Set Device Sleep
#define BQ76925_POWER_CTL_VC_EN 0x04 //Cell amplifier is enabled
#define BQ76925_POWER_CTL_VT_EN 0x02 //VTB pin is internally switched to the V3P3 voltage
#define BQ76925_POWER_REF_EN 0x01 //The 1.5 / 3.0 V reference is enabled

/* Exported functions ------------------------------------------------------- */
extern void BQ76925_Init(void);
extern void BQ76925_SetVtemp(void);
extern void BQ76925_SetVCx(u8 vc_channel);
extern U16 BQ76925_GetVCx(U8 vc_channel,U16 vcout,U16 vref);
extern void BQ76925_Sleep(void);
extern void BQ76925_PowerOn(void);

#endif

/*****************************END OF FILE**************************************/

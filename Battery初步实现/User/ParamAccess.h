/*******************************************************************************
* 文件名	: ParamAccess.h
* 作者		: Yang
* 版本		: V1.0.0
* 创建时间	: 10/16/2014
* 描述		: 系统参数的存储 与 读取
*******************************************************************************/

#ifndef _PARAM_ACCESS_
#define _PARAM_ACCESS_

/* Includes ------------------------------------------------------------------*/
#include "Stm32_Driver.h"
#include "Test.h"

/* Exported types ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define LOW_LINE_OCV 2800

#define START_ADDR (0x8000000 | 0x30000)

/*存储状态*/
#define STATE_ADDR	 (START_ADDR | (0x0F<<11))	

/*内阻存储*/
#define TEMP_RI_STATE_ADDR  (START_ADDR | (0<<11)) 	//TEMP存储状态
#define TEMP10_RI_STATE_ADDR  (START_ADDR | (0<<11))+2 //TEMP10存储状态
#define TEMP0_RI_STATE_ADDR  (START_ADDR | (0<<11))+4  //TEMP0存储状态

#define TEMP_RI_ADDR 		(START_ADDR | (1<<11))  //常温内阻存储
#define TEMP10_RI_ADDR 		(START_ADDR | (2<<11))//10度时的内阻
#define TEMP0_RI_ADDR		(START_ADDR | (3<<11))//0度时的内阻

/*OCV_SOC数据表*/
#define OCV_SOC_ADDR	(START_ADDR | (0x0B<<11))		 //OCV SOC	2.80V 对应 (0x8000000 | 0x3B000),2.81V (0x8000000 | 0x3B004)


#define Qmax_ADDR	(START_ADDR | (0x0C<<11)|(0x00<<10))
#define AEG_ADDR	(START_ADDR | (0x0D<<11)) //使用次数

#define RI_SHEET_ADDR	(START_ADDR | 0x01<<12)




/* Exported functions ------------------------------------------------------- */
/*参数初始化*/

/*存储状态*/
/* Age Qmax OCV_SOC Ri*/
extern U16 Read_Store_State(void);
extern void Store_State(U16 data);	

/*内阻表*/
extern void Store_Ri(U16* pdata,U16 length);
extern void Store_Init_Ri(U16 temp,U16 r);
extern U16 Read_Ri(U16 temp,U16 soc);

/*OCV，SOC表*/
extern void Store_OCV_SOC(U16 ocv,U16 soc);	
extern U16 Read_OCV_SOC(U16 ocv);

extern U16 OCVtoSOC(U16 ocv);
extern U16 SOCtoOCV(U16 soc);

/*Qmax*/
extern void Store_Qmax(U16 qmax);			 
extern U16 Read_Qmax(void);

/*age,使用次数*/
extern void Store_Age(U16 age);					
extern U16 Read_Age(void);

#endif

/*****************************END OF FILE**************************************/

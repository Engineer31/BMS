#ifndef _LIBAT_H
#define _LIBAT_H

#include "ParamAccess.h"
#include "GetSensor.h"
#include "SystemState.h"
#include "Function.h"

#include "Test.h"

/*锂电池单体数量*/
#define BAT_NUMBER 5

#define POL_TIME  10 //极化时间

/*工作模式*/
#define WAIT_MODE  0x00  //闲置状态
#define CHARGE_MODE 0x01  //充电状态
#define DISCHARGE_MODE 0x02	//放电状态

#define NORMAL_RES	1000
#define NORMAL_TEMP 200

#define EDV 3000  //放电终止电压3.000V
#define UDV 4190  //充电终止电压4.190V

typedef struct
{
	U32 Current;	 //mA
	U16 TotalVotagle;  //总电压
	U16 SOC;
	U16 Votagle[BAT_NUMBER]; //单体电压
	U16	Temp;		//0.1摄氏度	
	U16 Age;		 //使用次数
	F32 Q;
	F32 Quse;
	F32 Qmax;		//最大容量，单位mah
    
	U16 R;			//内阻 单位 0.01毫欧

	U32 Low_I;		//预留 放电电流 
	U32 Low_t;		//预留 放电时间
}PackLiBATStruct;

typedef struct
{
	U16 Temp;
	U16 SOC;
	U32 R;
}USE_R_Struct;

extern void LiBAT_Init(void);
extern void LiBAT_I_Integral(U32 time);
extern void LiBAT_Low_V(void); 
extern void LiBAT_Update(void);
extern void LiBAT_ShowQ(void);
extern void LiBAT_Send(void);
extern U16 LiBAT_OCV2SOC(U16 ocv);
extern U16 LiBAT_SOC2OCV(U16 soc);
extern void LiBAT_GetSensor(void);

extern PackLiBATStruct LiBATPack;
extern void LiBAT_Mode(void);
extern U8 LiBAT_EndWork(void);
void LiBAT_UpdateRi(void);
F32 LiBAT_GetQuse(void);

extern void LiBAT_InitRiSheet(void);

extern void LiBAT_PrintR(void);

extern void LiBAT_PrintOCVSOC(void);


#endif

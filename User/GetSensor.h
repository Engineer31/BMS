/*******************************************************************************
* 文件名	: GetSensor.h
* 作者		: Yang
* 版本		: V1.0.0
* 创建时间	: 10/13/2014
* 描述		: 获取传感器数据：（电池电流、电压、温度等）
*******************************************************************************/
#ifndef GET_SENSOR_H
#define GET_SENSOR_H

#include "Devices.h"

extern U32 Get_Current(void);
extern U16 Get_Votagle(U8 number);
extern U16 Get_Temp(void);

#endif

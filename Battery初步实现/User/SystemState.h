/*******************************************************************************
* 文件名	: SystemState.h
* 作者		: Yang
* 版本		: V1.0.0
* 创建时间	: 10/16/2014
* 描述		: 系统状态指示
*******************************************************************************/
#ifndef SYS_STATE
#define SYS_STATE

#include "Devices.h"

#define NORMAL_STATE
#define OPREATE_ERROR 	 {LED_OFF(LED1 | LED2);LED_ON(LED3);}  //操作错误，LED1 LED2灭 ， LED3 亮

#endif

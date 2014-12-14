#ifndef _USER_H
#define _USER_H

#include"Devices.h"
#include"ParamAccess.h"
#include"Function.h"
#include"LiBAT.h"
#include "Test.h"


#define TIME2_INTERRUPT_TIME 10
#define TIME3_INTERRUPT_TIME 500
#define TIME4_INTERRUPT_TIME 1000

void SysDriverInit(void);
void UPort1_RxDataHandler(void);

void Timer2_InterruptHandler(void);
void Timer3_InterruptHandler(void);
void Timer4_InterruptHandler(void);

#endif

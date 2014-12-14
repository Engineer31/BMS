#ifndef _CAN_H
#define _CAN_H

#include "CAN1.h"
#include "CAN2.h"

typedef struct
{
    U8 i;
} CANStruct;

extern Bool CAN_DriverInit(CANStruct *, U8);

#endif

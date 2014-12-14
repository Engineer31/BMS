#include "CAN.h"

Bool CAN_DriverInit(CANStruct *can , U8 ch)
{
    if(ch == 1)
    {
        CAN1_HardwareInit();
    }
    else if(ch == 2)
    {
    }
    else
    {
        return FALSE;
    }
}

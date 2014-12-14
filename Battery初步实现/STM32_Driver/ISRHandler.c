#include "ISRHandler.h"
#include <string.h>

ISRHandlerStruct ISRHandler;



void ISRHandler_Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
}


#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "TypeDef.h"
#include "memory.h"
#include "Queue.h"

U16 Filter(U16 *pdata, U16 count);

extern U8 CheckSum(U8 *, U8); //校验和
extern void Data_Package(QueueStruct* pQueue,U8* data,U16* data_length);	//数据打包函数
extern void Data_UNPackage(U8* data,U16* data_length);//数据解包函数 ,解包后原数据丢弃，每次解一个数据包，

#endif

//Just t
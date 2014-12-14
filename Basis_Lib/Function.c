#include "Function.h"
extern U8 Rx_Data[512];
extern U8 Rx_Data_Count;
U16 Filter(U16 *pdata, U16 count)
{
    U64 sum = 0;
    U16 i = 0;

    for(i = 0; i < count; i++)
    {
        sum += pdata[i];
    }
    return (sum / count);
}

U8 CheckSum(U8 *data, U8 count)
{
    U8 i = 0;
    U8 sum = 0;

    for(i = 0; i < count; i++)
    {
        sum += data[i];
    }

    return sum;
}

void Data_Package(QueueStruct* pQueue,U8* data,U16* data_length)
{
	 U8 sum;
	 U8 i;

	 sum=0;

	 data[0]=0xA5;
	 data[1]=0x5A;
	 data[2]=pQueue->Count;

	 sum=data[0]+data[1]+data[2];

	 for(i=0;i<(Rx_Data_Count);i++)
	 {
	 	data[3+i]=pQueue->Data[i];
	 	sum+=pQueue->Data[i];
	 }

	 data[3+i]=sum;
	 *data_length=4+i;
}

void Data_UNPackage(U8* data,U16* data_length)
{
	U8 i=0;
	U8 j=0;
	U8 k;
	U8 Length=0;

	while(1)
	{
      if((Rx_Data_Count)<5)	  //数据量不足，退出
	      break;

     /*寻找帧头*/
	 for(i=0;i<(Rx_Data_Count)-1;i++)
	 {
	     if((Rx_Data[i]==0xA5)&&(Rx_Data[i+1]==0x5A))
		 {
		     
		     break;
		 }
	 }
	 
	 /*去除废数据*/	
	 Rx_Data_Count=(Rx_Data_Count)-i;
	 for(j=0;j<(Rx_Data_Count);j++)
	 {
	     Rx_Data[j]=Rx_Data[i+j]; 
	 }

	 /*获取包数据长度（总长度）*/
	 if((Rx_Data_Count)>2)
	 {
     	Length= Rx_Data[2];
	 }

	 Length=Length-3;				 //匹配

	 /*解包*/
	 if((Rx_Data_Count)>=(Length+3))
	 {


	    if(Rx_Data[3+Length]==CheckSum(Rx_Data,2+Length))
	    {
		   /*解包数据进队列*/
		    for(k=0;k<Length-1;k++)
			{
		   		data[k]=(Rx_Data[3+k]);
				
			}
			*data_length=Length-1;
	    }

		/*丢包*/
		for(i=0;i<((Rx_Data_Count)-1);i++)
		{
			Rx_Data[i]=Rx_Data[i+1];
		}
	 }
	}
	
}





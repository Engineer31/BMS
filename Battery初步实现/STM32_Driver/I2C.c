#include "I2C.h"

void I2C_DriverInit(u8 ch)
{
	if(ch==1)
	{
		I2C1_HardwareInit();
	}
	else if(ch==2)
	{

	}
	else 
	{
	}
}

void I2C_WriteByte(u8 ch,u8 DevAddr,u8 WData)
{
	if(ch==1)
	{
		I2C1_WriteByte(DevAddr,WData);
	}
	else if(ch==2)
	{

	}
	else 
	{
	}
}

void I2C_Read(u8 ch,u8 DevAddr,u8* pBuffer,u16 no)
{
	if(ch==1)
	{
		I2C1_Read(DevAddr,pBuffer,no);
	}
	else if(ch==2)
	{

	}
	else 
	{
	}
}

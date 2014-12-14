/*******************************************************************************
* 文件名  	: BQ76925.c
* 作者		: Yang
* 版本		: V1.0.0
* 创建时间	: 10/13/2014
* 描述		: 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "BQ76925.h"

BQ76925_CALStruct Cal_Param;
/* Function ------------------------------------------------------------------*/
void BQ76925_Init(void)
{
	U8 i;
	U8 j=7;
	U8 data8;
	U8 addr;

	/*I2C init*/
	I2C_DriverInit(BQ76925_I2C_CHANNEL);

	/*PoweOn*/
	I2C_WriteByte(BQ76925_I2C_CHANNEL,(0x20 | BQ76925_STATUS_ADDR),BQ76925_STATUS_POWERON);
	
	/*Set Vref 3.0V, NO CRC*/
	I2C_WriteByte(BQ76925_I2C_CHANNEL,
				(0x20 | BQ76925_CONFIG_2_CTL_ADDR),
					BQ76925_CONFIG_2_CTL_REF30 | BQ76925_CONFIG_2_CTL_CRC);	

	/*VC Enable,VTemp Enable, VRef Enable*/
	I2C_WriteByte(BQ76925_I2C_CHANNEL,
				(0x20 | BQ76925_POWER_CTL_ADDR),
					BQ76925_POWER_CTL_VC_EN | BQ76925_POWER_CTL_VT_EN | BQ76925_POWER_REF_EN);
   
   /*系统初始校准参数读取*/
   	I2C_Read(BQ76925_I2C_CHANNEL,
					(0x20 | BQ76925_VC_CAL_EXT_1_ADDR),
					&data8,1);

	Cal_Param.VC_OC_4[0] = (data8>>7)&0x01;
	Cal_Param.VC_GC_4[0] = (data8>>6)&0x01;

	Cal_Param.VC_OC_4[1] = (data8>>5)&0x01;
	Cal_Param.VC_GC_4[1] = (data8>>4)&0x01;

	I2C_Read(BQ76925_I2C_CHANNEL,
					(0x20 | BQ76925_VC_CAL_EXT_2_ADDR),
					&data8,1);
		
   for(i=0;i<4;i++)
   {
   		Cal_Param.VC_OC_4[i+2] = (data8>>(j))&0x01;
		j--;
		Cal_Param.VC_GC_4[i+2] = (data8>>(j))&0x01;	
		j--;
   }
	I2C_Read(BQ76925_I2C_CHANNEL,(0x20 | BQ76925_VREF_CAL_EXT_ADDR),&data8,1);
	Cal_Param.VREF_GC_4=data8&0x01;
	Cal_Param.VREF_OC_4=(data8>>1)&0x01;
	Cal_Param.VREF_OC_5=(data8>>2)&0x01;

	I2C_Read(BQ76925_I2C_CHANNEL,(0x20 | BQ76925_VREF_CAL_ADDR),&data8,1);
	Cal_Param.VREF_GAIN_CORR=data8&0x0F;
	Cal_Param.VREF_OFFSET_CORR=(data8>>4)&0x0F;
	addr=BQ76925_VC1_CAL_ADDR;
	for(i=0;i<6;i++)
	{
		I2C_Read(BQ76925_I2C_CHANNEL,(0x20 | addr),&data8,1);
		Cal_Param.VC_GAIN_CORR[i]=data8&0x0F;
		Cal_Param.VC_OFFSET_CORR[i]=(data8>>4)&0x0F;
		addr++;
	}
	
}

void BQ76925_SetVtemp(void)
{
	I2C_WriteByte(BQ76925_I2C_CHANNEL,
				 (0x20 | BQ76925_CELL_CTL_ADDR),
					BQ76925_CELL_CTL_VTEMP);
}

void BQ76925_SetVCx(u8 vc_channel)
{
	U8 vcx;
	
	if(vc_channel==1)
	{
		vcx=BQ76925_CELL_CTL_VC1;
	}
	else if(vc_channel==2)
	{
		vcx=BQ76925_CELL_CTL_VC2;
	}
	else if(vc_channel==3)
	{
		vcx=BQ76925_CELL_CTL_VC3;
	}
	else if(vc_channel==4)
	{
		vcx=BQ76925_CELL_CTL_VC4;
	}
	else if(vc_channel==5)
	{
		vcx=BQ76925_CELL_CTL_VC5;
	}
	else if(vc_channel==6)
	{
		vcx=BQ76925_CELL_CTL_VC6;
	}
	else
	{
	}

	I2C_WriteByte(BQ76925_I2C_CHANNEL,
				(0x20 | BQ76925_CELL_CTL_ADDR),vcx);	
}

U16 BQ76925_GetVCx(U8 vc_channel,U16 vcout,U16 vref)
{
	U8 i;
	U16 Vvcx;
	S8 VREF_GAIN;
	S8 VREF_OFFSET;
	F64 GC_Vcout;
	F64 OC_Vcout;
	F64 GC_Vref;
	F64 G_Vout=0.6;
	
	i=vc_channel-1;


    if(Cal_Param.VC_GC_4[i]==0)
	{
		GC_Vcout=(Cal_Param.VC_GAIN_CORR[i])*0.001;
	}
	else 
	{
		GC_Vcout=-(0x0F-Cal_Param.VC_GAIN_CORR[i]+1)*0.001;
	}

	if(Cal_Param.VC_OC_4[i]==0)
	{
		OC_Vcout=(Cal_Param.VC_OFFSET_CORR[i])*0.001;
	}
	else
	{
		OC_Vcout=-(0x0F-Cal_Param.VC_OFFSET_CORR[i]+1)*0.001;
	}


	if(Cal_Param.VREF_GC_4==0)
	{
		VREF_GAIN=Cal_Param.VREF_GAIN_CORR;
	}
	else
	{
		VREF_GAIN=-(0x0F-Cal_Param.VREF_GAIN_CORR+1);	
	}

	if(Cal_Param.VREF_OC_5==0)
	{
		VREF_OFFSET=(Cal_Param.VREF_OC_4<<4)+Cal_Param.VREF_OFFSET_CORR;
	}
	else
	{
		VREF_OFFSET=-(0x1F-((Cal_Param.VREF_OC_4<<4)+Cal_Param.VREF_OFFSET_CORR)+1);
	}
	GC_Vref=(1+(VREF_GAIN)*0.001)
			+(VREF_OFFSET)*0.001/vref;

 	Vvcx=((vcout*GC_Vref+OC_Vcout)/G_Vout)*(1+GC_Vcout);	//使用校准参数

	return Vvcx;

}

void BQ76925_Sleep(void)
{
	/*Sleep*/
	I2C_WriteByte(BQ76925_I2C_CHANNEL,
				(0x20 | BQ76925_POWER_CTL_ADDR),
					BQ76925_POWER_CTL_SLEEP);	
}

void BQ76925_PowerOn(void)
{
	/*PoweOn*/
	I2C_WriteByte(BQ76925_I2C_CHANNEL,
				(0x20 | BQ76925_STATUS_ADDR),
					BQ76925_STATUS_POWERON);
}

/*****************************END OF FILE**************************************/

#include "LiBAT.h"							 
PackLiBATStruct	 LiBATPack;
USE_R_Struct USE_R[1001];  
U16 R_COUNT;
U8 WORK_MODE;
U8 POL_STATE;//极化状态标志
U16 Poltime;//极化持续时间
U16 R_Data[1001];
F32 THIS_QUSE;

U16 START_SOC;
U16 END_SOC;

U32 DISCHARGE_TIME;

extern U8 DISCHATGE_TEST;

void LiBAT_Init(void)
{	
    U8 i;
	U16 lowV;

	LiBAT_GetSensor();	 //mA

	LiBATPack.Age=Read_Age();		 //使用次数	
	LiBATPack.Qmax=Read_Qmax();		//最大容量，单位mah

	lowV=LiBATPack.Votagle[0];
	for(i=1;i<BAT_NUMBER;i++)
	{
		if(LiBATPack.Votagle[i]<lowV)
		{
			lowV=LiBATPack.Votagle[i];
		}
	}
	LiBATPack.SOC=LiBAT_OCV2SOC(lowV);	//0.1%
	LiBATPack.Q = (LiBATPack.Qmax)*(LiBATPack.SOC)/1000.0;			//现有容量

	LiBAT_ShowQ();
	THIS_QUSE=0;

	WORK_MODE=WAIT_MODE;
}

void LiBAT_I_Integral(U32 time)
{  
	/*Q更新*/
	if(WORK_MODE==DISCHARGE_MODE)
	{
		LiBATPack.Q-=(1.0*(LiBATPack.Current)*time)/(1000*60*60*1.0);             //(mA ms)-mah
		THIS_QUSE+=(1.0*(LiBATPack.Current)*time)/(1000*60*60*1.0);
	}

}

void LiBAT_GetSensor(void)
{
	U8 i;
	U32 data;

	/*电流更新*/		
	data=Get_Current();
	if(data>140000)
		data=0;
	LiBATPack.Current=data;

	/*单体电压更新*/
	for(i=0;i<BAT_NUMBER;i++)
	{
		LiBATPack.Votagle[i]=Get_Votagle(i+1); 
    }

	/*温度更新*/
	LiBATPack.Temp=Get_Temp();
}


void LiBAT_Update(void)
{
	U8 i;
	U16 ocv;
	U16 lowV;
	U32 r;
	U16 V_SOC;
	U16 I_SOC;

	/*最小单体电压*/
	lowV=LiBATPack.Votagle[0];
	for(i=1;i<BAT_NUMBER;i++)
	{
		if(LiBATPack.Votagle[i]<lowV)
		{
			lowV=LiBATPack.Votagle[i];
		}
	}

	/*总电压更新*/
	LiBATPack.TotalVotagle=0;
	for(i=0;i<BAT_NUMBER;i++)
	{
		LiBATPack.TotalVotagle+=LiBATPack.Votagle[i];
	}

	/*soc更新,Qmax更新，Q更新*/
	LiBATPack.Qmax=Read_Qmax();		//最大容量，单位mah	
	if(WORK_MODE==DISCHARGE_MODE)
	{
		/*放电时间累计*/
		DISCHARGE_TIME++;

		/*积分得到*/
		I_SOC=(LiBATPack.Q/LiBATPack.Qmax)*1000;			//现有容量

		/*内阻估计得到*/
		ocv=lowV*1.0+LiBATPack.Current*Read_Ri(LiBATPack.Temp,LiBATPack.SOC)*0.001/100.0;
		V_SOC=LiBAT_OCV2SOC(ocv);

		/*SOC*/
		LiBATPack.SOC=I_SOC;
		
	}
	else
	{
		if(Poltime>0)
		{
			Poltime--;
			LiBATPack.SOC=(LiBATPack.Q/LiBATPack.Qmax)*1000;
		}
		else
		{
			LiBATPack.SOC=LiBAT_OCV2SOC(lowV);	//0.1%
			LiBATPack.Q = (LiBATPack.Qmax)*(LiBATPack.SOC)/1000.0;	 //现有容量	
		}
	}


	if(WORK_MODE==DISCHARGE_MODE)
	{
		/*此次使用内阻更新*/
		ocv=LiBAT_SOC2OCV(LiBATPack.SOC);	 
		r=((ocv-lowV)*100*1000*1.0/LiBATPack.Current)*BAT_NUMBER; //最大内阻  0.01毫欧单位
    	if(R_COUNT==0)
		{
			USE_R[R_COUNT].Temp=LiBATPack.Temp;
			USE_R[R_COUNT].SOC=LiBATPack.SOC;
			USE_R[R_COUNT].R=r;
			LiBATPack.R=USE_R[R_COUNT].R;
			R_COUNT++;
		}
		else 
		{
			if(LiBATPack.SOC!=USE_R[R_COUNT-1].SOC)
			{
				USE_R[R_COUNT].Temp=LiBATPack.Temp;
				USE_R[R_COUNT].SOC=LiBATPack.SOC;
				USE_R[R_COUNT].R=r;
				LiBATPack.R=USE_R[R_COUNT].R;
				R_COUNT++;	
			}
		}
	}
	
	/*获取可用容量*/
	if(WORK_MODE==DISCHARGE_MODE)
	{
		LiBATPack.Quse=LiBAT_GetQuse();
	}
	else 
	{
		LiBATPack.Quse=LiBATPack.Q;
	}
}

F32 LiBAT_GetQuse(void)
{
	F32 Quse;
	F32 k;
	U16 r;
	U16 i;
	U16 ocv;
	U16 r_end;
	U16 dv;
	
	r=Read_Ri(LiBATPack.Temp,LiBATPack.SOC);
	if(LiBATPack.R>r)
	{
		k=1;
	}
	else
	{
		k=r*1.0/LiBATPack.R;
	}
	
	for(i=0;i<1001;i++)
	{
		ocv=LiBAT_SOC2OCV(i);
		r_end=Read_Ri(LiBATPack.Temp,i);
		r_end=r_end*k;
		dv=LiBATPack.Current*r_end*0.01*0.001;
		if(ocv>=(dv+EDV))
		{
			break;
		}
	}
	Quse=LiBATPack.Q-LiBATPack.Qmax*i*1.0/1000;
			
	return Quse;
}

void LiBAT_Send(void)
{
	U8 data[50] = {0x00};
    U8 i;
	U32 data32;
	U16 data16;

	data[0]=0xA5;
	data[1]=0x5A;
	data[2]=0x26;

	data[3]=0x01; //帧ID
	data[4]=0x01; //使用状态

	data[5]=LiBATPack.SOC;
	data[6]=LiBATPack.SOC>>8;

	data16=LiBATPack.Q;
	data[7]=data16;
	data[8]=data16>>8;

	data16=LiBATPack.Quse;
	data[9]=data16;
	data[10]=data16>>8;

	data[11]=LiBATPack.TotalVotagle;
	data[12]=LiBATPack.TotalVotagle>>8;

	data32=	LiBATPack.Current;
	data[13]=data32;
	data[14]=data32>>8;
	data[15]=data32>>16;
	data[16]=data32>>24;

	for(i=0;i<BAT_NUMBER;i++)
	{
		data[17+2*i]=LiBATPack.Votagle[i];
		data[18+2*i]=LiBATPack.Votagle[i]>>8;
	}

	data[27]=LiBATPack.Age;
	data[28]=LiBATPack.Age>>8;

	data[29]=LiBATPack.Temp;
	data[30]=LiBATPack.Temp>>8;

	data[31]=LiBATPack.R;
	data[32]=LiBATPack.R>>8;

	data16=THIS_QUSE;
	data[33]=data16;
	data[34]=data16>>8;

	data16=LiBATPack.Qmax;
	data[35]=data16;
	data[36]=data16>>8;
	
	data[37]=CheckSum(data,37);

    UART_Write(CHANNEL1, data ,38);
}

void LiBAT_ShowQ(void)
{
	U8 i;

	i=((U16)(((LiBATPack.Q*1.0)/(LiBATPack.Qmax*1.0))*100))/25.0;
	LED_OFF(LED4 | LED5 | LED6 | LED7);

	if(i>=3)
	{
		LED_ON(LED4);
	}

	if(i>=2)
	{
		LED_ON(LED5);
	}

	if(i>=1)
	{
		LED_ON(LED6);
	}

	if(i>=0)
	{
		LED_ON(LED7);
	}
	if(DISCHATGE_TEST==1)
	{
		LED_OFF(LED7);
	}
}

//工作模式判断
void LiBAT_Mode(void)
{
	U16 v1;
	U16 v2;
	U32 current;

	v1=LiBATPack.Votagle[0];
	
	while(1)
	{
		current=LiBATPack.Current;
		v2=LiBATPack.Votagle[0];
		if(v2>(v1+100))
		{
			WORK_MODE=CHARGE_MODE;
			break;
		}
		if((current>500))
		{
			WORK_MODE=DISCHARGE_MODE;
			START_SOC=LiBATPack.SOC;
			break;
		}
	}
}

U8 LiBAT_EndWork(void)
{
	U8 state;
	U16 i;
	U16 j;
	F32 ksoc;
	F32 q;
	U16 lowV;

	state=0;
	ksoc=1;

	/*最小单体电压*/
	lowV=LiBATPack.Votagle[0];
	for(i=1;i<BAT_NUMBER;i++)
	{
		if(LiBATPack.Votagle[i]<lowV)
		{
			lowV=LiBATPack.Votagle[i];
		}
	}

	if(WORK_MODE==DISCHARGE_MODE)
	{
		if(LiBATPack.Current<500 || (lowV<=3000))
		{
			state=1;

			DISCHARGE_TIME=0;//放电时间计数清零

			if(DISCHATGE_TEST==1)
			{
			/*测试状态此次放电结束*/
			
    			/*更新总容量*/
				Delay_s(POL_TIME);
				END_SOC=LiBAT_OCV2SOC(lowV);	
				if(THIS_QUSE>(0.5*LiBATPack.Qmax))
				{
					q=LiBATPack.Qmax;
			  		LiBATPack.Qmax=(THIS_QUSE/(START_SOC-END_SOC))*1000;
					ksoc=q/LiBATPack.Qmax;
					Store_Qmax(LiBATPack.Qmax);
				}
					
				/*记录内阻*/
				for(i=0;i<1001;i++)
				{
					if(i<(U16)(START_SOC-(START_SOC-USE_R[R_COUNT-1].SOC)*ksoc))
					{   
						R_Data[i]=USE_R[R_COUNT-1].R;
					}
					else if(i>(U16)(START_SOC-(START_SOC-USE_R[0].SOC)*ksoc))
					{
						R_Data[i]=USE_R[0].R;
					}
					else
					{
						for(j=0;j<R_COUNT-1;j++)
						{
							if(((U16)(START_SOC-(START_SOC-USE_R[j].SOC)*ksoc)>=i)&&((U16)(START_SOC-(START_SOC-USE_R[j+1].SOC)*ksoc)<=i))
							{
								R_Data[i]=USE_R[j].R;	 	
							}						  
						}
					}
				}
				R_COUNT=0;
				Store_Ri(R_Data,1001);
				DISCHATGE_TEST=0;
				
			}
			else
			{
			/*一般使用状态此次放电结束*/

			 /*考虑其断电的极化*/
			 Poltime=POL_TIME;

			 /*更新内阻*/
			 //LiBAT_UpdateRi();
			}
		}
	}

	if(WORK_MODE==CHARGE_MODE)
	{
		if(LiBATPack.Votagle[0]>UDV)   //用充电电流=0判断
		{
			LiBATPack.Age++;
			Store_Age(LiBATPack.Age);
			state=1;	
		}			
	}
	if(state==1)
	{
		WORK_MODE=WAIT_MODE;
	}

	return state;
} 

void LiBAT_UpdateRi(void)
{
	U16 i;
	F32 k;
	U16 r;

	k=1;
	for(i=R_COUNT/2;i<R_COUNT;i++)
	{
		if(USE_R[i].Temp<20)
		{
			continue;
		}
		r=Read_Ri(USE_R[i].Temp,USE_R[i].SOC);
		if((USE_R[i].R*1.0/r)>k)
		{
			k=(USE_R[i].R*1.0/r);
		}
	}

	for(i=0;i<1001;i++)
	{
		R_Data[i]=k*Read_Ri(250,i);
	}

	Store_Ri(R_Data,1001);			
}

void LiBAT_InitRiSheet(void)
{
	U16 length;
	U16 i;
    
	length=1001;

	for(i=0;i<length;i++)
	{
		R_Data[i]=NORMAL_RES;
	}
	Store_Ri(R_Data,length);				
}	

U16 LiBAT_OCV2SOC(U16 ocv)
{
	U16 soc;
	F32 k;
   	
	k=1000*1.0/(1000-31);
	soc=(OCVtoSOC(ocv)-31)*k;
		
	return soc;
}

U16 LiBAT_SOC2OCV(U16 soc)
{ 
	U16 ocv;
	F32 k;
   	
	k=1000*1.0/(1000-31);
	soc=soc*1.0/k+31;		
	ocv=SOCtoOCV(soc);

	return ocv;

}

void LiBAT_PrintR(void)
{
	U16 i;
	U16 r;

	printf("Ri_Sheet");
	printf("\t\n");
	for(i=0;i<1001;i++)
	{
		r=Read_Ri(250,i);
		printf("%d\t",i);
		printf("%d\t\n",r);		
	} 
	printf("\t\n");
	printf("\t\n");
	printf("\t\n");
		
}

void LiBAT_PrintOCVSOC(void)
{
	U16 i;
	U16 OCV;
	
	printf("OCV_SOC_Sheet");
	printf("\t\n");
	for(i=0;i<1001;i++)
	{
		OCV=LiBAT_SOC2OCV(i);
		printf("%d\t",i);
		printf("%d\t\n",OCV);		
	} 
	printf("\t\n");
	printf("\t\n");
	printf("\t\n");
		
}


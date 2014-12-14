#include "User.h"
U8 SEND_OCV_SOC;
extern F32 THIS_QUSE;
U8 DISCHATGE_TEST;
U8 PRINT_R;
U8 PRINT_OCV_SOC;

int main(void)
{
	SysDriverInit();

	/*系统参数初始化*/
	TIM3_StartTime();//开始读取串口数据
			
	/*锂电池参数初始化*/
	LiBAT_Init();
	TIM2_StartTime();//开始传感器数据采集
	TIM4_StartTime();//电池参数更新及发送，及电量显示

	while(1)
	{
		/*工作模式判断*/
		LiBAT_Mode();

    	while(1)
    	{
			if(LiBAT_EndWork())
				break;
		}
		
	}   
}

void SysDriverInit(void)
{
    /*MCU硬件初始化*/

	/*滴答时钟定时器初始化*/
    SysTick_Init();
	Delay_ms(1000);
   
    /*UART串口初始化*/
    UART_DriverInit(CHANNEL1, 115200, 256);

    UART_DriverInit(CHANNEL2,115200,256);
    
    /*定时器中断初始化*/
    TIM2_InterruptInit(TIME2_INTERRUPT_TIME);
    TIM2_SetTimeInterruptISR(Timer2_InterruptHandler); //

    TIM3_InterruptInit(TIME3_INTERRUPT_TIME);
    TIM3_SetTimeInterruptISR(Timer3_InterruptHandler); //
   
    TIM4_InterruptInit(TIME4_INTERRUPT_TIME);
    TIM4_SetTimeInterruptISR(Timer4_InterruptHandler); //

    /*Devices初始化*/

    /*LED初始化*/
    LED_DriverInit(LED3 | LED4 | LED5 | LED6 | LED7);
	LED_OFF(LED4 | LED5 | LED6 | LED7);

    /*ADS8341初始化*/
	ADS8341_Init();

	/*BQ76925初始化*/
	BQ76925_Init();
}

void Timer2_InterruptHandler(void)
{
	 LiBAT_GetSensor();	  //更新单体电压，电流，温度

  	 LiBAT_I_Integral(TIME2_INTERRUPT_TIME);	//电流积分，更新Q 
}

void Timer3_InterruptHandler(void)
{
	 UPort1_RxDataHandler();  //接收数据处理
}

void Timer4_InterruptHandler(void)
{
	 U16 ocv;

     LiBAT_Update();						//锂电池状态更新 V SOC  
	 LiBAT_Send();	 
	 LiBAT_ShowQ();

	 if(PRINT_R)
	 {
	 	LiBAT_PrintR();
		PRINT_R=0;
	 }
	 
	 if(PRINT_OCV_SOC)
	 {
	 	LiBAT_PrintOCVSOC();
		PRINT_OCV_SOC=0;
	}
}


/*串口1接收数据处理*/
void UPort1_RxDataHandler(void)
{
	U8 data[256];
	U16 length;
	U16 charge;

	Data_UNPackage(data,&length);	 //获取一个解包数据

	if(data[0]!=0x01)
		return;

	/*Low_t Low_I Age Qmax OCV_SOC Ri*/
	if(data[1]==0x00)
	{
	/*清除Flash*/
     Store_State(0x00);

	}
	else if(data[1]==0x01)
	{
	/*配置最大容量*/
		charge=data[3];
		charge=data[2]  | charge<<8;
		Store_Qmax(charge);

	}
	else if(data[1]==0x02)		
	{
	/*配置使用次数*/
		Store_Age(1);
	}
	else if(data[1]==0x30)
	{
	/*获取OCV_SOC数据表*/
		PRINT_OCV_SOC=1;

	 
	}
	else if(data[1]==0x31)
	{
	/*获取Ri表*/
		PRINT_R=1;
	}
	else if(data[1]==0xF0)
	{
	  /*进入放电测试*/
	  	if(data[2]==0x01)
	  	{
		/*第一次放电测试*/
			DISCHATGE_TEST=1;
		}
		else if(data[2]==0x02)
		{
		/*第二次放电测试*/
		}
	}
	else if(data[1]==0xF1)
	{
	   /*退出放电测试*/
	   DISCHATGE_TEST=0;

	}
	else 
	{

	}
}






#include "CAN1.h"

Bool CAN1_HardwareInit(void)
{
    //    GPIO_InitTypeDef       GPIO_InitStructure;
    //	CAN_InitTypeDef        CAN_InitStructure;
    //	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    //	NVIC_InitTypeDef NVIC_InitStructure;
    //
    //  	/*外设时钟设置*/
    //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
    //	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    //
    //  	/*IO设置*/
    //	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
    //	/* Configure CAN pin: RX */									               // PB8
    //    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	             // 上拉输入
    //    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //	GPIO_Init(GPIOB, &GPIO_InitStructure);
    //    /* Configure CAN pin: TX */									               // PB9
    //    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    //    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		         // 复用推挽输出
    //    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //	GPIO_Init(GPIOB, &GPIO_InitStructure);
    //
    //	/*CAN寄存器初始化*/
    //	CAN_DeInit(CAN1);
    //	CAN_StructInit(&CAN_InitStructure);
    //	/*CAN单元初始化*/
    //	CAN_InitStructure.CAN_TTCM=DISABLE;			   //MCR-TTCM  关闭时间触发通信模式使能
    //    CAN_InitStructure.CAN_ABOM=ENABLE;			   //MCR-ABOM  自动离线管理
    //    CAN_InitStructure.CAN_AWUM=ENABLE;			   //MCR-AWUM  使用自动唤醒模式
    //    CAN_InitStructure.CAN_NART=DISABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
    //    CAN_InitStructure.CAN_RFLM=DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文
    //    CAN_InitStructure.CAN_TXFP=DISABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符
    //    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  //正常工作模式
    //    CAN_InitStructure.CAN_SJW=CAN_SJW_2tq;		   //BTR-SJW 重新同步跳跃宽度 2个时间单元
    //    CAN_InitStructure.CAN_BS1=CAN_BS1_6tq;		   //BTR-TS1 时间段1 占用了6个时间单元
    //    CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;		   //BTR-TS1 时间段2 占用了3个时间单元
    //    CAN_InitStructure.CAN_Prescaler =4;		   ////BTR-BRP 波特率分频器  定义了时间单元的时间长度 36/(1+6+3)/4=0.8Mbps
    //	CAN_Init(CAN1, &CAN_InitStructure);
    //
    //	/*CAN过滤器初始化*/
    //	CAN_FilterInitStructure.CAN_FilterNumber=0;						//过滤器组0
    //    CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;	//工作在标识符屏蔽位模式
    //	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;	//过滤器位宽为单个32位。
    //	/* 使能报文标示符过滤器按照标示符的内容进行比对过滤，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
    //    CAN_FilterInitStructure.CAN_FilterIdHigh= (((u32)0x1314<<3)&0xFFFF0000)>>16;				//要过滤的ID高位
    //    CAN_FilterInitStructure.CAN_FilterIdLow= (((u32)0x1314<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF; //要过滤的ID低位
    //    CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0xFFFF;			//过滤器高16位每位必须匹配
    //    CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0xFFFF;			//过滤器低16位每位必须匹配
    //	//CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0 ;				//过滤器被关联到FIFO0
    //	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;			//使能过滤器
    //	CAN_FilterInit(&CAN_FilterInitStructure);
    //
    //	/*CAN通信中断使能*/
    //		/* Configure one bit for preemption priority */
    //	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    //	 	/*中断设置*/
    //	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	   //CAN1 RX0中断
    //    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //抢占优先级0
    //    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //子优先级为0
    //    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //    NVIC_Init(&NVIC_InitStructure);
    //
    //	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
    return TRUE;
}

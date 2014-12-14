#include "I2C1.h"

void I2C1_HardwareInit(void)
{
    I2C_InitTypeDef I2C_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);         
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;       
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x30;         
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;         
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 100000;       

    I2C_Init(I2C1, &I2C_InitStructure);				
	I2C_Cmd(I2C1, ENABLE);                        
	               
	I2C_AcknowledgeConfig(I2C1, ENABLE); 
}


void I2C1_Read(u8 DevAddr,u8* pBuffer,u16 no)
{
    
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));	 
		
	I2C_AcknowledgeConfig(I2C1, ENABLE);	
	
	I2C_GenerateSTART(I2C1, ENABLE);	
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));	
	
	I2C_Send7bitAddress(I2C1, DevAddr<<1 , I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
    while (no)
    {
		if(no==1)
		{
     		I2C_AcknowledgeConfig(I2C1, DISABLE);	
    		I2C_GenerateSTOP(I2C1, ENABLE);		
		}
	    
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	    *pBuffer = I2C_ReceiveData(I2C1);
	    pBuffer++;
	    no--;
    }
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
}


void I2C1_WriteByte(u8 DevAddr,u8 WData)
{
	u16  i;
	u8 state;

	

	while(1)
	{ 
	i=0;
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
	{
		i++;
		if(i>10000)
		{
			break;
		}
	}

  	I2C_GenerateSTART(I2C1, ENABLE);	  //????
  	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  	{
  		i++;
		if(i>10000)
		{
			break;
		}
  	} 	//?????



  
  I2C_Send7bitAddress(I2C1, DevAddr<<1, I2C_Direction_Transmitter);  //??(??)
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
   {
  		i++;
		if(i>10000)
		{
			break;
		}
  	} 
   
  I2C_SendData(I2C1, WData); 					//????
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
   {
  		i++;
		if(i>10000)
		{
			break;
		}
  	} 
  
 		if(i>10000)
		{
	 	I2C_DeInit(I2C1);
		I2C1_HardwareInit();
		}
		else
		{
			break;
		}
	}
  I2C_GenerateSTOP(I2C1, ENABLE);			 //????
}


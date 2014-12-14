#include "Flash.h"

#define PageSize (0x0001)
//Flash 每页2kb

/*
size :U32 个数
*/

Bool Flash_Write_U32(u32 StartAddr,u32 *p_data,u32 size)
{	
	volatile FLASH_Status FLASHStatus;	
	u32 EndAddr=StartAddr+size*4;	
	vu32 NbrOfPage = 0;	
	u32 EraseCounter = 0x0, Address = 0x0;
	int i;
	int MemoryProgramStatus=1;
	
	FLASH_Unlock();          //
	NbrOfPage=((EndAddr-StartAddr-1)/PageSize)+1;
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASHStatus=FLASH_COMPLETE;
	for(EraseCounter=0;(EraseCounter<NbrOfPage)&&(FLASHStatus==FLASH_COMPLETE);EraseCounter++)
	{		
		FLASHStatus=FLASH_ErasePage(StartAddr+(PageSize*EraseCounter));	
	}
	Address = StartAddr;
	i=0;
	while((Address<EndAddr)&&(FLASHStatus==FLASH_COMPLETE))	
	{	FLASHStatus=FLASH_ProgramWord(Address,p_data[i++]);
		Address=Address+4;

	}
	Address = StartAddr;
	i=0;
	while((Address < EndAddr) && (MemoryProgramStatus != 0))
	{	
		if((*(vu32*) Address) != p_data[i++])
		{		MemoryProgramStatus = 0;
				return 1;
		}
		Address += 4;
	}
	return 0;
}

Bool Flash_Read_U32(u32 StartAddr,u32 *p_data,u32 size)
{
	u32 EndAddr=StartAddr+size*4;
	int MemoryProgramStatus=1;
	u32 Address = 0x0;
	int i=0;
	Address = StartAddr;
	while((Address < EndAddr) && (MemoryProgramStatus != 0))
	{
		p_data[i++]=(*(vu32*) Address);
		Address += 4;	
	}
	return 0;
}

void Flash_Write_F32(U32 StartAddr,F32 *p_data,u32 size)
{
	Flash_Write_U32(StartAddr,(U32*)(p_data),size);
} 

void Flash_Read_F32(U32 StartAddr,F32 *p_data,u32 size)
{
	Flash_Read_U32(StartAddr,(U32*)(p_data),size);	
}

//解锁STM32的FLASH
void STMFLASH_Unlock(void)
{
//  FLASH->KEYR=FLASH_KEY1;//写入解锁序列.
//  FLASH->KEYR=FLASH_KEY2;
}
//flash上锁
void STMFLASH_Lock(void)
{
  FLASH->CR|=1<<7;//上锁
}
//得到FLASH状态
u8 STMFLASH_GetStatus(void)
{    
       u32 res;         
       res=FLASH->SR;
       if(res&(1<<0))return 1;            //忙
       else if(res&(1<<2))return 2;  //编程错误
       else if(res&(1<<4))return 3;  //写保护错误
       return 0;                                     //操作完成
}
//等待操作完成
//time:要延时的长短
//返回值:状态.
u8 STMFLASH_WaitDone(u16 time)
{
       u8 res;
       do
       {
              res=STMFLASH_GetStatus();
              if(res!=1)break;//非忙,无需等待了,直接退出.
              Delay_us(1); time--;             
        }while(time);
        if(time==0)res=0xff;//TIMEOUT
        return res;
}
//擦除页
//paddr:页地址
//返回值:执行情况
u8 STMFLASH_ErasePage(u32 paddr)
{
       u8 res=0;
       res=STMFLASH_WaitDone(0X5FFF);//等待上次操作结束,>20ms   
       if(res==0)
       {
              FLASH->CR|=1<<1;//页擦除
              FLASH->AR=paddr;//设置页地址
              FLASH->CR|=1<<6;//开始擦除           
              res=STMFLASH_WaitDone(0X5FFF);//等待操作结束,>20ms 
              if(res!=1)//非忙
              {
                     FLASH->CR&=~(1<<1);//清除页擦除标志.
              }
       }
       return res;
}

//在FLASH指定地址写入半字
//faddr:指定地址(此地址必须为2的倍数!!)
//dat:要写入的数据
//返回值:写入的情况
u8 FLASH_WriteHalfWord(u32 faddr, u16 dat)
{
	FLASH_Unlock();          //
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(faddr);			//每次擦除1页
	FLASH_ProgramHalfWord(faddr, dat); 
}

//在FLASH指定地址写入半字
//faddr:指定地址(此地址必须为2的倍数!!)
//dat:要写入的数据
//返回值:写入的情况
u8 FLASH_Write_U16(u32 faddr, u16* pdata,u16 length)
{
	u16 i;
	FLASH_Unlock();          //
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(faddr);			//每次擦除1页
	for(i=0;i<length;i++)
	{
		FLASH_ProgramHalfWord(faddr+2*i,pdata[i]); 
	}
}

//读取指定地址的半字(16位数据)
//faddr:读地址
//返回值:对应数据.
u16 FLASH_ReadHalfWord(u32 faddr)
{
       return *(vu16*)faddr;
}


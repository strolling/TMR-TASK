#include "tmr.h"
/***********************************TMR TASK**************************************************/
//名称：TMR TASK
//作者：杨永超
//版本：V1.1.0
//初版创建时间：2019年3月2日       
TASK_STATISTICS_TYPE TASK_STATISTICS;
TASK_TYPE TASK_LIST[TASK_NUM];
SOFT_TMR _tmr[TMR_COUNT];//存储信号相关信息结构体数据类型


void Task_STATISTICS(void)
{
	u8 a;
	a++;
}
/* 此函数检查本次时间自减后时间是否归零，如果为零则将标志位置代表已经到了运行的时间*/
void TMR_CheckFlag(TASK_PONIT_TYPE TASK_PONIT)
{
	if(--TASK_PONIT->__tmr.Count==0)
	{
		TASK_PONIT->__tmr.Flag=1;
		if(TASK_PONIT->__tmr.Mode==TMR_AUTO_MODE)//检查该软件定时器是否为计数值自动装载模式
		{
			TASK_PONIT->__tmr.Count=TASK_PONIT->__tmr.PreLoad;//自动装载
		}
		
	}
}
/*节奏管理此处应该放在硬件定时器中*/
/* 如果Count位不为零则表示该软件定时器被启用，则进行时间检查*/
void TMR_Manage(void)
{
	TASK_PONIT_TYPE TASK_PONIT;
	for(TASK_PONIT=TASK_STATISTICS.HEAD->__next_ponit;TASK_PONIT!=TASK_STATISTICS.HEAD;TASK_PONIT=TASK_PONIT->__next_ponit)
	{
		if(TASK_PONIT->__tmr.Count>0)
		{
			TMR_CheckFlag(TASK_PONIT);
		}
	}
}
//在程序运行前进行时间分配，自己手动管理注册task的信号
void TMRx_Init(TASK_FUNCTION Task,uint8_t mode,uint32_t times)
{
	static u16 Count=0;
	TASK_PONIT_TYPE TASK_PONIT,TASK_PREVPONIT;
	TASK_PONIT=TASK_STATISTICS.HEAD;
	TASK_PREVPONIT=TASK_LIST+Count;
	TASK_LIST[++Count].__next_ponit=TASK_PONIT;
	TASK_LIST[Count].__task_fp=Task;
	TASK_LIST[Count].__tmr.Mode=mode;
	TASK_LIST[Count].__tmr.Count=times;
	TASK_LIST[Count].__tmr.PreLoad=times;
	TASK_PREVPONIT->__next_ponit=&TASK_LIST[Count];
}
//在程序运行中进行时间分配不会影响到原本任务的节奏，手动管理注册task的信号
void TMRx_Change(TASK_FUNCTION Task,uint8_t mode,uint32_t times)
{	
	TASK_PONIT_TYPE TASK_PONIT;
	DISABLE_INT();
	for(TASK_PONIT=TASK_STATISTICS.HEAD;TASK_PONIT->__task_fp!=Task;TASK_PONIT=TASK_PONIT->__next_ponit);
	TASK_PONIT->__tmr.PreLoad=times;
	TASK_PONIT->__tmr.Mode=mode;
	ENABLE_INT();
}
//对信号进行检查是否已经到达运行的时间，如果到达则返回1，并且自动将标志位清零，如果不是或者发生异常则返回0
uint8_t TMRx_Check(TASK_FUNCTION Task)
{
	TASK_PONIT_TYPE TASK_PONIT;
	DISABLE_INT();
	for(TASK_PONIT=TASK_STATISTICS.HEAD;TASK_PONIT->__task_fp!=Task;TASK_PONIT=TASK_PONIT->__next_ponit);
	if(TASK_PONIT->__tmr.Flag==1)
	{
		TASK_PONIT->__tmr.Flag=0;//清除标志位
		return 1;
		
	}else 
	{
		return 0;
	}
	ENABLE_INT();
}

void TASK_INIT(void)
{
	TASK_STATISTICS.HEAD=&TASK_LIST[0];
	TASK_LIST[0].__tmr.Flag=1;
	TASK_LIST[0].__task_fp=Task_STATISTICS;
	TASK_LIST[0].__tmr.Count=1;
	TASK_LIST[0].__tmr.PreLoad=1;
	TASK_LIST[0].__tmr.Mode=TMR_FOREVER_MODE;
	TASK_LIST[0].__next_ponit=&TASK_LIST[0];
}

void TASK_RUN(void)
{
	TASK_PONIT_TYPE TASK_PONIT=TASK_STATISTICS.HEAD;
	TASK_PONIT=TASK_PONIT->__next_ponit;
	for(;;TASK_PONIT=TASK_PONIT->__next_ponit)
	{
	  if(TASK_PONIT->__tmr.Flag==1)
		{
			if(TASK_PONIT->__tmr.Mode!=TMR_FOREVER_MODE)
			{
				TASK_PONIT->__tmr.Flag=0;
			}
			TASK_PONIT->__task_fp();
		}
	}
	


}





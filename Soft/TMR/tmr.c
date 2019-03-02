#include "tmr.h"
/***********************************TMR TASK**************************************************/
//名称：TMR TASK
//作者：杨永超
//版本：V1.1.0
//初版创建时间：2019年3月2日                                                                                                                                                                                                                                                                         
SOFT_TMR _tmr[TMR_COUNT];//存储信号相关信息结构体数据类型

/* 此函数检查本次时间自减后时间是否归零，如果为零则将标志位置代表已经到了运行的时间*/
void TMR_CheckFlag(SOFT_TMR * __tmr)
{
	if(__tmr->Count>0)
	{
		if(--__tmr->Count==0)
		{
			__tmr->Flag=1;
			if(__tmr->Mode==TMR_AUTO_MODE)//检查该软件定时器是否为计数值自动装载模式
			{
				__tmr->Count=__tmr->PreLoad;//自动装载
			}
		}
	}
}
/*节奏管理此处应该放在硬件定时器中*/
/* 如果Count位不为零则表示该软件定时器被启用，则进行时间检查*/
void TMR_Manage(void)
{
  uint8_t i;
	for(i=0;i<TMR_COUNT;i++)
	{
		if(_tmr[i].Count>0)
		{
			TMR_CheckFlag(&_tmr[i]);
		}
	}
}
//在程序运行前进行时间分配，自己手动管理注册task的信号
void TMRx_Init(uint8_t tmr,uint8_t mode,uint32_t times)
{
	_tmr[tmr].Count=times;
	_tmr[tmr].PreLoad=times;
	_tmr[tmr].Mode=mode;
}
//在程序运行中进行时间分配不会影响到原本任务的节奏，手动管理注册task的信号
void TMRx_Change(uint8_t tmr,uint8_t mode,uint32_t times)
{
	DISABLE_INT();
	_tmr[tmr].PreLoad=times;
	_tmr[tmr].Mode=mode;
	ENABLE_INT();
}
//对信号进行检查是否已经到达运行的时间，如果到达则返回1，并且自动将标志位清零，如果不是或者发生异常则返回0
uint8_t TMRx_Check(uint8_t TMRx)
{
	if(TMRx>TMR_COUNT)//信号超出范围
	{
		return 0;
	}
	if(_tmr[TMRx].Flag==1)
	{
		_tmr[TMRx].Flag=0;//清除标志位
		return 1;
		
	}else 
	{
		return 0;
	}
}





#include "tmr.h"
/***********************************TMR TASK**************************************************/
//���ƣ�TMR TASK
//���ߣ�������
//�汾��V1.1.0
//���洴��ʱ�䣺2019��3��2��       
TASK_STATISTICS_TYPE TASK_STATISTICS;
TASK_TYPE TASK_LIST[TASK_NUM];
SOFT_TMR _tmr[TMR_COUNT];//�洢�ź������Ϣ�ṹ����������


void Task_STATISTICS(void)
{
	u8 a;
	a++;
}
/* �˺�����鱾��ʱ���Լ���ʱ���Ƿ���㣬���Ϊ���򽫱�־λ�ô����Ѿ��������е�ʱ��*/
void TMR_CheckFlag(TASK_PONIT_TYPE TASK_PONIT)
{
	if(--TASK_PONIT->__tmr.Count==0)
	{
		TASK_PONIT->__tmr.Flag=1;
		if(TASK_PONIT->__tmr.Mode==TMR_AUTO_MODE)//���������ʱ���Ƿ�Ϊ����ֵ�Զ�װ��ģʽ
		{
			TASK_PONIT->__tmr.Count=TASK_PONIT->__tmr.PreLoad;//�Զ�װ��
		}
		
	}
}
/*�������˴�Ӧ�÷���Ӳ����ʱ����*/
/* ���Countλ��Ϊ�����ʾ�������ʱ�������ã������ʱ����*/
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
//�ڳ�������ǰ����ʱ����䣬�Լ��ֶ�����ע��task���ź�
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
//�ڳ��������н���ʱ����䲻��Ӱ�쵽ԭ������Ľ��࣬�ֶ�����ע��task���ź�
void TMRx_Change(TASK_FUNCTION Task,uint8_t mode,uint32_t times)
{	
	TASK_PONIT_TYPE TASK_PONIT;
	DISABLE_INT();
	for(TASK_PONIT=TASK_STATISTICS.HEAD;TASK_PONIT->__task_fp!=Task;TASK_PONIT=TASK_PONIT->__next_ponit);
	TASK_PONIT->__tmr.PreLoad=times;
	TASK_PONIT->__tmr.Mode=mode;
	ENABLE_INT();
}
//���źŽ��м���Ƿ��Ѿ��������е�ʱ�䣬��������򷵻�1�������Զ�����־λ���㣬������ǻ��߷����쳣�򷵻�0
uint8_t TMRx_Check(TASK_FUNCTION Task)
{
	TASK_PONIT_TYPE TASK_PONIT;
	DISABLE_INT();
	for(TASK_PONIT=TASK_STATISTICS.HEAD;TASK_PONIT->__task_fp!=Task;TASK_PONIT=TASK_PONIT->__next_ponit);
	if(TASK_PONIT->__tmr.Flag==1)
	{
		TASK_PONIT->__tmr.Flag=0;//�����־λ
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





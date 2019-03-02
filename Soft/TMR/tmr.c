#include "tmr.h"
/***********************************TMR TASK**************************************************/
//���ƣ�TMR TASK
//���ߣ�������
//�汾��V1.1.0
//���洴��ʱ�䣺2019��3��2��                                                                                                                                                                                                                                                                         
SOFT_TMR _tmr[TMR_COUNT];//�洢�ź������Ϣ�ṹ����������

/* �˺�����鱾��ʱ���Լ���ʱ���Ƿ���㣬���Ϊ���򽫱�־λ�ô����Ѿ��������е�ʱ��*/
void TMR_CheckFlag(SOFT_TMR * __tmr)
{
	if(__tmr->Count>0)
	{
		if(--__tmr->Count==0)
		{
			__tmr->Flag=1;
			if(__tmr->Mode==TMR_AUTO_MODE)//���������ʱ���Ƿ�Ϊ����ֵ�Զ�װ��ģʽ
			{
				__tmr->Count=__tmr->PreLoad;//�Զ�װ��
			}
		}
	}
}
/*�������˴�Ӧ�÷���Ӳ����ʱ����*/
/* ���Countλ��Ϊ�����ʾ�������ʱ�������ã������ʱ����*/
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
//�ڳ�������ǰ����ʱ����䣬�Լ��ֶ�����ע��task���ź�
void TMRx_Init(uint8_t tmr,uint8_t mode,uint32_t times)
{
	_tmr[tmr].Count=times;
	_tmr[tmr].PreLoad=times;
	_tmr[tmr].Mode=mode;
}
//�ڳ��������н���ʱ����䲻��Ӱ�쵽ԭ������Ľ��࣬�ֶ�����ע��task���ź�
void TMRx_Change(uint8_t tmr,uint8_t mode,uint32_t times)
{
	DISABLE_INT();
	_tmr[tmr].PreLoad=times;
	_tmr[tmr].Mode=mode;
	ENABLE_INT();
}
//���źŽ��м���Ƿ��Ѿ��������е�ʱ�䣬��������򷵻�1�������Զ�����־λ���㣬������ǻ��߷����쳣�򷵻�0
uint8_t TMRx_Check(uint8_t TMRx)
{
	if(TMRx>TMR_COUNT)//�źų�����Χ
	{
		return 0;
	}
	if(_tmr[TMRx].Flag==1)
	{
		_tmr[TMRx].Flag=0;//�����־λ
		return 1;
		
	}else 
	{
		return 0;
	}
}





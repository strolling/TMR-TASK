#ifndef TMR_H
#define TMR_H
#include "stm32f10x.h"

/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

#define TMR_COUNT 10//�ź�����
#define TASK_NUM 10
typedef  void (*TASK_FUNCTION)(void);//typedef ָ��task�ĺ���ָ��
/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef enum
{
	TMR_ONCE_MODE = 0,		/* һ�ι���ģʽ */
	TMR_AUTO_MODE = 1,		/* �Զ���ʱ����ģʽ */
	TMR_FOREVER_MODE = 2 /* �����붨ʱ������ģʽ */
}TMR_MODE_E;

/* ��ʱ���ṹ�壬��Ա���������� volatile, ����C�������Ż�ʱ���������� */
typedef struct SOFT_TMR
{
	volatile uint8_t Mode;		/* ������ģʽ��1���� */
	volatile uint8_t Flag;		/* ��ʱ�����־  */
	volatile uint32_t Count;	/* ������ */
	volatile uint32_t PreLoad;	/* ������Ԥװֵ */
}SOFT_TMR;


typedef struct TASK_TYPE
{
	SOFT_TMR __tmr;                       /*�洢task������Ϣ*/
	TASK_FUNCTION  __task_fp;             /*�洢task����ָ��*/
	struct TASK_TYPE * __next_ponit;      /*ָ����һ���ڵ�*/
}TASK_TYPE,*TASK_PONIT_TYPE;            /*typedef �ṹ��*/

typedef struct  TASK_STATISTICS_TYPE
{
	u8 TASK_COUNT;
	TASK_PONIT_TYPE HEAD;
}TASK_STATISTICS_TYPE;

void TASK_INIT(void);
void TASK_RUN(void);
void TMR_Manage(void);
void TMRx_Init(TASK_FUNCTION Task,uint8_t mode,uint32_t times);
void TMRx_Change(TASK_FUNCTION Task,uint8_t mode,uint32_t times);

#endif







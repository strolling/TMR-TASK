#ifndef TMR_H
#define TMR_H
#include "stm32f10x.h"

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

#define TMR_COUNT 10//信号数量
#define TASK_NUM 10
typedef  void (*TASK_FUNCTION)(void);//typedef 指向task的函数指针
/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef enum
{
	TMR_ONCE_MODE = 0,		/* 一次工作模式 */
	TMR_AUTO_MODE = 1,		/* 自动定时工作模式 */
	TMR_FOREVER_MODE = 2 /* 不进入定时器工作模式 */
}TMR_MODE_E;

/* 定时器结构体，成员变量必须是 volatile, 否则C编译器优化时可能有问题 */
typedef struct SOFT_TMR
{
	volatile uint8_t Mode;		/* 计数器模式，1次性 */
	volatile uint8_t Flag;		/* 定时到达标志  */
	volatile uint32_t Count;	/* 计数器 */
	volatile uint32_t PreLoad;	/* 计数器预装值 */
}SOFT_TMR;


typedef struct TASK_TYPE
{
	SOFT_TMR __tmr;                       /*存储task运行信息*/
	TASK_FUNCTION  __task_fp;             /*存储task函数指针*/
	struct TASK_TYPE * __next_ponit;      /*指向下一个节点*/
}TASK_TYPE,*TASK_PONIT_TYPE;            /*typedef 结构体*/

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







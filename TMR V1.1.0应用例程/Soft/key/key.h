#ifndef KEY_H
#define KEY_H
#include "stm32f10x.h"
#include "tmr.h"
#define SCAN_TIMER 30
#define KEY1 2
#define KEY2 3
#define KEY3 4
#define TIMEOUT5 7
#define TIMEOUT_T 1000
typedef enum
{
	NONE = 0,		    //�ް�������
	KEY_DELAY = 1,  //����������
	KEY_DOWN = 2,		//����������
	KEY_UP =3,      //�����ɿ�
	KEY_CLEAR=4     //����״̬�����������Ӧ����ִֻ��һ��ʱʹ��
}KEY_STATUS;

void Key_Init(void);
void Key_Scan(u8 *Status ,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);



#endif






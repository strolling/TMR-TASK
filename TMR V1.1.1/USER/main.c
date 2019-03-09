#include "stm32f10x.h"
#include "led.h"
#include "timer.h"
#define LED 0
#define CHANGE_LED 1

void led(void)
{
	static u8 Led_Status=0;
  LED1(Led_Status);
  Led_Status=!Led_Status;
}
int main(void)
{  	
	u16 times=500;
	SystemInit();//配置系统时钟为 72M 
	LED_GPIO_Config(); //LED管脚初始化
	TASK_INIT();
	TMRx_Init(led,TMR_AUTO_MODE,times);
	TIM4_Int_Init(1,72);//1ms
	TASK_RUN();
  while(1);
}





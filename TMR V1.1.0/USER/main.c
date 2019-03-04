#include "stm32f10x.h"
#include "led.h"
#include "timer.h"
#define LED 0
#define CHANGE_LED 1
int main(void)
{  	
	u16 times=500;
	u8 Led_Status=0;
	SystemInit();//配置系统时钟为 72M 
	LED_GPIO_Config(); //LED管脚初始化
	TMRx_Init(LED,TMR_AUTO_MODE,times);
	TMRx_Init(CHANGE_LED,TMR_AUTO_MODE,5000);
	TIM4_Int_Init(1,72);//1ms
  while (1)
  {
		if(TMRx_Check(LED))
		{
			LED1(Led_Status);
			Led_Status=!Led_Status;
		}
		if(TMRx_Check(CHANGE_LED))
		{
			TMRx_Change(LED,TMR_AUTO_MODE,times+=500);
			if(times==2000)
			{
				times=0;
			}
		}
		
		
		
		
		
  }
}





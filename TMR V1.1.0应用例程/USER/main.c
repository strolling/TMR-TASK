#include "stm32f10x.h"
#include "led.h"
#include "timer.h"
#include "key.h"
#include "pwm.h"
#include "light.h"
int main(void)
{ 
	u8 Count=0;
	u8 ButtonStatus=0;
  u8 Key1Ststus=0;
	u8 Key2Ststus=0;
	u8 Key3Ststus=0;
	u16 times=800;
	u8 Led_Status=0;
	SystemInit();//配置系统时钟为 72M 
	LED_GPIO_Config(); //LED管脚初始化
	Key_Init();
  TMRx_Init(LED,TMR_AUTO_MODE,times);
	TMRx_Init(KEY1,TMR_AUTO_MODE,SCAN_TIMER);
	TMRx_Init(KEY2,TMR_AUTO_MODE,SCAN_TIMER);
	TMRx_Init(KEY3,TMR_AUTO_MODE,SCAN_TIMER);
	//TMRx_Init(BREATHE_START,TMR_AUTO_MODE,10);
	//TMRx_Init(BREATHE_END,TMR_AUTO_MODE,10);
	TIM4_Int_Init(1,72);//1ms
  TIM3_PWM_Init(254,69);
  while (1)
  {
		if(TMRx_Check(LED))
		{
			LED1(Led_Status);
			Led_Status=!Led_Status;
		}
		//key1 scan
		if(TMRx_Check(KEY1))
		{
			Key_Scan(&Key1Ststus,GPIOA,GPIO_Pin_1);
		}
		
			//key2 scan
		if(TMRx_Check(KEY2))
		{
			Key_Scan(&Key2Ststus,GPIOA,GPIO_Pin_2);
		
		}
			//key3 scan
		if(TMRx_Check(KEY3))
		{
			Key_Scan(&Key3Ststus,GPIOA,GPIO_Pin_3);
		
		}
		
		if(Key1Ststus==3)
		{
			Count++;
			ButtonStatus|=Count;
			Key1Ststus=4;
			TMRx_Init(TIMEOUT5,TMR_ONCE_MODE,TIMEOUT_T);
			
		}
		
		if(Key2Ststus==3)
		{
			Count++;
			ButtonStatus|=(Count<<2);
			Key2Ststus=4;
			TMRx_Init(TIMEOUT5,TMR_ONCE_MODE,TIMEOUT_T);
		}
		if(Key3Ststus==3)
		{
			Count++;
			ButtonStatus|=(Count<<4);
			Key3Ststus=4;
			TMRx_Init(TIMEOUT5,TMR_ONCE_MODE,TIMEOUT_T);
		}
		if(TMRx_Check(TIMEOUT5))
		{
			Count=0;
			ButtonStatus=0;
		}
		
		if(TMRx_Check(BREATHE_START))
		{
			breathe_statr(0x20202000,20);
		}
		if(TMRx_Check(BREATHE_END))
		{
			breathe_end(0x20202000,20);
		}
		if(((ButtonStatus&0x03)==0x01)&&((ButtonStatus&0x0c)==0x08)&&((ButtonStatus&0x30)==0x30))
		{
			Count=0;
 			ButtonStatus=0;
			TMRx_Init(BREATHE_START,TMR_AUTO_MODE,10);
		}
		
		
		
		
  }
}





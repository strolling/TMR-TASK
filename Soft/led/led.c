#include "led.h"


 /***************  配置LED用到的I/O口 *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);// 使能pc端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB端口
}




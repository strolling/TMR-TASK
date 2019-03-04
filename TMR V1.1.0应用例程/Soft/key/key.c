#include "key.h"
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);// 使能pc端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PB端口
  GPIO_ResetBits(GPIOA,GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3);
}

void Key_Scan(u8 *Status ,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	u8 status;
	status=GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	if(status==Bit_SET)
	{
		if((*Status)==NONE)
		{
			(*Status)=KEY_DELAY;
		}else
		{
			(*Status)=KEY_DOWN;
		
		}

	}else if((*Status)==KEY_DOWN)
	{
		(*Status)=KEY_UP;
	}else if((*Status)!=NONE)
	{
		(*Status)=NONE;
	}
}




#ifndef PWM_H
#define PWM_H
#include "stm32f10x.h"
#define 	Led_BrightNess(time) TIM3->CCR2=time


void TIM3_PWM_Init(u16 arr,u16 psc);

#endif










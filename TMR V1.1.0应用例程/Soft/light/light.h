#ifndef LIGHT_H
#define LIGHT_H
#include "stm32f10x.h"
#include "pwm.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tmr.h"
#define BREATHE_START 5
#define BREATHE_END 6
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
void breathe_statr(u32 color1,int speed);
void breathe_end(u32 color1,int speed);
#endif





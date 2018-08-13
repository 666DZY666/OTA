#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"	  
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(void);
#define v1 PCout(6)
#define v2 PCout(7)
#define v3 PCout(8)
#define v4 PCout(9)
#endif


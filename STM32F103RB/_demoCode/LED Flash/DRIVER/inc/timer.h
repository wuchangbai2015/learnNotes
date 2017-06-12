#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32f10x.h"

extern __IO uint32_t TimingDelay;

void systick_init(void);
void delay_ms(__IO uint32_t nTime);

#endif
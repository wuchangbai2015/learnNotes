#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32f10x.h"

extern uint32_t TimingDelay;

void systick_init(void);
void delay_ms(uint32_t nTime);

#endif
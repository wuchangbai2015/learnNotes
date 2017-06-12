#include "timer.h"

uint32_t TimingDelay;

void systick_init(void)
{
    if (SysTick_Config(72000) == 1)
    {
        while(1);
    }
}

void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay --;
    }
}

void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}

void delay_ms(uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}












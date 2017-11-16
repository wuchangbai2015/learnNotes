#include "timer.h"

__IO uint32_t TimingDelay;

void systick_init(void)
{
    /*配置Systick重载值，系统时钟为72MHz*/
    /*设置72000，中断时间：72000*（1/72000000） = 1ms*/
    if(SysTick_Config(72) == 1)
    {
        while(1);
    }
    /*
    while(Systick_Config(72000) == 1);
    */
}
void TimingDelay_Decrement(void)
{
    if (TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}
void SysTick_Handler(void)
{
    TimingDelay_Decrement();
}
void delay_us(__IO uint32_t nTime)
{
    TimingDelay = nTime;//时钟滴答数
    while(TimingDelay != 0);
}
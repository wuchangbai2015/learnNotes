/**************************************
系统定时器
systick:系统滴答
*********************************************/
#ifndef __TIMER_H_
#define __TIMER_H_

#include "stm32f10x.h"

extern __IO uint32_t TimingDelay;

void systick_init(void);
void delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

/******************************************************************************/
void nvci_config(void);
void timer2_config(void);
void TIM2_IRQHandler(void);

/******************************************************************************/

void set_pwm_high(u8 high_tm);
void breath_pwm_change(void);
//extern u8 led0_state;

typedef struct 
{
    u16 high_breath_counter;
    u8 high_flag;
    u8 pwm_step;
}breath_LT;

extern breath_LT led_breath;
extern u8 pwm_high;
extern u8 pwm_fq;

#endif
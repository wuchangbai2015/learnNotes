#include "timer.h"
#include "led.h"

__IO uint32_t TimingDelay;

//u8 led0_state;
/*****************************系统滴答**********************************************/
/**********systick初始化函数****************/
void systick_init(void)
{
    /*配置Systick重载值，系统时钟为72MHz*/
    /*设置72000，中断时间：72000*（1/72000000） = 1ms*/
    /*SystemCoreClock / 1000000 ------- 1us*/
    /*SystemCoreClock / 100000 ------- 10us*/
    /*SystemCoreClock / 10000 ------- 100us*/
    /*SystemCoreClock / 1000 ------- 1ms*/
    if(SysTick_Config(72000) == 1)
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

/***********************************************************
*中断处理函数入口
*所有的中断函数入口可以在statup_stm32f10x_md.s中查找
*我们在这边定义这个函数了，那么需要在stm32f10x_it.c
*中将其这个函数注释掉
*************************************************************/
void SysTick_Handler(void) 
{
    TimingDelay_Decrement();
}

void delay_ms(__IO uint32_t nTime)
{
    TimingDelay = nTime;//时钟滴答数
    while(TimingDelay != 0);
}
/******************************************************************************/


/******************************************************************************/
/*******************************************************************************
使用TIM2定时器

*******************************************************************************/
/*****配置嵌套中断控制器 NVCI*******/
void nvci_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //设置组优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //设置定时器 2 中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能 IRQ 中断
    NVIC_Init(&NVIC_InitStructure);
}

/***************定时器初始化配置***************/

/***************************
TIM2 的时钟为 72MHz = 72 000 000 Hz

发生中断时间 = (TIM_Prescaler+1)* (TIM_Period+1)/FLK
以定时 1s 为例 TIM_Period=2000-1， TIM_Prescaler=(36000-1)

2000*36000 = 72000000 / 72MHz = 1s 
***************************/
void timer2_config(void)
{
/************************中断点灯周期1s****************************************/
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    nvci_config();
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//    TIM_DeInit(TIM2);
//    TIM_TimeBaseStructure.TIM_Period=(2000-1); //自动重装载寄存器的值
//    TIM_TimeBaseStructure.TIM_Prescaler=(36000-1); //时钟预分频数
//    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //采样分频
//    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
//    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
//    TIM_ClearFlag(TIM2,TIM_FLAG_Update); //清除溢出中断标志
//    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//    TIM_Cmd(TIM2,ENABLE); //开启时钟
/*************************设置pwm制作呼吸灯************************************/
/**************************
周期 = 36 * 10 / 72 000 000 
频率 = 72 000 000 / 360 = 200 000 = 200k
  
这个频率刚好可以产生100kHz的方波
 
********************************/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    nvci_config();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=36-1; //自动重装载寄存器的值
    TIM_TimeBaseStructure.TIM_Prescaler=10-1; //时钟预分频数
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //采样分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2,TIM_FLAG_Update); //清除溢出中断标志
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2,ENABLE); //开启时钟
}


/*******************点灯的*************************/
//void TIM2_IRQHandler(void)
//{
//    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//    {
//        led0_state = (led0_state >= 1) ? 0 : led0_state + 1;
//        if(led0_state == 0)
//        {
//            turnOn();
//        } 
//        else
//        {
//            turnOff();
//        }
//
//        TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
//    } 
//}
/******************pwm呼吸灯的***************************/
//u8 led0_state;
u8 pwm_high;
u8 pwm_fq;
breath_LT led_breath;

void breath_pwm_change(void)
{
    if(led_breath.high_breath_counter >= 80)
    {
        if(led_breath.high_flag == 0x00)
        {
            if(led_breath.pwm_step <= 99)
            {
                led_breath.pwm_step ++;
            }
            else
            {
                led_breath.high_flag = 0xff;
            }
        }
        else if(led_breath.high_flag == 0xff)
        {
            if(led_breath.pwm_step > 0)
            {
                led_breath.pwm_step -= 2;
            }
            else
            {
                led_breath.high_flag = 0x00;
            }
        }
        set_pwm_high(led_breath.pwm_step);
        led_breath.high_breath_counter = 0;
    }
}

void set_pwm_high(u8 high_tm)
{
    pwm_high = high_tm;
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    { 
        pwm_fq ++;
        if(pwm_fq < pwm_high)
        {
            turnOn();
        }
        else if(pwm_fq < 100)
        {
            turnOff();
        } 
        else
        {
            pwm_fq = 0;
            led_breath.high_breath_counter ++;
        }
    }
    TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
}



/******************************************************************************/
#include "key.h"
#include "led.h"
key_state key0;
void key_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //设置组优先级
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //设置组优先级
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //外部中断线
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能 IRQ 中断
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI9_5_IRQHandler(void)
{
    u16 i, j;
    if(EXTI_GetFlagStatus(EXTI_Line7) !=  RESET)
    {
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--);
        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7) == RESET)
        {
            key0.led_on_off = key0.led_on_off >= 4 ? 0 : key0.led_on_off + 1;
            key0.key_change_bit = CHGE_IN;
        }
        EXTI_ClearITPendingBit(EXTI_Line7); //清除标志
    }
    
}
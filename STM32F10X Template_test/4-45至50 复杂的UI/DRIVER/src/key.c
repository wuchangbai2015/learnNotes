#include "key.h"
#include "led.h"
key_state key0, key1, key2, key3;
void key_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /*GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11 | GPIO_PinSource12 | \
                                              GPIO_PinSource13 | GPIO_PinSource14);*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    
    EXTI_InitStructure.EXTI_Line = EXTI_Line11 | EXTI_Line12 | EXTI_Line13 | EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //设置组优先级
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //设置组优先级
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; //外部中断线
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能 IRQ 中断
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
    u16 i, j;
    /*判断EXTI 11？*/
    if(EXTI_GetFlagStatus(EXTI_Line11) !=  RESET)
    {
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--);
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET)
        {
            key0.led_on_off = key0.led_on_off >= 4 ? 0 : key0.led_on_off + 1;
            key0.key_change_bit = CHGE_IN;
        }
        EXTI_ClearITPendingBit(EXTI_Line11); //清除标志
    }
    
    /*判断EXTI 12？*/
    if(EXTI_GetFlagStatus(EXTI_Line12) !=  RESET)
    {
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--);
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == RESET)
        {
            key1.led_on_off = key1.led_on_off >= 4 ? 0 : key1.led_on_off + 1;
            key1.key_change_bit = CHGE_IN;
        }
        EXTI_ClearITPendingBit(EXTI_Line12); //清除标志
    }
    
    /*判断EXTI 13？*/
    if(EXTI_GetFlagStatus(EXTI_Line13) !=  RESET)
    {
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--);
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == RESET)
        {
            key2.led_on_off = key2.led_on_off >= 4 ? 0 : key2.led_on_off + 1;
            key2.key_change_bit = CHGE_IN;
        }
        EXTI_ClearITPendingBit(EXTI_Line13); //清除标志
    }        
    
    /*判断EXTI 14？*/
    if(EXTI_GetFlagStatus(EXTI_Line14) !=  RESET)
    {
        for(i = 100; i > 0; i--)
            for(j = 720; j > 0; j--);
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == RESET)
        {
            key3.led_on_off = key0.led_on_off >= 4 ? 0 : key3.led_on_off + 1;
            key3.key_change_bit = CHGE_IN;
        }
        EXTI_ClearITPendingBit(EXTI_Line14); //清除标志
    }
}
#include "led.h"

void led_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /*使能GPIOB的rcc时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  
    
    /*配置GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      
    /*初始化GPIO*/
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /*配置GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      
    /*初始化GPIO*/
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

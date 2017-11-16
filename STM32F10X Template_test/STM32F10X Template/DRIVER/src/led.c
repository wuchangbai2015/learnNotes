/*******************************************************************************

扩展板连接a6

目前我试了PA10 、PB10这两个端口的led没有问题
还是了其他的端口 PA2 、PA3 、PA5，不亮，不知道为啥

*******************************************************************************/

#include "led.h"

void led_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /*使能GPIOB的rcc时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
    
    /*配置GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;// 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   
    /*初始化GPIO*/
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void turnOn(void)
{
    GPIO_SetBits (GPIOB, GPIO_Pin_10);

}

void turnOff(void)
{
    GPIO_ResetBits (GPIOB, GPIO_Pin_10);
}

//void blink(void)
//{
//    while(1)
//    {   
//        GPIO_SetBits (GPIOA, GPIO_Pin_3);
//        delay_ms(200);
//        GPIO_ResetBits (GPIOA, GPIO_Pin_3);
//        delay_ms(200);    
//    
//    }
//
//}




#include "led.h"
#include "timer.h"
#include "key.h"
#include "usart.h"

extern key_state key0;
int main(void)
{
    
    SystemInit();                              //初始化系统，使得系统频率为72M
    systick_init();                            //配置Systick，使得1ms产生中断
    led_gpio_init ();                          //配置LED驱动管脚
    key_gpio_init ();                          //配置按键输入引脚
    usart_config();
    while(1)
    {
        if(key0.key_change_bit == CHGE_IN)
        {
            if((key0.led_on_off % 2) == 1)
            {
                GPIO_SetBits (GPIOB, GPIO_Pin_10);   //开灯
                USART_SendData(USART1, 0x01);
            }
            else
            {
                GPIO_ResetBits (GPIOB, GPIO_Pin_10); //关灯 
                USART_SendData(USART1, 0x00);
            }
            key0.key_change_bit = NO_CHGE;
        }
        else
        {
            ;
        }
    }
}
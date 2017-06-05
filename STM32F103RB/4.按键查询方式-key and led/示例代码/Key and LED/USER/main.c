#include "led.h"
#include "timer.h"
#include "key.h"

int main(void)
{
  
    u8 led_state;
    
    SystemInit();                              //初始化系统，使得系统频率为72M
    systick_init();                            //配置Systick，使得1ms产生中断
    led_gpio_init ();                          //配置LED驱动管脚
    key_gpio_init ();                          //配置按键输入引脚
    
    while(1)
    {
        if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7) == RESET) //检测按钮是不是被按下了
        {
            delay_ms (10);// 按键消抖
            if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7) == RESET) //GPIO_ReadInputDataBit()读取指定端口管脚的输入
            {
              led_state = led_state >= 4 ? 0 : led_state + 1;
            }
            while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_7) == RESET);
        }
        if((led_state % 2) == 1)
        {
            GPIO_SetBits (GPIOB, GPIO_Pin_10);   //点灯
        }
        else
        {
            GPIO_ResetBits (GPIOB, GPIO_Pin_10); //关灯
        }
    }
}
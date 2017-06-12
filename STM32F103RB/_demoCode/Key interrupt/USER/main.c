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
    while(1);  // 注意这个地方有一个分号，其实程序是进不来的 。
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET)
        {
            delay_ms (10);
            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET)
            {
              led_state = led_state >= 4 ? 0 : led_state + 1;
            }
            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == RESET);
        }
        if((led_state % 2) == 1)
        {
            GPIO_SetBits (GPIOB, GPIO_Pin_15);   //点灯
        }
        else
        {
            GPIO_ResetBits (GPIOB, GPIO_Pin_15); //关灯
        }
    }
}
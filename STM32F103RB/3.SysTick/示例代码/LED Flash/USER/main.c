#include "led.h"
#include "timer.h"
int main(void)
{
    SystemInit();                              //初始化系统，使得系统频率为72M
    systick_init();                            //配置Systick，使得1ms产生中断
    led_gpio_init ();
    while(1)
    {
        GPIO_SetBits (GPIOB, GPIO_Pin_15);
        delay_ms(1000);                        //延迟1s
        GPIO_ResetBits (GPIOB, GPIO_Pin_15);
        delay_ms(1000);                        //延迟1s
    }
}
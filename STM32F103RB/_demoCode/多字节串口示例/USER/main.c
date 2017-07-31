#include "led.h"
#include "timer.h"
#include "key.h"
#include "usart.h"

extern key_state key0, key1, key2, key3;
extern ptl_stack tx_stack;
extern ptr_stack rx_stack;
int main(void)
{
    
    SystemInit();                              //初始化系统，使得系统频率为72M
    systick_init();                            //配置Systick，使得1ms产生中断
    led_gpio_init ();                          //配置LED驱动管脚
    key_gpio_init ();                          //配置按键输入引脚
    usart_config();
    tx_stack_init();                           //初始化发送缓冲区
    rx_stack_init();                           //初始化接收缓冲区
    LED0_OFF();
    LED1_OFF();
    LED2_OFF();
    LED3_OFF();
    while(1)
    {
        if(key0.key_change_bit == CHGE_IN)
        {
            if((key0.led_on_off % 2) == 1)
            {
                LED0_ON();  //开灯
                tx_stack.data[0] = 0xff;
            }
            else
            {
                LED0_OFF(); //关灯
                tx_stack.data[0] = 0x00;
            }
            key0.key_change_bit = NO_CHGE;
            send_ptl();
        }
        if(key1.key_change_bit == CHGE_IN)
        {
            if((key1.led_on_off % 2) == 1)
            {
                LED1_ON();  //开灯
                tx_stack.data[1] = 0xff;
            }
            else
            {
                LED1_OFF(); //关灯
                tx_stack.data[1] = 0x00;
            }
            key1.key_change_bit = NO_CHGE;
            send_ptl();
        }
        if(key2.key_change_bit == CHGE_IN)
        {
            if((key2.led_on_off % 2) == 1)
            {
                LED2_ON();  //开灯
                tx_stack.data[2] = 0xff;
            }
            else
            {
                LED2_OFF(); //关灯
                tx_stack.data[2] = 0x00;
            }  
            key2.key_change_bit = NO_CHGE;
            send_ptl();
        }
        if(key3.key_change_bit == CHGE_IN)
        {
            if((key3.led_on_off % 2) == 1)
            {
                LED3_ON();  //开灯
                tx_stack.data[3] = 0xff;
            }
            else
            {
                LED3_OFF(); //关灯
                tx_stack.data[3] = 0x00;
            }
            key3.key_change_bit = NO_CHGE;
            send_ptl();
        }
        if(rx_stack.lock_flag == LOCK)   // 接受满
        {
            ptr_handle(&rx_stack.data[0]);//运行协议解析函数
        }
    }
}
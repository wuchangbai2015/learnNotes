#include "led.h"
#include "button.h"
#include "usart.h"
#include "timer.h"


extern key_state key0;

int main(void)
{
    led_gpio_init ();
//    button_gpio_init();
    button_gpio_interrupt_init();
    
/******************************************************************************/    
    SystemInit();                              //初始化系统，使得系统频率为72M
    systick_init();                            //配置Systick，使得1ms产生中断
/******************************************************************************/
    
    timer2_config();
    
/*****************************************/
//   blink(); 
    
/*****************************************************************************/
/*
    查询控制的按键   
*/
//    u8 led_state;
//    while(1)
//    {
//        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == RESET)
//        {
//            delay_ms (10);
//            if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == RESET)
//            {
//              led_state = led_state >= 4 ? 0 : led_state + 1;
//            }
//            while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == RESET);
//        }
//        if((led_state % 2) == 1)
//        {
//            turnOn();  
//        }
//        else
//        {
//            turnOff(); 
//        }
//    } 
/*******************************************************************************/ 
// 等待中断（按钮的中断的测试）
//    while(1);
    
/******************************************************************************/
// 串口字节测试
//    usart_config();
//    while(1)
//    {
//        if(key0.key_change_bit == CHGE_IN)
//        {
//            if((key0.led_on_off % 2) == 1)
//            {
//                turnOn();   //开灯
//                USART_SendData(USART1, 0x01);// 给串口发送单字节数据
//            }
//            else
//            {
//                turnOff(); //关灯
//                USART_SendData(USART1, 0x00);
//            }
//            key0.key_change_bit = NO_CHGE;
//        }
//        else
//        {
//            ;
//        }
//    }   
/******************************************************************************/    
//    return 0;
    
/******************************************************************************/
 // pwm呼吸灯 
    while(1){
      breath_pwm_change();
    
    
    }

/******************************************************************************/
}
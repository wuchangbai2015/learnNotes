#include "usart.h"

void usart_config(void)
{
    
    /*1、打开GPIO，AFIO，USART1的时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 |RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    
    /*2\初始化相应的串口引脚*/
    usart_release_gpio_init();  
    
    /*3、配置串口中断*/
    usart_nvic_config();
    
    /*4、配置串口模式*/
    usart_para_config();
}
void usart_release_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    /*配置PA9为复用推挽输出*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    /*配置PA10为浮空输入*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void usart_para_config(void)
{
    USART_InitTypeDef USART_InitStruct;
    
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;  //8
    USART_InitStruct.USART_Parity = USART_Parity_No;          //n
    USART_InitStruct.USART_StopBits = USART_StopBits_1;       //1
    
    USART_Init(USART1, &USART_InitStruct);
    
    USART_ClearFlag(USART1,USART_FLAG_TC); //清除发送完成标志位
    USART_Cmd(USART1, ENABLE); //使能串口 1
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
void usart_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //设置串口 1 中断
    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //子优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能
    NVIC_Init(&NVIC_InitStructure);
}
void USART1_IRQHandler(void)
{
    u8 receive_data;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        receive_data = USART_ReceiveData(USART1);
        if(receive_data == 0x00)
        {
            GPIO_ResetBits (GPIOB, GPIO_Pin_10); //关灯
        }
        else
        {
            GPIO_SetBits (GPIOB, GPIO_Pin_10);   //开灯
        }
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
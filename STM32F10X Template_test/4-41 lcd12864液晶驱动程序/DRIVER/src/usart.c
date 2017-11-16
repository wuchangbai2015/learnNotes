#include "usart.h"
#include "led.h"
#include "key.h"
ptl_stack tx_stack;
ptr_stack rx_stack;

void send_ptl(void)
{
    u8 i;
    USART_SendData(USART1,tx_stack.head);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, tx_stack.direction);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    for(i = 0; i <= 3; i++)
    {
        USART_SendData(USART1, tx_stack.data[i]);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
    USART_SendData(USART1, tx_stack.tail);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void tx_stack_init(void)
{
    u8 i;
    tx_stack.head = 0xaa;
    tx_stack.direction = 0x09;
    for(i = 0; i <=3; i++)
    {
        tx_stack.data[i] = 0x00;
    }
    tx_stack.tail = 0xdd;
    usart_config();
}

void rx_stack_init(void)
{
    u8 i;
    rx_stack.head = 0;
    rx_stack.direction = 0;
    for(i = 0; i <=3; i++)
    {
        rx_stack.data[i] = 0;
    }
    rx_stack.data_pt = 0;
    rx_stack.tail = 0;
    rx_stack.lock_flag = UNLOCK;
    usart_config();    
}

void usart_config(void)
{
    
    /*1、打开GPIO，AFIO，USART1的时钟*/
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 |RCC_APB2Periph_GPIOA \
                            | RCC_APB2Periph_AFIO, ENABLE);
    
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用功能的推挽输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    /*配置PA10为浮空输入*/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void usart_para_config(void)
{
    USART_InitTypeDef USART_InitStruct;
    
    USART_InitStruct.USART_BaudRate = 9600;
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

void ptr_handle(u8 *stack)
{
    u8 *stack_pt;
    stack_pt = stack;
    
    if(*stack_pt == 0xff)
    {
        key0.key_change_bit = CHGE_IN;
        if((key0.led_on_off % 2) == 1)
        {
            ;
        }
        else
        {
            key0.led_on_off = key0.led_on_off >=4 ? 0 : key0.led_on_off + 1;
        }
    }
    else
    {
        key0.key_change_bit = CHGE_IN;
        if((key0.led_on_off % 2) == 1)
        {
            key0.led_on_off = key0.led_on_off >=4 ? 0 : key0.led_on_off + 1;
        }
        else
        {
            ;
        }
    }
    stack_pt ++;
    if(*stack_pt == 0xff)
    {
        key1.key_change_bit = CHGE_IN;
        if((key1.led_on_off % 2) == 1)
        {
            ;
        }
        else
        {
            key1.led_on_off = key1.led_on_off >=4 ? 0 : key1.led_on_off + 1;
        }
    }
    else
    {
        key1.key_change_bit = CHGE_IN;
        if((key1.led_on_off % 2) == 1)
        {
            key1.led_on_off = key1.led_on_off >=4 ? 0 : key1.led_on_off + 1;
        }
        else
        {
            ;
        }
    }
    stack_pt ++;
    if(*stack_pt == 0xff)
    {
        key2.key_change_bit = CHGE_IN;
        if((key2.led_on_off % 2) == 1)
        {
            ;
        }
        else
        {
            key2.led_on_off = key2.led_on_off >=4 ? 0 : key2.led_on_off + 1;
        }
    }
    else
    {
        key2.key_change_bit = CHGE_IN;
        if((key2.led_on_off % 2) == 1)
        {
            key2.led_on_off = key2.led_on_off >=4 ? 0 : key2.led_on_off + 1;
        }
        else
        {
            ;
        }
    }
    stack_pt ++;
    if(*stack_pt == 0xff)
    {
        key3.key_change_bit = CHGE_IN;
        if((key3.led_on_off % 2) == 1)
        {
            ;
        }
        else
        {
            key3.led_on_off = key3.led_on_off >=4 ? 0 : key3.led_on_off + 1;
        }
    }
    else
    {
        key3.key_change_bit = CHGE_IN;
        if((key3.led_on_off % 2) == 1)
        {
            key3.led_on_off = key3.led_on_off >=4 ? 0 : key3.led_on_off + 1;
        }
        else
        {
            ;
        }
    }
    rx_stack_init(); 
    rx_stack.lock_flag = UNLOCK;
}

int fputc(int ch, FILE *f)
{
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET)
    { 
    
    }
    USART_SendData(USART1,(uint8_t) ch);
    return ch;
}

void USART1_IRQHandler(void)
{
    u8 receive_data;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        receive_data = USART_ReceiveData(USART1); //接收单个字节的串口数据
        
        if(rx_stack.lock_flag == UNLOCK)          //如果接受协议栈未锁住
        {
            if(receive_data == 0xaa)
            {
                rx_stack.head = receive_data;
            }
            else if(receive_data == 0xf9)
            {
                rx_stack.direction = receive_data;
            }
            else if(receive_data == 0xdd)
            {
                rx_stack.tail = receive_data;
            }
            else
            {
                rx_stack.data[rx_stack.data_pt] = receive_data;
                rx_stack.data_pt ++;
            }
            
            if((rx_stack.data_pt >= 4) && (rx_stack.tail == 0xdd))
            {
                rx_stack.lock_flag = LOCK;
            }
        }      
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}
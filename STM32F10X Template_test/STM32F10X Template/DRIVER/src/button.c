#include "button.h"

key_state key0;
/******************************************************************************/
//查询的方式
void button_gpio_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //打开GPIOB的RCC时钟
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
}
/******************************************************************************/
//中断的方式
void button_gpio_interrupt_init()
{
    GPIO_InitTypeDef GPIO_InitStructure; //定义 GPIO 结构体
    NVIC_InitTypeDef NVIC_InitStructure; //定义外部中断结构体   
    EXTI_InitTypeDef EXTI_InitStructure; //定义中断控制器结构体
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE); //开启 GPIOB 和 AFIO（ 复用端口） 时钟
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化 GPIO
   
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5); //将PB5 和 EXIT_5 连接
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line5; //选择 EXTI_Line5
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //外部中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿出发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //设置中断组优先级 0
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //PPP 外部中断线  和这个的定义EXTI_Line5有关系，可以查看NVIT_INIT的文档查找
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //设置抢占优先级为 3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //设置从优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//中断处理函数
void EXTI9_5_IRQHandler(void)
{
    u16 i, j;
    if(EXTI_GetITStatus(EXTI_Line5) != RESET) //如果是 EXIT_5 出发的中断,则处理
    {
        for(i = 100; i > 0; i--)
        for(j = 720; j > 0; j--); //延迟一会 消抖
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == RESET) 
        {
            key0.led_on_off = key0.led_on_off >= 4 ? 0 : key0.led_on_off + 1;
            key0.key_change_bit = CHGE_IN;
        } 
//        if((key0.led_on_off % 2) == 1)
//        {
//            turnOn();
//        } 
//        else
//        {
//            turnOff();
//        } 
        EXTI_ClearITPendingBit(EXTI_Line5); //清除标志
    }
}
/******************************************************************************/








//int button_press()
//{
//    u8 state = 0;
//    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == RESET)
//    {
//        delay_ms (10);
//        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == RESET)
//        {
//            state = state >= 4 ? 0 : state + 1;
//        }
//        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == RESET);
//    }
//
//    return state;
//}




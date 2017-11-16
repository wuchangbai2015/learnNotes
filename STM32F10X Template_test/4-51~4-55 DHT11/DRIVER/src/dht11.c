#include "dht11.h"
u8 dht11_buffer[5];

void dht11_portin(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //Configure pin as input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮动输入
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void dht11_portout(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //Configure pin as input
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void dht11_reset(void)
{
    dht11_portout(); // 将DHT11单总线设置成输出模式
    DHT11_OUT_L;    // MCU将单总线拉低
    delay_us(19000);// 保持19ms
    DHT11_OUT_H;    // MCU将单总线拉高
    delay_us(30);   //保持30us
    dht11_portin();
}

u16 dht11_scan(void)
{
    return DHT11_IN;
}

u16 dht11_read_bit(void)
{
    while(DHT11_IN == RESET);   //检测到低电平时候等待，每一位数据的50us低电平
    delay_us(40);
    if(DHT11_IN == SET)
    {
        while(DHT11_IN == SET);
        return 1;
    }
    else
        return 0;
}

u16 dht11_read_byte(void)
{
    u16 i;
    u16 data = 0;
    for(i = 0; i < 8; i ++)
    {
        data <<= 1;
        data |= dht11_read_bit();
    }
    return data;
}

/*******************************************************************************
一次完整的数据传输为40bit,高位先出。

数据格式:8bit湿度整数数据+8bit湿度小数数据
         +8bi温度整数数据+8bit温度小数数据
         +8bit校验和
数据传送正确时校验和数据等于“8bit湿度整数数据+8bit湿度小数数据+8bi温度整数数据+
8bit温度小数数据”所得结果的末8位。


1.将单总线设置成输出模式
2.将单总线拉低并且保持19s
3.将单总线拉高并且保持30s
4.将单总线设置成输入模式
此时DHT传感器就开始会启动数据的准备传输

5.用mcu的管脚去检测dht传感器是否发送响应信号
如果是高电平，说明没有发送响应信号，有问题
如果是低电平，说明发出了响应信号
6.等待 80us 的低电平响应信号结束
7.等待 80us 的高电平响应信号结束

8.依次读取5byte数据存在一个数组里面
9.等待 40 位数据输出完后的 50us 低电平输出结束
10.一次数据读取完了之后，将单总线设置成输出模式
11.将mcu的管脚拉高

12.校验
*******************************************************************************/
u16 dht11_read_data(void)
{
    u16 i = 0;
    dht11_reset();
    if(dht11_scan() == 0)   //检测到DHT11响应
    {
        while(dht11_scan() == RESET);
        while(dht11_scan() == SET);
        for(i = 0; i < 5; i ++)
        {
            dht11_buffer[i] = dht11_read_byte();
        }
        while(DHT11_IN == RESET);
        dht11_portout();
        DHT11_OUT_H;
        if((dht11_buffer[0] + dht11_buffer[1] + dht11_buffer[2] + dht11_buffer[3]) == dht11_buffer[4])
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
    
}
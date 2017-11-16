#include "config.h"


// ISP下载命令
static const u8 ISP_DownCmd[4] = {0x55,0xaa,0x5a,0xa5};

// 延时函数
static void delay(u32 dly)
{
    u32 i;
    while(--dly > 0)
    {
        for(i=0;i++;i<1000000);
    }
}

// 下载命令检测函数
u8 ISP_CmpDownCmd(u8 chr)
{
    static u8 i=0;
    if(chr == ISP_DownCmd[i])
    {
        i++;
        if(i == 4)
        {
            delay(100000);          // 延时1秒就足够了
            IAP_CONTR = 0x60;       // 软复位到系统ISP监控区
        }
    }else{
        i=0;
    }
    return 0;
}
/*
// 串口发送
void UART_SendChar(U8 chr)
{
    ES     =   0;  //关串口中断
    TI     =   0;  //清零串口发送完成中断请求标志
    SBUF   =   chr;
    while(TI ==0); //等待发送完成
    TI     =   0;  //清零串口发送完成中断请求标志
    ES     =   1;  //允许串口中断
}

char putchar (char c)
{
    UART_SendChar(c);
    return(c);
}

void UART_SendString(U8 *str)
{
    while(*str)
    {
        UART_SendChar(*str++);
    }
}

static const char code digits[17] = "0123456789ABCDEF";
void PutHEX(U8 c)
{
    UART_SendChar(digits[(c>>4)&0x0f]);
    UART_SendChar(digits[c&0x0f]);
}

*/
// 串口中断
void UART_Interrupt_Receive(void) interrupt 4
{
    u8 k = 0;
    if(RI==1)
    {
        RI  =   0;
        k   =   SBUF;
        ISP_CmpDownCmd(k);
    }
    if(TI == 1)
    {
        TI  =  0;
    }
}
// 串口初始化
void UartInit(void)		
{
    P3M0 &= ~0x03;
    P3M1 &= ~0x03;

	PCON &= 0x7f;       // 波特率不倍速
	SCON  = 0x50;       // 8位数据,可变波特率
	BRT   = 0xFA;       // 设定独立波特率发生器重装值  //115200bps@22.1184MHz
	AUXR |= 0x04;       // 独立波特率发生器时钟为Fosc,即1T
	AUXR |= 0x01;       // 串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;       // 启动独立波特率发生器

    TI = 0;             // 清零串口发送完成中断请求标志
    PS = 1;	            // 串口中断  优先级控制位, 1 为高优先级 0 为低优先级
    ES = 1;             // 允许串口中断
    EA = 1;             // 开总中断
}
















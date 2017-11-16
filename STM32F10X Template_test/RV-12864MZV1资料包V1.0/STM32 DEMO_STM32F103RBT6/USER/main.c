//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：原子MINI/本店STM32测试板   晶振:8MHZ 主频：72MHZ
//RV12864 SPI串口TFT液晶驱动
//ronview@ShenZhen RonView co., LTD
//淘宝网站：https://shop150504992.taobao.com/
//我司提供技术支持，任何技术问题欢迎随时交流学习
//手机:17097319383
//邮箱:990777066@qq.com 
//QQ:990777066
//Skype:ronview
//QQ技术支持群：288486111
//创建日期:2016/3/18
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳龙威显示技术有限公司 2015-2065
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
//接线说明：
//1脚VDD接3.3V
//2脚GND接GND
//3脚CS接PC9
//4脚RST接RESET
//5脚D/C接PC8
//6脚SDI接PC7
//7脚SCK接PC6
//8脚BL接3.3V(或者可以加三极管开关、PWM控制)
//9脚---13脚预留功能，根据自己需要情况选择
//////////////////////////////////////////////////////////////////////////////////
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"


//程序功能说明；
//开机显示龙威LOGO
//按键1（PC5）按下显示ASCII字符；
//按键2（PC4）按下显示汉字；
//按键3（PC11）按下显示BMP
 int main(void)
 {
	u8 x=0,i,j,t;
	 
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
	KEY_Init();
	LCDInit();
 
	DisplayFont(1,1 , 0, FONT_128X64);
	 
	while(1)
	{		
		t=KEY_Scan();
	  if(t)
		{						   
			switch(t)
			{				 
				case 1:
					ClearScreen();
					for (i=0; i<16; i++)
					{
						DisplayFont(1, i*8+1, i, FONT_8X16);
					}
					for (i=0; i<16; i++)
					{
						j = i;
						DisplayFont(3, j*8+1, j+16, FONT_8X16);
					}
					for (i=0; i<16; i++)
					{
						j = i;
						DisplayFont(5, j*8+1, j+32, FONT_8X16);
					} 
					for (i=0; i<16; i++)
					{
						j = i;
						DisplayFont(7, j*8+1, j+48, FONT_8X16);
					} 
					break;
				case 2:
					ClearScreen();
					for (i=0; i<16; i++)
					{
						j = i;
						DisplayFont(1, j*16+1, j, FONT_16X16);
					} 
					for (i=0; i<16; i++)
					{
						j = i;
						DisplayFont(3, j*16+1, j+8, FONT_16X16);
					} 
					for (i=0; i<16; i++)
					{
						j = i;
						DisplayFont(7, j*16+1, j+16, FONT_16X16);
					}
					break;
				case 3:				
					ClearScreen();
					DisplayFont(1,1 , 0, FONT_128X64);
					break;
				case 4:				
					LED0=!LED0;
					LED1=!LED1;
					break;
			}
		}
		
	  x++;
		if(x==12)x=0;
		LED0=!LED0;					 
		delay_ms(10);	
	}	
 }


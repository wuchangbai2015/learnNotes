//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：51 TFT TEST BOARD V1.0/MCU :STC12LE5A60S2/STC12C5A60S2   晶振:33MHZ
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
/* 
代码测试环境:单片机STC12LE5A60S2/STC12C5A60S2,晶振33M  单片机工作电压3.3V
程序默认IO连接方式：
接线方式：D/C-P3^5;    SDI-P3^6;   SCK-P3^7;   CS-P1^0;   REST-P1^2;
*/
#include "STC12C5A.H"
#include <intrins.h>
#include <sys.h>
#include <lcd.h>


sbit key1=P3^2;
sbit key2=P3^3;
sbit key3=P3^4;
//程序功能说明；
//开机显示龙威LOGO
//按键1（P3.2）按下显示ASCII字符；
//按键2（P3.3）按下显示汉字；
//按键3（P3.4）按下显示BMP
main()
{ 
	u8 i,j;
	
	LCDInit();      //LCD初始化
	DisplayFont(1,1 , 0, FONT_128X64);
	
	while(1)
	{		
	  if(key1==0)	//如果按键1按下,进入显示ASCII字符
		{						   
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
		}
		if(key2==0)	//如果按键2按下,进入显示汉字
		{		
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
		}
		if(key3==0)	//如果按键3按下,进入显示BMP图片
		{
			ClearScreen();
			DisplayFont(1,1 , 0, FONT_128X64);
		}
	}
}

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
#ifndef  __LCD_H
#define  __LCD_H  

 
//-----------------LCD端口定义---------------- 
#define	LCD_RST     P12      //复位        P1.2
#define	LCD_CS      P10      //片选端口  	 P1.0
#define	LCD_DC	    P35      //数据/命令   P3.5   
#define	LCD_SDI	    P36      //数据			   P3.6
#define	LCD_SCK  	  P37      //时钟    		 P3.7					  	    																						  
	
	
typedef enum
{
	FONT_5X8 = 1,
	FONT_8X16,
	FONT_16X16,
	FONT_128X64,
	SCRIBING
}Typeface;

void LCDInit(void);
void Lcd_Address(u16 page,u16 column);
void ClearScreen(void);
void DisplayFont(u8 page, u8 column, u8 No, u8 typeface);


#endif    // end 


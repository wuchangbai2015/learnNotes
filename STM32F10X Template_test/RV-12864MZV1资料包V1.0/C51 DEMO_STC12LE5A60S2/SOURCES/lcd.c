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
#include "config.h"
#include "5X8ziku.h"


void LCDShiftWrite(u8 dat)   
{    
  u8 i;                                      
  u8 Series; 
	                                         
  Series = dat;   
  for(i=0; i<8; i++)   
  {   
    LCD_SCK=0;  
		if(Series&0x80) LCD_SDI=1;
		else LCD_SDI=0;
    LCD_SCK=1;                            
    Series = Series << 1;               
  }   
}   


void send_cmd(u8 cmd)
{
  LCD_CS=0;
	LCD_DC=0;
  LCDShiftWrite(cmd);
  LCD_CS=1;
}

void send_dat(u8 dat)
{
  LCD_CS=0;
	LCD_DC=1;
  LCDShiftWrite(dat);
  LCD_CS=1;
}


void LCDInit(void) 
{ 
	LCD_RST=1;	
	delayms(5);
	LCD_RST=0;
	delayms(20);	
	LCD_RST=1;	
	delayms(20);
	
  send_cmd(0xe2);	 //软复位
	delayms(10);
	send_cmd(0xa0);  //列扫描顺序：从左到右
	send_cmd(0xc8);  //行扫描顺序：从下到上，c0从上到下
	send_cmd(0xa2);	 //设置偏压比1/9
	send_cmd(0x2f);	 //控制电源
	send_cmd(0x25);	 //粗调对比度
	send_cmd(0x81);  //微调对比度,进入微调对比度命令
	send_cmd(0x19);  //设置电压的参数RR值(对比度请修改此值，调浓增大此值，反之调淡)
	send_cmd(0x40);  //起始行：第一行开始
	send_cmd(0xaf);  //开显示
	
	ClearScreen();

} 

void Lcd_Address(u16 page,u16 column)
{
	column=column-0x01;
	send_cmd(0xb0+page-1);   /*设置页地址*/ //1-8
	send_cmd(0x10+(column>>4&0x0f));	/*设置列地址的高4位*///0-128
	send_cmd(column&0x0f);	/*设置列地址的低4位*/	
}

/*全屏清屏*/
void ClearScreen(void)
{
	unsigned char i,j;
	for(i=0;i<9;i++)
	{
		send_cmd(0xb0+i);  //从第0页开始
		send_cmd(0x10);
		send_cmd(0x00);
		for(j=0;j<132;j++)
		{
		 	send_dat(0x00);
		}
	}
}

/*显示128x64点阵图像*/
void Display_128x64(u8 *dp)
{
	u8 i,j;
	
	for(j=0;j<8;j++)
	{
		Lcd_Address(j+1,1);
		for (i=0;i<128;i++)
		{	
		  send_dat(*dp);	 	/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
		  dp++;
		}
	}
}

/*显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void Display_Graphic_16x16(u8 page,u8 column,u8 *dp)
{
	u8 i,j;
	
	for(j=0;j<2;j++)
	{
		Lcd_Address(page+j,column);
		for (i=0;i<16;i++)
		{	
			send_dat(*dp);	 /*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
			dp++;
		}
	}
}

/*显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标*/
void Display_Graphic_8x16(u8 page,u8 column,u8 *dp)
{
	u8 i,j;
	
	for(j=0;j<2;j++)
	{
		Lcd_Address(page+j,column);
		for (i=0;i<8;i++)
		{	
			send_dat(*dp);	 	/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
			dp++;
		}
	}
}

/*显示5*8点阵图像、ASCII, 或5x8点阵的自造字符、其他图标*/
void Display_Graphic_5x8(u8 page,u8 column,u8 *dp)
{
	u8 col_cnt;
	
    Lcd_Address(page,column);
	for (col_cnt=0;col_cnt<5;col_cnt++)
	{	
		send_dat(*dp);
		dp++;
	}
}

void Scribing(void)
{
	u8 i;
	
	Lcd_Address(2, 1);
	for (i=0; i<128; i++)
	{
		send_dat(0x08);
	}		
}

void DisplayFont(u8 page, u8 column, u8 No, u8 typeface)
{
	u8 *dp;
	
	switch (typeface)
	{
		case FONT_5X8:
			dp = font5x8[No];
			Display_Graphic_5x8(page, column, dp);
			break;
		case FONT_8X16:
			dp = font8x16[No];
			Display_Graphic_8x16(page, column, dp);
			break;
		case FONT_16X16:
			dp = font16x16[No];
			Display_Graphic_16x16(page, column, dp);
			break;
		case FONT_128X64:
			dp = IMG128x64;
			Display_128x64(dp);
			break;
		case SCRIBING:
			Scribing();
			break;
		default:
			break;
	}		   
}


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
//程序功能说明；
//开机显示龙威LOGO
//按键1（PC5）按下显示ASCII字符；
//按键2（PC4）按下显示汉字；
//按键3（PC11）按下显示BMP
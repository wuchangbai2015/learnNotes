#ifndef __LCD_H_
#define __LCD_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LCD_BK_ON GPIO_SetBits(GPIOB, GPIO_Pin_2) //lcd back ground on
#define LCD_BK_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_2) //lcd back ground off
#define LCD_RST_H GPIO_SetBits(GPIOB, GPIO_Pin_3) //lcd reset pin high
#define LCD_RST_L GPIO_ResetBits(GPIOB, GPIO_Pin_3) //lcd reset pin low
#define LCD_A0_H GPIO_SetBits(GPIOB, GPIO_Pin_4) //lcd A0 pin high
#define LCD_A0_L GPIO_ResetBits(GPIOB, GPIO_Pin_4) //lcd A0 pin low
#define LCD_CS_H GPIO_SetBits(GPIOB, GPIO_Pin_5) //lcd CS pin high
#define LCD_CS_L GPIO_ResetBits(GPIOB, GPIO_Pin_5) //lcd CS pin low
#define LCD_MDO_H GPIO_SetBits(GPIOA, GPIO_Pin_7) //lcd MOSI pin high
#define LCD_MDO_L GPIO_ResetBits(GPIOA, GPIO_Pin_7) //lcd MOSI pin low
#define LCD_SCK_H GPIO_SetBits(GPIOA, GPIO_Pin_5) //lcd SCK pin high
#define LCD_SCK_L GPIO_ResetBits(GPIOA, GPIO_Pin_5) //lcd SCK pin low

#define POSTIVE 0x01
#define NECTIVE 0x00

void write_lcd_data_spi(u8 data);
void write_lcd_cmd_spi(u8 cmd);
void lcd_gpio_spi(void);
void lcd_delay(unsigned long value);
void HDReset(void);
void Init_ST7567(void);
void show_num(u8 page, u8 colum, u8 number);
void show_num_s(u8 page, u8 colum, u8 number);
void show_letter_s(u8 page, u8 colum, char uletter);
void show_num_m(u8 page, u8 colum, u8 number);
void show_letter_m(u8 page, u8 colum, char uletter);
void show_num_l(u8 page, u8 colum, u8 number);
void show_letter_l(u8 page, u8 colum, char uletter);
void display_num(u8 page, u8 colum, u8 size, u16 num);
void dispaly_string(u8 page, u8 colum, u8 size, u8 *word);
void display_pic(u8 pic_num, u8 pos_or_nec);

#endif
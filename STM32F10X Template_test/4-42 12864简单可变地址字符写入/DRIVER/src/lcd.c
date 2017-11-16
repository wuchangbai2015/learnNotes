#include "lcd.h"

const u8 num[10][5] = {
                      {0x7e, 0x81, 0x81, 0x81, 0x7e},   //"0"
                      {0x00, 0x82, 0xff, 0x80, 0x00},   //"1"
                       };

void lcd_gpio_spi(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void write_lcd_data_spi(u8 data)  // --> 0b xxxx xxxx  & 0b1000 0000
{
    u8 i, temp_data;
    temp_data = data;
    LCD_CS_H;
    LCD_A0_H;
    LCD_SCK_H;
    LCD_CS_L;
    for(i = 0; i < 8; i ++)
    {
        LCD_SCK_L;
        if((temp_data & 0x80) == 0x80)
        {
            LCD_MDO_H;
        }
        else 
            LCD_MDO_L;
        LCD_SCK_H;
        temp_data <<= 1;
    }
    LCD_CS_H;
}

void write_lcd_cmd_spi(u8 cmd)  // --> 0b xxxx xxxx  & 0b1000 0000
{
    u8 i, temp_cmd;
    temp_cmd = cmd;
    LCD_CS_H;
    LCD_A0_L;
    LCD_SCK_H;
    LCD_CS_L;
    for(i = 0; i < 8; i ++)
    {
        LCD_SCK_L;
        if((temp_cmd & 0x80) == 0x80)
        {
            LCD_MDO_H;
        }
        else 
            LCD_MDO_L;
        LCD_SCK_H;
        temp_cmd <<= 1;
    }
    LCD_CS_H;
}

void lcd_delay(unsigned long value)
{
    u16 i,j;
    for (i=0;i<value;i++)
        for (j=0;j<500;j++);
}

void HDReset(void)
{
    LCD_RST_L;
    lcd_delay(2);
    LCD_RST_H;
    lcd_delay(4);
}

void Init_ST7567(void)
{
    lcd_gpio_spi();
    
    lcd_delay(10);
    HDReset(); //复位 LCD
    lcd_delay(100);
    
    write_lcd_cmd_spi(0xe2); //Soft rest
    write_lcd_cmd_spi(0xa2); //SET LCD bias(A2-1/9bias; A3-1/7bias)
    write_lcd_cmd_spi(0xa0); //SET ADC NORMAL(OB-POR seg0-00h) A0: NORMAL
                             //A1: REVERSE
    write_lcd_cmd_spi(0xc8); //SET COM OUTPUT SCAN
                             //DIRECTION(0XXXB-NORMAL)-POR COM63-->COM0
    write_lcd_cmd_spi(0xa4); // SET DISPLAY NORMAL (0B-NORMAL)-POR
                             //A4:NORMAL A5:ENTIRE DISPLAY ON
    write_lcd_cmd_spi(0xa6); //SET NORMAL DISPLAY MODE(0B-NORMAL)
                             //A6:NORMAL A7:REVERSE
    write_lcd_cmd_spi(0x25); //SET INTERNAL REGULATOR RESDASTOR
                             //RATIO(100B)-POR
    write_lcd_cmd_spi(0x81);
    write_lcd_cmd_spi(0x1a); // SET CONTRAST CONTROL
                             //REGISTER(00,0000H-11,1111H) 30 对比度请修改此值，调浓增大此值，反之调淡。
    write_lcd_cmd_spi(0x2f); //SET POWER CONTROL REGISTER (ALL
                             //INTERNAL)
    write_lcd_cmd_spi(0x40); //end of initialzation
    write_lcd_cmd_spi(0xaf); //DisPlay On
}

void show_num(u8 page, u8 colum, u8 number)
{
    u8 i, col_addr, col_msb, col_lsb, page_temp, col_temp;
    page_temp = page;
    col_temp = colum;
    write_lcd_cmd_spi(0xb0 + page_temp);  //指向第0页
    col_addr = col_temp;
    for (i = 0; i < 5; i++)
    {
        col_msb = ((col_addr >> 4) & 0x0f) | 0x10;
        col_lsb = col_addr & 0x0f;
        write_lcd_cmd_spi(col_msb);   //写列地址高4位
        write_lcd_cmd_spi(col_lsb);   //写列地址低4位
        write_lcd_data_spi(num[number][i]);
        col_addr ++;
    }
}
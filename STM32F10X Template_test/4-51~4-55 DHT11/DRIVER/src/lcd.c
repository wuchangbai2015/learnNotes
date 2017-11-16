#include "lcd.h"
#include "font.h"
#include "string.h"
const u8 num[10][18] = {
                      {0x0C,0x0E,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x06,0x06,0x07,0x07,0x06,0x06},   //"1"
                      
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
    u8 i, j, col_addr, col_msb, col_lsb, page_temp, col_temp;
    page_temp = page;
    
    col_temp = colum;
    
    for (j = 0; j < 3; j++)
    {
        write_lcd_cmd_spi(0xb0 + page_temp);  //指向第0页
        
        col_addr = col_temp;
        for (i = 0; i < 6; i++)
        {
            col_msb = ((col_addr >> 4) & 0x0f) | 0x10;
            col_lsb = col_addr & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            write_lcd_data_spi(num[number][i + j * 6]);
            col_addr ++;
        }
        page_temp ++;
    }
}

void show_num_s(u8 page, u8 colum, u8 number)
{
    u8 i, j, col_addr, col_msb, col_lsb, page_temp, col_temp;
    page_temp = page;
    
    col_temp = colum;
    
    for (j = 0; j < 1; j++)
    {
        write_lcd_cmd_spi(0xb0 + page_temp);  //指向第0页
        
        col_addr = col_temp;
        for (i = 0; i < 6; i++)
        {
            col_msb = ((col_addr >> 4) & 0x0f) | 0x10;
            col_lsb = col_addr & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            write_lcd_data_spi(num_s[number][i + j * 6]);
            col_addr ++;
        }
        page_temp ++;
    }
}

void show_letter_s(u8 page, u8 colum, char uletter)
{
    u8 i, j, col_addr, col_msb, col_lsb, page_temp, col_temp, array_num;
    page_temp = page;
    
    array_num = uletter - 65;
    col_temp = colum;
    
    for (j = 0; j < 1; j++)
    {
        write_lcd_cmd_spi(0xb0 + page_temp);  //指向第0页
        
        col_addr = col_temp;
        for (i = 0; i < 6; i++)
        {
            col_msb = ((col_addr >> 4) & 0x0f) | 0x10;
            col_lsb = col_addr & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            write_lcd_data_spi(letter_s[array_num][i + j * 6]);
            col_addr ++;
        }
        page_temp ++;
    }
}

void show_num_m(u8 page, u8 colum, u8 number)
{
    u8 i, j, col_addr, col_msb, col_lsb, page_temp, col_temp;
    page_temp = page;
    
    col_temp = colum;
    
    for (j = 0; j < 2; j++)
    {
        write_lcd_cmd_spi(0xb0 + page_temp);  //指向第0页
        
        col_addr = col_temp;
        for (i = 0; i < 8; i++)
        {
            col_msb = ((col_addr >> 4) & 0x0f) | 0x10;
            col_lsb = col_addr & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            write_lcd_data_spi(num_m[number][i + j * 8]);
            col_addr ++;
        }
        page_temp ++;
    }
}

void show_letter_m(u8 page, u8 colum, char uletter)
{
    u8 i, j, col_addr, col_msb, col_lsb, page_temp, col_temp, array_num;
    page_temp = page;
    
    array_num = uletter - 65;
    col_temp = colum;
    
    for (j = 0; j < 2; j++)
    {
        write_lcd_cmd_spi(0xb0 + page_temp);  //指向第0页
        
        col_addr = col_temp;
        for (i = 0; i < 8; i++)
        {
            col_msb = ((col_addr >> 4) & 0x0f) | 0x10;
            col_lsb = col_addr & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            write_lcd_data_spi(letter_m[array_num][i + j * 8]);
            col_addr ++;
        }
        page_temp ++;
    }
}

void show_num_l(u8 page, u8 colum, u8 number)
{
    u8 i, j, col_addr, col_msb, col_lsb, page_temp, col_temp;
    page_temp = page;
    
    col_temp = colum;
    
    for (j = 0; j < 3; j++)
    {
        write_lcd_cmd_spi(0xb0 + page_temp);  //指向第0页
        
        col_addr = col_temp;
        for (i = 0; i < 10; i++)
        {
            col_msb = ((col_addr >> 4) & 0x0f) | 0x10;
            col_lsb = col_addr & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            write_lcd_data_spi(num_l[number][i + j * 10]);
            col_addr ++;
        }
        page_temp ++;
    }
}

void show_letter_l(u8 page, u8 colum, char uletter)
{
    u8 i, j, col_addr, col_msb, col_lsb, page_temp, col_temp, array_num;
    page_temp = page;
    
    array_num = uletter - 65;
    col_temp = colum;
    
    for (j = 0; j < 3; j++)
    {
        write_lcd_cmd_spi(0xb0 + page_temp);  //指向第0页
        
        col_addr = col_temp;
        for (i = 0; i < 10; i++)
        {
            col_msb = ((col_addr >> 4) & 0x0f) | 0x10;
            col_lsb = col_addr & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            write_lcd_data_spi(letter_l[array_num][i + j * 10]);
            col_addr ++;
        }
        page_temp ++;
    }
}

void display_num(u8 page, u8 colum, u8 size, u16 num)
{
    u16 num_temp;
    u8 thu, han, ten, none, page_temp, colum_temp;
    page_temp = page;
    colum_temp = colum;
    num_temp = num;
    thu = num / 1000;
    han = (num_temp - thu * 1000) / 100;
    ten = (num_temp - thu * 1000 - han * 100) / 10;
    none = num_temp % 10;
    if(num_temp < 1000)
    {
         if(num_temp < 100)
         {
             if(num_temp < 10)
             {
                 switch(size)
                 {
                 case 1:show_num_s(page_temp, colum_temp, none);break;
                 case 2:show_num_m(page_temp, colum_temp, none);break;
                 case 3:show_num_l(page_temp, colum_temp, none);break;
                 default : break;
                 }
             }
             else
             {
                 switch(size)
                 {
                     case 1:
                     {
                         show_num_s(page_temp, colum_temp, ten);
                         show_num_s(page_temp, colum_temp + 6, none);
                         break;
                     }
                     case 2:
                     {
                         show_num_m(page_temp, colum_temp, ten);
                         show_num_m(page_temp, colum_temp + 8, none);
                         break;
                     }
                     case 3:
                     {
                         show_num_l(page_temp, colum_temp, ten);
                         show_num_l(page_temp, colum_temp + 10, none);
                         break;
                     }
                     default : break;
                 }                 
             }
         }
         else
         {
             switch(size)
             {
                 case 1:
                 {
                     show_num_s(page_temp, colum_temp, han);
                     show_num_s(page_temp, colum_temp + 6, ten);
                     show_num_s(page_temp, colum_temp + 12, none);
                     break;
                 }
                 case 2:
                 {
                     show_num_m(page_temp, colum_temp, han);
                     show_num_m(page_temp, colum_temp + 8, ten);
                     show_num_m(page_temp, colum_temp + 16, none);
                     break;
                 }     
                 case 3:
                 {
                     show_num_m(page_temp, colum_temp, han);
                     show_num_m(page_temp, colum_temp + 10, ten);
                     show_num_m(page_temp, colum_temp + 20, none);
                     break;
                 }      
                 default : break;
             }
         }
    }
    else
    {
        switch(size)
        {
            case 1:
            {
                show_num_s(page_temp, colum_temp, thu);
                show_num_s(page_temp, colum_temp + 6, han);
                show_num_s(page_temp, colum_temp + 12, ten);
                show_num_s(page_temp, colum_temp + 18, none);
                break;
            }
            case 2:
            {
                show_num_m(page_temp, colum_temp, thu);
                show_num_m(page_temp, colum_temp + 8, han);
                show_num_m(page_temp, colum_temp + 16, ten);
                show_num_m(page_temp, colum_temp + 24, none);
                break;
            }
            case 3:
            {
                show_num_l(page_temp, colum_temp, thu);
                show_num_l(page_temp, colum_temp + 10, han);
                show_num_l(page_temp, colum_temp + 20, ten);
                show_num_l(page_temp, colum_temp + 30, none);
                break;
            }            
           default : break;
        }
    }
}

void dispaly_string(u8 page, u8 colum, u8 size, u8 *word)
{
    u8 page_temp, colum_temp, *word_temp;
    page_temp = page;
    colum_temp = colum;
    word_temp = word;
    while(*word_temp != '\0')
    {
        switch(size)
        {
            case 1:
            {
                show_letter_s(page_temp, colum_temp, *word_temp);
                colum_temp += 6;
                break;
            }
            case 2:
            {
                show_letter_m(page_temp, colum_temp, *word_temp);
                colum_temp += 8;
                break;
            }
            case 3:
            {
                show_letter_l(page_temp, colum_temp, *word_temp);
                colum_temp += 10;
                break;
            }
            default : break;
        }
        word_temp ++;
    }
}

void display_pic(u8 pic_num, u8 pos_or_nec)
{
    u8 i, j, pic_num_temp, col_msb, col_lsb;
    pic_num_temp = pic_num;
    for(i = 0; i < 8; i++)
    {
        write_lcd_cmd_spi(0xb0 + i);
        for(j = 0; j < 128; j ++)
        {
            col_msb = ((j >> 4) & 0x0f) | 0x10;
            col_lsb = j & 0x0f;
            write_lcd_cmd_spi(col_msb);   //写列地址高4位
            write_lcd_cmd_spi(col_lsb);   //写列地址低4位
            if(pos_or_nec == POSTIVE)
            {
                write_lcd_data_spi(logo[pic_num_temp][j + i * 128]);
            }
            else if(pos_or_nec == NECTIVE)
            {
                write_lcd_data_spi(~logo[pic_num_temp][j + i * 128]);
            }
        }
    }
    
}
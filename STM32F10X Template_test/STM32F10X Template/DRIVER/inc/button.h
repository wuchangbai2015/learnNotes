/*******************************************************************************
¿©’π∞Â¡¨Ω”a4

*******************************************************************************/

#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h" 
#include "timer.h"
#include "led.h"

#define CHGE_IN 0x01
#define NO_CHGE 0x00

typedef struct key
{
    u8 led_on_off;
    u8 key_change_bit;
} key_state;

extern key_state key0;

void button_gpio_init(void);

void button_gpio_interrupt_init(void);

//int button_press();



#endif
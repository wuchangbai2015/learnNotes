#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define CHGE_IN 0x01
#define NO_CHGE 0x00
typedef struct key
{
    u8 led_on_off;
    u8 key_change_bit;
} key_state;
extern key_state key0;
void key_gpio_init(void);

#endif 
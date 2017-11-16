#ifndef __LED_H_
#define __LED_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h" 
#include "timer.h"

void led_gpio_init(void);
void turnOn(void);
void turnOff(void);
//void blink(void);

#endif
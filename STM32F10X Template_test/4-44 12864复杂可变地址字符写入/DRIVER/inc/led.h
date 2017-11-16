#ifndef __LED_H_
#define __LED_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LED0_ON() do{GPIO_SetBits (GPIOB, GPIO_Pin_15);}while(0);//LED0打开
#define LED0_OFF() do{GPIO_ResetBits (GPIOB, GPIO_Pin_15);}while(0);//LED0打开

#define LED1_ON() do{GPIO_SetBits (GPIOA, GPIO_Pin_11);}while(0);//LED1打开
#define LED1_OFF() do{GPIO_ResetBits (GPIOA, GPIO_Pin_11);}while(0);//LED1打开

#define LED2_ON() do{GPIO_SetBits (GPIOA, GPIO_Pin_12);}while(0);//LED2打开
#define LED2_OFF() do{GPIO_ResetBits (GPIOA, GPIO_Pin_12);}while(0);//LED2打开

#define LED3_ON() do{GPIO_SetBits (GPIOB, GPIO_Pin_10);}while(0);//LED3打开
#define LED3_OFF() do{GPIO_ResetBits (GPIOB, GPIO_Pin_10);}while(0);//LED3打开

void led_gpio_init(void);



#endif
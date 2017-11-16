#ifndef __DHT11_H_
#define __DHT11_H_

#include "timer.h"
#include "stm32f10x_gpio.h"

#define DHT11_OUT_H GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define DHT11_OUT_L GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define DHT11_IN GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)

void dht11_portin(void);
void dht11_portout(void);
void dht11_reset(void);
u16 dht11_scan(void);
u16 dht11_read_bit(void);
u16 dht11_read_byte(void);
u16 dht11_read_data(void);

extern u8 dht11_buffer[5];

#endif
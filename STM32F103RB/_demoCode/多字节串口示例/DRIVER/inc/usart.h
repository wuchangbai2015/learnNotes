#ifndef __USART_H_
#define __USART_H_

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define UNLOCK 0x00 
#define LOCK 0xff

typedef struct
{
    u8 head;
    u8 direction;
    u8 data[4];
    u8 tail;
} ptl_stack;
extern ptl_stack tx_stack;

typedef struct 
{
    u8 head;
    u8 direction;
    u8 data[4];
    u8 tail;
    u8 data_pt;
    u8 lock_flag;
} ptr_stack;
extern ptr_stack rx_stack;

void send_ptl(void);
void usart_config(void);
void usart_release_gpio_init(void);
void usart_para_config(void);
void usart_nvic_config(void);
void tx_stack_init(void);
void rx_stack_init(void);
void ptr_handle(u8 *stack);
#endif
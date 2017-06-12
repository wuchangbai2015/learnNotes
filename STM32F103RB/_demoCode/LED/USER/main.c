#include "led.h"
int main(void)
{
    led_gpio_init ();
    GPIO_SetBits (GPIOB, GPIO_Pin_15);
    return 0;
}
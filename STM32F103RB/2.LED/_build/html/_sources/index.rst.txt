.. LED documentation master file, created by
   sphinx-quickstart on Wed May 31 13:53:34 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

LED的基本使用
===============================

1.使能GPIOB的rcc时钟
-------------------------------
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

2.配置GPIO引脚
-------------------------------
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
3.初始化GPIO
-------------------------------
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  






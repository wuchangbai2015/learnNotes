.. systick documentation master file, created by
   sphinx-quickstart on Wed May 31 15:57:04 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

按键查询方式示例-按钮点亮LED
===================================

配置流程
-----------------------------------	

	1.开启GPIO时钟（在STM32中，所有的外设固件，都需要开启相应的时钟）
	
	2.选择需要配置的引脚
		
	3.选择引脚工作速度
	
	4.配置GPI0模式（八种模式之一）
	
	5.初始化GPIO 口
	
		- 5.1开启 GPI0 时钟。"RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE)"
		
		- 5.2选择需要配置的引脚。
			首先，我们需要定义一个"GPIO_InitTypeDef"的结构体"GPIO_InitStructure"。
			由于我们需要检测的引脚是PB11,因此我们选择的引脚是 "GPIO_Pin_7"，
			即“GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7"
		
		- 5.3选择引脚速度（频率）。
			一般来说，我们定义成最快的速度。
			"GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz"
		
		- 5.4配置GPIO模式。
			由于我们检测按键的实质，就是检测GPIO的电平状态， 
			因此需要将端口设置成输入模式，而仔细观察我们的电路，
			每颗按键都用电阻上拉，因 此我们只需要使用浮空输入即可。
			“GPIO_InitStructure.GPIO_Mode = GPIO_Mode_m_FLOATmG;”
		
		- 5.5初始化GPIOATM32固件库里面提供了一个GPIO的初始化函数GPIO_Init, 
			因此我们只需要使用此函数，就可以完成端口的初始化，
			这个函数的传递参数有两个个， 
			第一个是我们需要初始化的端口名，
			第二个即是我们上文里面定义的GPIO_InitTypeDef 类型的结构体。
			“GPIO_Init(GPIOB，&GPIO_InitStructure);”
		
		
		

		
		
	
	
	
	


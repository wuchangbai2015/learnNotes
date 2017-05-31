.. systick documentation master file, created by
   sphinx-quickstart on Wed May 31 15:57:04 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

LED灯的闪烁-systick的应用
===================================

1.systick的简要介绍
-----------------------------------

	systick是一个24位（0~2^24-1）的系统时钟，是从重载值递减到0会产生一个systick事件。
	systick一共有四个相关的寄存器。

2.systick的配置流程
-----------------------------------	

	- 2.1设置系统时钟（初始化系统）
	
		可直接使用固件库函数"void SystemInit(void)"设置成72M赫兹
		
	- 2.2配置systick
	
		“void systick_init(void)
		
		{
		
			/*配置Systick重载值，系统时钟为72MHz*/
			
			/*设置72000，中断时间：72000*（1/72000000） = 1ms*/
			
			if(SysTick_Config(72000) == 1)
			
			{
			
				while(1);
				
			}
			
			/*while(Systick_Config(72000) == 1);*/
			
		}”
		
		没有设置完成就"while(1)",设置完成了就出if语句，重载寄存器就变成了7200减1，减到0将
		产生一次中断。将跳入到中断入口函数这来了。
		
		
		
	- 2.3写中断处理函数
	
		先可在“startup_stm32f10x_md.s”函数里面找到systick的中断入口函数
		“void SysTick_Handler(void)“

	
	- 2.4编写systick的中断处理函数
	
		“__IO uint32_t TimingDelay; // 定义一个volatile 型的变量
	
		void TimingDelay_Decrement(void)
		
		{
		
			if (TimingDelay != 0x00)
			
			{
			
				TimingDelay--;
				
			}
			
		}
		
		void SysTick_Handler(void)
		
		{
		
			TimingDelay_Decrement();
			
		}
		
		void delay_ms(__IO uint32_t nTime)
		
		{
		
			TimingDelay = nTime;//时钟滴答数
			
			while(TimingDelay != 0);
			
		}”	
	
	
	


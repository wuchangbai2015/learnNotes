

单片机avr 定时器/计数器
===================================

	单片机的定时器/计数器实质 就是一个加1计数器
	通过软件对其控制寄存器的操作，来实现定时，计数功能及转
	换。 当定时器/计数器为定时工作方式时，计数
	器的加1信号由振荡器的分频信号产生，即每过一个机器
	周期，计数器加1，直至计满溢出为止。 当定时器/计数
	器为计数工作方式时，通过引脚T0和T1对外部信号计数，
	当电平变化时，计数器加1.定时器/计数器使用灵活，用
	途广泛，如延时，物理信号的测量，信号的周期，频率，
	脉宽测量，产生定时脉冲信号，捕捉输入，还可以实现PWM
	输出，用于D/A ,电动机的无极调速等。一个定时器可以有
	两个中断资源可利用，一个只溢出中断，另一个是比较匹配中断。
	
	ATmega16 三个定时器/计数器T/C0,T/C1,T/C2，其中T/C0
	T/C2为8位定时器/计数器，T/C1是16位定时器/计数器。
		
	
1.比较中断（以timer1为例）
-----------------------------------	

	.. code-block:: sh
	
		volatile int ggyy = 1; 
	
		int ledPin =11;
	
		const int myTOP = 7812;  //0.5s   定时时间/(分频数* (1/晶振频率))  0.5/(1024*(1/16000000))=7812(DEC)

		ISR(TIMER1_COMPA_vect){
	
			digitalWrite(ledPin, ggyy); 
		
			ggyy = 1 - ggyy; 
		
		}
	
	
		void setup( ){
	
			pinMode(ledPin, OUTPUT);
		
			digitalWrite(ledPin, LOW); 
		
			cli();  // 禁止中斷
		
			TCCR1A = 0;
		
			TCCR1B = 0; 
		
			TCCR1B |= (1<<WGM12);  // CTC mode; Clear Timer on Compare
		
			TCCR1B |= (1<<CS10) | (1<<CS12);  // Prescaler == 1024
		
			OCR1A = myTOP; 
		
			TCNT1=0; //计数初值
		
			TIMSK1 |= (1 << OCIE1A);  // enable CTC for TIMER1_COMPA_vect
		
			sei();  // 允許中斷 
		
		}

		void loop() {
	

		}

	参考链接：
			www.eeboard.com/bbs/thread-40496-1-1.html
			
			http://www.51hei.com/mcu/3472.html
	
	
	


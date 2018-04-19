#include <avr/io.h>  
#include <avr/interrupt.h>  
#define TASKS_MAX   3     //  任务数为3，表示有三个任务会使用此定时器定时

//typedef enum _TASK_LIST
//{
//    TAST_ONE,            
//    TAST_TWO,        
//    TASK_THREE,           
//    TASKS_MAX              
//} TASK_LIST;   

typedef struct _TASK_COMPONENTS
{
	unsigned int Run;                // 程序运行标记：0-不运行，1运行
    unsigned int Timer;              // 计时器
    unsigned int ItvTime;            // 任务运行间隔时间
    void (*TaskHook)(void);          // 要运行的任务函数
} TASK_COMPONENTS;                   // 任务定义


void Task_1()
{
	Serial.println("我是任务1");
}

void Task_2()
{
	Serial.println("我是任务2");
}

void Task_3()
{
	Serial.println("我是任务3");
}

static TASK_COMPONENTS TaskComps[]  = 
{
    {0, 60, 60, Task_1},         
    {0, 20, 20, Task_2},              
    {0, 30, 30, Task_3},     
};

void TaskRemarks(void)
{
    Serial.println("进入中断处理函数");

    unsigned int i;
    for (i=0; i<TASKS_MAX; i++)   // 逐个任务时间处理
    {

         if (TaskComps[i].Timer)  // 时间不为0
        {

            TaskComps[i].Timer--;     // 减去一个节拍
            if (TaskComps[i].Timer == 0)   // 时间减完了
            {                                 
				TaskComps[i].Timer = TaskComps[i].ItvTime;       // 恢复计时器值，从新下一次
				TaskComps[i].Run = 1;           // 任务可以运行
				Serial.println("任务可以运行了");
            }
        }
   }
}

void TaskProcess(void)
{
    unsigned int i;
    for (i=0; i<TASKS_MAX; i++)           // 逐个任务时间处理
    {
         Serial.println("进入任务处理函数");
         if (TaskComps[i].Run)           // 时间不为0
        {

             Serial.println("可以开始任务了");
             TaskComps[i].TaskHook();       // 运行任务
             TaskComps[i].Run = 0;          // 标志清0
        }
    }   
}

void setup(void)  
{  
	Serial.begin(115200);  
    init_time(); 
}  
  
void loop( void )  
{  
 
	Serial.println("进入主循环");
    TaskProcess();  // 任务处理
} 

//将定时器中断设为1ms 
void init_time()  
{  
  cli(); 
  TCCR1A = 0;
  TCCR1B = (1<<CS10) | (1<<CS12);
  TCNT1=0xFFEA; 
  TIMSK1 = (1 << TOIE1);  
  sei();
}  

int count = 0;
 
ISR(TIMER1_OVF_vect)
{
	TCNT1=0xFFEA;
	++count;
	if(count == 10)//这个地方为10ms了
	{
		Serial.println("Interrupt began");
		TaskRemarks();
		count = 0;
	}

} 






/***************************************
• ioctl函数：
• int ioctl( int fd, int request, int cmd);
– 参数fd，函数open 返回的句柄
– 参数request 和参数cmd，由内核驱动决定具体操作，例如request 可以
代表那个IO 口
– 参数cmd：代表对IO 进行什么样的操作，也可以反过来。具体的含义由
驱动工程师在驱动中switch决定
– 返回值：返回0 成功;返回-1，出错

**************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LED_NUM 2
#define LED_C 2
//cmd为0，则灭，为1，则亮；
//io为0则是靠近蜂鸣器的小灯，为1则靠近独立按键的小灯
int main(int argc,char *argv[])
{
	int fd,led_num,led_c;
	char *leds = "/dev/leds";

	led_num = LED_NUM;
	led_c = LED_C;
	
	printf("argv1 is cmd;argv2 is io \n"); 
	//对传入的参数进行判断，超出范围直接退出
	if (atoi(argv[1]) >= led_c) {
		printf("argv1 is 0 or 1）");
		exit(1);
	}
	if (atoi(argv[2]) >= led_num) {
		printf("argv2 is 0 or 1）");
		exit(1);
	}
	//使用ioctl函数将参数传入内核
	if((fd = open(leds, O_RDWR|O_NOCTTY|O_NDELAY))<0)
		printf("open %s failed\n",leds);   
	else{
			ioctl(fd,atoi(argv[1]),atoi(argv[2]));
			printf("ioctl %s success\n",leds);
		}
	close(fd);
	
	return(1);
}

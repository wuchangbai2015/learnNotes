/*函数time头文件*/
#include<time.h>

#include<stdio.h> 

int main(void)
{
	time_t timep;
	
	time(&timep);
	printf("UTC time: 0x%08x\n", timep);

	timep = time(NULL);
	printf("UTC time: 0x%08x\n", timep);

	return 0;
}
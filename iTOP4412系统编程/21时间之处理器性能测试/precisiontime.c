/*函数time头文件*/
#include<time.h>
/*函数gettimeofday和settimeofday的头文件*/
#include<sys/time.h>
#include<stdio.h>

void function() 
{ 
	 unsigned int i,j; 
	 double y; 
	 for(i=0;i<1000;i++) 
	 for(j=0;j<1000;j++) 
	 y=i/(j+1); //耗时操作
} 

main() 
{ 
	struct timeval tpstart,tpend; 
	float timeuse; 

	gettimeofday(&tpstart,NULL); //记录开始时间
	function();
	
	gettimeofday(&tpend,NULL); //记录结束时间
	
	timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+ 
	tpend.tv_usec-tpstart.tv_usec; //计算差值
	timeuse /= 1000000; 
	
	printf("Used Time:%f\n",timeuse); 
}
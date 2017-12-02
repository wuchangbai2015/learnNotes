#include<stdio.h> 
#include<string.h>

//argument count变元计数
//argument value变元值
int main(int argc,char *argv[])
{
	int i,j;
	i = atoi(argv[1]);
	j = atoi(argv[2]);
	
	printf("the Program name is %s\n",argv[0]);
	
	printf("The command line has %d argument:\n",argc-1);
	
	printf("%d,%d\n",i,j);
	
	return 0;
}
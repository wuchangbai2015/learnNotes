#include <stdio.h>

#include <time.h>

int main(void){
	time_t timep;
	struct tm *tblock;
	
	time(&timep);
	printf("ctime/timep is %s\n",ctime(&timep));
	
	printf("asctime is %s\n",asctime(gmtime(&timep)));
	
	tblock = localtime(&timep);
	printf("localtime is :%s\n",asctime(tblock));
	printf("localtime is:%s\n",ctime(&timep));
	return 0;
}
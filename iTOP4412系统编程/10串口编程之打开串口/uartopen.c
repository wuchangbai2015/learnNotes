#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void main(){
	int fd;
	char *uart3 = "/dev/ttySAC3";
	
	if((fd = open(uart3,O_RDWR|O_CREAT,0777))<0){
		printf("open %s failed!\n",uart3);
	}
	else{
		printf("open %s is success!\n",uart3);
	}
	
	close(fd);
}
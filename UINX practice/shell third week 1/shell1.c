#include<stdio.h>
#include<fcntl.h>
int main()
{
	int fd ;
	fd = open("./a.txt",O_CREAT,O_EXCL,0000);
	if(fd == -1) {printf("creat fial\n");}
	else         {printf("success\n");}
	return 0 ;
}





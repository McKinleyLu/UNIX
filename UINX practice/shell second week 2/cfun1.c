#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
  int fd ;
  fd=open("a.txt",O_RDONLY);
  if(fd != -1)
	  printf("%d file open sccess",fd);
  else
	  printf("-1");
  return 0 ;
}

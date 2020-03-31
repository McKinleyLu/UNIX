#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#define FIFO "myfifo"
int main()
{
   printf("i am service \n");
  if(mkfifo(FIFO,0777)<0 && (errno != EEXIST)){
      printf("pipe create wrong \n");
  }
  char b[100];
  int s = 0;
  int  fd = open(FIFO,O_RDONLY);
  if(fd == -1) {printf("open error\n");exit(-1);}
  while(1){
    int flag = 1 ;
    memset(b,0,sizeof(b));
    if( read(fd,b,100) == 0){printf("wait client\n"); flag  = 0;}
    if(flag = 1) {printf("client convert info is %s \n",b);}
    sleep(3);
 }
 pause();
 unlink(FIFO);
  
return 0 ;
}

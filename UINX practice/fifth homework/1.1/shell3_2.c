#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#define FIFO "myfifo"
int main(int argc ,char * argv[]){
      printf("i am client \n");
      int  fd = open(FIFO,O_WRONLY);
      printf("%d\n",fd);
      if(fd == -1) {printf("wrong open \n"); exit(-1);}
      char wr[100];
      while(argc == 1) {
      printf("please write something\n");
      scanf("%s",wr);
     fflush(stdin);
      if(write(fd,wr,100) == 0)  {printf("write wrong , please wait service online\n");}
      else                   {printf("convert to service pipe success \n");}
      }
return 0 ;
}

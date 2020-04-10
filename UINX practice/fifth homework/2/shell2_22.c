#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include <time.h>
#define FIFO "myfifo"
int main(int argc ,char * argv[]){
      printf("i am client \n");
      int  fd = open(FIFO,O_WRONLY);
      if(fd == -1) {printf("wrong open \n"); exit(-1);}
      char wr[100];
      while(argc == 1) {
      // get time
      time_t timep;
      time (&timep);
      //
      printf("write  time to service\n");
      strcpy(wr,asctime(gmtime(&timep)));
      //
      if(write(fd,wr,100) == 0)  {printf("write wrong , please wait service online\n");}
      else                   {printf("convert to service pipe success \n");}
      }
return 0 ;
}

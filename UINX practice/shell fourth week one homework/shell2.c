#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<string.h>
#define len 30
int main()
{
       struct timeval tv;
       int startsec,endsec;
       long starttime,endtime;
       void print_m(char *);
       /*时间采集*/
       gettimeofday(&tv,NULL);
       startsec=tv.tv_sec;
       starttime=tv.tv_usec;
        int n = 0;
        char buffer[100];
        int fd = open("a.txt",O_RDONLY);
        int fds = open("b.txt",O_WRONLY|O_CREAT);
        pid_t pid ;
        pid = fork();
        if(pid == -1 )  {printf("fork1 error\n"); exit(-1);}
        else if (pid == 0) 
        {
          printf("children is %d parent is %d \n",getpid(),getppid());
          while( n = read(fd,buffer,len)  ){ write(fds,buffer,n);}
          exit(8);
        }
        int  pids = fork();
        if(pids == -1 )  {printf("fork2 error\n"); exit(-1);}
        else if (pids == 0) 
        {
          printf("children is %d parent is %d \n",getpid(),getppid());
          while(  n = read(fd,buffer,len)  ){ write(fds,buffer,n);}
           exit(8);
        }
         /*时间采集*/
         gettimeofday(&tv,NULL);
         endsec=tv.tv_sec;
         endtime=tv.tv_usec;
         printf("Running time: %d s %lu us.\n",endsec-startsec,endtime-starttime);
   

   return 0;
}

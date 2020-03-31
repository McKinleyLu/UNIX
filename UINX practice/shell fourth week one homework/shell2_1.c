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
        int fds = open("c.txt",O_WRONLY|O_CREAT);
        while(  n = read(fd,buffer,len)  ){ write(fds,buffer,n);}
         /*时间采集*/
         gettimeofday(&tv,NULL);
         endsec=tv.tv_sec;
         endtime=tv.tv_usec;
         printf("Running time: %d s %lu us.\n",endsec-startsec,endtime-starttime);
   return 0;
}

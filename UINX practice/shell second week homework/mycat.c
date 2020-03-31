#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#define MAX_LINE 255
int main(int argc ,char* argv[])
{
       int fd_in = 0 ,fd_out = 1;
       char buffer[MAX_LINE];
       if(argc == 1)
       {
           while(1)
           {
              int n = read(fd_in,buffer,MAX_LINE);
              write(fd_out,buffer,n);
           }
       } 
       else if(argc == 2)
       {
           int fd = open(argv[1],O_RDONLY);
           if(fd == -1)  {printf("file not exit\n"); exit(-1);}
           while(1)
           {
              int n = read(fd,buffer,MAX_LINE);
              write(fd_out,buffer,n);
           }
           close(fd);
       } 
       else if (argc == 3 && (strcmp(argv[1],"+")) == 0)
       {
           int fd = open(argv[2],O_CREAT|O_RDWR);
           while(1)
           {
              int n = read(fd_in,buffer,MAX_LINE);
              write(fd,buffer,n);
               write(fd_out,buffer,n);
           }
           close(fd);
       }
       else if (argc == 5 && (strcmp(argv[1],"-") == 0) && (strcmp(argv[3],"+") == 0))
       {

          int fda = open(argv[2],O_RDONLY);
          int fdb = open(argv[4],O_CREAT|O_RDWR);
          int  n = read(fda,buffer,MAX_LINE);
          write(fdb,buffer,n);
       }
       else {printf("wrong input\n"); exit(-1);}
return 0;
}

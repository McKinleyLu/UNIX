#include<sys/types.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
int main(){

   pid_t pid;
   int n = 0;
   for(int n = 1 ; n <= 5 ; ++n){
       pid = fork();
       if(pid == 0)   {printf("child: pid=%d ppid = %d\n",getpid(),getppid());break;}
   }
   wait(0);
return 0 ;
}


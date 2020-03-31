#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
       int fd[2];
       char s[20] = "helloworldtoday";
       if(pipe(fd) < 0)  {printf("pipe wrong \n"); exit(-1);}
       pid_t pid ;
       int i = 1 ;
       for(i = 1 ; i <= 3 ; ++i){
       pid = fork();
       if(pid == 0){
         char m[10];
         close(fd[1]);
         read(fd[0],m,5);
         printf("i am child my pid is : %d my father pid is %d : my info is : %s  \n",getpid(),getppid(),m);
         close(fd[0]);
         break;         
       }
      } 
     close(fd[0]);
     write(fd[1],s,20);
     close(fd[1]);
    return 0 ;
}

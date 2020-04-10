#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
   int fd[2];
   char buffer[100];
   if(pipe(fd) < 0)  {printf("create pipe fail \n"); exit(-1);}
   pid_t pid;
   pid = fork();
   if(pid > 0)  {
     close(fd[0]);
     dup2(fd[1],STDOUT_FILENO);
     close(fd[1]);
     execlp("cat","cat","/etc/passwd",NULL);
   }
   else if(pid  == 0) {
   close(fd[1]);
   dup2(fd[0],STDIN_FILENO);
   close(fd[0]);
   execlp("grep","grep","root",NULL);
   }
   else  {printf("fork is wrong\n");}

    return 0 ;
}

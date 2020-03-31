#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
void pr_exit(int status)
{
    if(WIFEXITED(status))  {printf("existed code = %d , child exists normally\n",WEXITSTATUS(status));}
}
void pr_wrong(int status)
{

    if(WIFSIGNALED(status)) {printf("existed code = %d , chile exists abnormally\n"),WTERMSIG(status);}
}
int main()
{
       pid_t pid ;
       int status;
       printf("first normal test\n");
       pid = fork();
       if(pid == -1)       {printf("Usage : fork error \n"); exit(-1);}
       else if (pid == 0)  {exit(100);}
       
       if(wait(&status) != pid)  {printf("Usage wait wrong\n"); exit(-1);}
       printf("wating the child process\n");
       pr_exit(status);



       printf("\n\nsecond abnormal test\n");
       pid_t pids;
       int info ;
       pids = fork();
       if(pids == 0 )    { abort(); printf("I am the child program\n");}
       else if(pid > 0)  {printf("I am the parent \n"); wait(&status); pr_wrong(status);}
       else              {printf("wrong pid \n");}
      return 0;
}



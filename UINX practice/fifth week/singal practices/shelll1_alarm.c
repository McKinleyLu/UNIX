#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

int main()
{
     pid_t pid ;
     char cmd[10];
     char  ch ;
     char argv[10];
     /*printf("$");
     while(1)
   {
     signal(SIGINT,SIG_IGN);
     scanf("%s",cmd);
     ch=getchar();
     if(ch != '\n')  {scanf("%s",argv);}
     pid = fork();
     if(pid == -1)   {printf("fork is wrong\n"); exit(-1);}
     else if (pid == 0) 
        {
          if(ch != '\n')    {execlp(cmd,cmd,argv,NULL); printf("\n$");}
          else                {execlp(cmd,argv,NULL);}  
        }

      else { sleep(1)  ;  printf("$");}
   }

    wait(0);*/
   int a = alarm(5);
   //printf("%d\n",a);
   sleep(2);
   int b = alarm(10);
      printf("%d",b);

return 0;
}

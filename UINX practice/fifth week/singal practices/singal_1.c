#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void catch_hd(int signo)
{  
   for(int i = 0 ; i<= 10 ;++i)
     printf("pid = %d\n",getpid());

}

int main()
{
      signal(SIGINT,catch_hd);
      printf("hello world\n");
      execlp("./out","./out",NULL);
      //sleep(5);
    //  printf("end\n");
      return 0 ;
}

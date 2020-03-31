#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

         printf("hello world\n");
	 printf("my pid = %d\n",getpid());
	 printf("my father pid  = %d\n",getppid());
	 printf("my userID  = %d\n",getuid());
	 sleep(10);



return 0;
}

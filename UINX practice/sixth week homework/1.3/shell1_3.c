#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/wait.h>
int main()
{
   int shm_mid = shmget((key_t)123,1024,IPC_CREAT|0777);
   pid_t pid = fork();
   if(pid > 0)  {
      char *add = shmat(shm_mid,NULL,0);
      *add = 12;
      *(add+1) = 13;
      printf("I am father ,send value %d and %d\n",*add,*(add+1));
      shmdt(shm_mid);
   }
   if(pid==0){
     sleep(1);
     char *add = shmat(shm_mid,NULL,0);
     int sum = *add + *(add+1);
     printf("I am son , value acculate result is %d\n",sum);
     shmdt(shm_mid);
}

wait(0);

return 0 ;
}

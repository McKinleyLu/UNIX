#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
   int shmid = 0;
   pid_t pid;
   char *add ;
  
   shmid = shmget((key_t)14,1024,IPC_CREAT|IPC_EXCL|0777);
   
   pid = fork();
   if(pid == 0) {
         sleep(3);
         add = shmat(shmid,0,0);
         printf("get data from %d,%d\n",getppid(),*add);
         shmdt(add); 
   }
  else if (pid > 0){
    add = shmat(shmid,0,0);
    *add = 100 ;
    *(add+1) = 101;
    shmdt(add);
   }
   wait(0);


return 0;
}

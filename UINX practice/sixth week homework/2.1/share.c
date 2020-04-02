#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/wait.h>
int main(){
    int shm_mid = shmget((key_t)12,1024,IPC_CREAT|0777);
    char * add;
    add = shmat(shm_mid,NULL,0);
    *add = 0 ;
    shmdt(add);
    pid_t pid = fork();
    if(pid > 0 ){
    //V opreator
      sleep(1);
      while(1){
      add = shmat(shm_mid,NULL,0);
      *add = (*add)+2;
      printf("I am father ,value is %d\n",*add);
      shmdt(add);
      sleep(1);
       }
    } 
    else if(pid == 0){
    //P opreator
    sleep(2);
    while(1){
       add = shmat(shm_mid,NULL,0);
       if(*add <= 0)  {continue;}
       *add = (*add)-1;
       printf("I am child ,value is %d\n",*add);
        shmdt(add);
       sleep(2);
     }
    }
   else {printf("fork fail\n");}
wait(0);
return 0 ;
}

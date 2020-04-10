#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/wait.h>
int main()
{
   pid_t pid = fork();
   int sem_id = semget((key_t)1234,1,IPC_CREAT|0777);
   union seum{
   int value;
   unsigned short *array;
   struct semid_ds *buf;
   };
   union seum se;
   se.value = 1;
   semctl(sem_id,0,SETVAL,&se);
   if(pid > 0){
   //P
   while(1){
   struct sembuf sem_buf;
   sem_buf.sem_num = 0 ;
   sem_buf.sem_op = 2 ;
   sem_buf.sem_flg = SEM_UNDO;
   semop(sem_id,&sem_buf,1); 
   printf("I am father value number is %d\n",semctl(sem_id,0,GETVAL,&se));      
   sleep(2);
   }
 } 
   else if (pid == 0){
   sleep(1);
   //v
   while(1){
   struct sembuf sem_buf;
   sem_buf.sem_num = 0 ;
   sem_buf.sem_op = -1;
   sem_buf.sem_flg = SEM_UNDO;
   semop(sem_id,&sem_buf,1);  
   printf("I am child value number is %d\n",semctl(sem_id,0,GETVAL,&se));    
   sleep(2);
   }
   }

wait(0);
return 0;
}

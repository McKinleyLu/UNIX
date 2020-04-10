#include<stdlib.h>
#include<stdio.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<unistd.h>
#include <errno.h>
int main(int argc , char*argv[]){
       pid_t pid = 0;
       pid = fork();
       int sem_id;
       char ch='A';
       union semnu{
       int val; 
       unsigned short *array;
       struct semid_ds *buf;
       };
        
       union semnu se;
       se.val = 0;
       struct sembuf sem_buf;
       
      /* if(argc == 1){
        int i = semctl(sem_id,0,SETVAL,&se);
        if(i==-1) {printf("init sem fail\n");}
        ch='B';
       }*/
       if (pid > 0)  {
        sem_id = semget((key_t)1,1,IPC_CREAT|0666);
        int s = semctl(sem_id,0,SETVAL,&se);
       }
       else if(pid == 0) {
         sem_id = semget((key_t)1,1,0666);
         ch = 'B';
       }
       while(1){
        sem_buf.sem_num = 0 ;
        sem_buf.sem_op = 1 ;
        sem_buf.sem_flg = SEM_UNDO;
        semop(sem_id,&sem_buf,1);      //p opreator
        
        printf("%c....",ch);
         printf(" %d\n",semctl(sem_id,0,GETVAL,&se));
        fflush(stdout);
        
        sleep(1);  
        sem_buf.sem_num = 0;
        sem_buf.sem_op  = 1;
        sem_buf.sem_flg = SEM_UNDO;
        sleep(1);
       }

	return 0;
}

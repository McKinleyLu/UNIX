#include<unistd.h>
#include<sys/sem.h>
#include<>
int main(){
         int sem_id ;
         key_t key ;
         
         union senum {
              int va;
              
          };
          union senum  se ;
          se.val = 1 ;
         key = ftok("./a.txt",1234);
         sem_id = semget(key,1,IPC_CREAT|0666);
         semctl(sem_id,0,SETVAL,&se);
        
      


return 0 ;
}

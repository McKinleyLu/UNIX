#include<stdlib.h>
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
typedef struct{
     int a;
     int b;
     char op;
     int result;
}MS; 
int main(){
   pid_t pid = fork();
   if(pid > 0 ){
      int msg_id = msgget(15,IPC_CREAT|0777);
      int i  = 0;
     // while(1){
       MS p;
       p.a = i++;
       p.b = i++;
       p.op = '+';
       msgsnd(msg_id,&p,sizeof(MS),IPC_NOWAIT);
       printf("I am father send to son %d %d %c \n",p.a,p.b,p.op);
       sleep(50);
     
     MS re;
      msgrcv(msg_id,&re,sizeof(MS),0,IPC_NOWAIT);
      printf("I am father recevie result from son  result=%d\n",re.result);//}

   }
    else if(pid == 0){
    //while(1){
     sleep(10);
     MS re,se;
     int msg_id = msgget(15,0);
     msgrcv(msg_id,&re,sizeof(MS),0,IPC_NOWAIT);
     printf("I am son recevie the nums and op from father %d %d %c\n",re.a,re.b,re.op);
     sleep(8);
     se.result = re.a+re.b;
     msgsnd(msg_id,&se,sizeof(MS),IPC_NOWAIT);
     printf("I am son  send  result to father result=%d\n",se.result);
     //sleep(50);
    // }

    }
    else {printf("wrong fork\n");}
    wait(0);
    sleep(10);
return 0 ;
}

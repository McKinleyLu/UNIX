#include<stdlib.h>
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
typedef struct{
       int a ;
       int b ;
}Msg; 
int main(int argv ,char*argc[]){
    int msg_id = msgget(1234,0);
    Msg mess;
    while(1){
    sleep(1);
    int s = msgrcv(msg_id,&mess,sizeof(Msg),0,IPC_NOWAIT);
    printf("%d + %d = %d\n",mess.a,mess.b,mess.a+mess.b);
}  
   return 0 ;
}

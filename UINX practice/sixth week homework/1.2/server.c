#include<stdlib.h>
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
typedef struct{
       int a ;
       int b ;
}Msg; 
int main(int argv ,char*argc[]){
    Msg m1 = {2,3};
    Msg m2 = {5,9};
    Msg m3 = {12,15};
    int msg = msgget(1234,IPC_CREAT|0777);
   while(1){
    msgsnd(msg,&m1,sizeof(Msg),IPC_NOWAIT);
    msgsnd(msg,&m2,sizeof(Msg),IPC_NOWAIT);
    msgsnd(msg,&m3,sizeof(Msg),IPC_NOWAIT);
    printf("send ok \n");
    sleep(1);
}
   return 0 ;

}

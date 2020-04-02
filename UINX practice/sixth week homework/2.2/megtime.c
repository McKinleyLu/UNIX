#include<stdlib.h>
#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<time.h>
typedef struct{
     int h;
     int m;
     int s;
}MS; 
int main(){
   pid_t pid = fork();
   if (pid > 0) {
   while(1){
   int msg_id = msgget(1245,IPC_CREAT|0777);
   //get time
   struct tm *p;
    time_t t;     
    time(&t);
    p = gmtime(&t);
        p->tm_min +=0;
    if (p->tm_min>59)
    {
        p->tm_hour += p->tm_min/60;
        p->tm_min = p->tm_min%60;
    }
    
    MS s ;
    s.h = p->tm_hour;
    s.m = p->tm_min;
    s.s = p->tm_sec;
   //send message
   msgsnd(msg_id,&s,sizeof(MS),IPC_NOWAIT);
   printf("I am father,current time is %d:%d:%d\n",s.h,s.m,s.s);
   sleep(1);
  }
}

  else if(pid == 0){
   sleep(1);
  while(1){
   MS s ;
   int msg_id = msgget(1245,0);
   msgrcv(msg_id,&s,sizeof(MS),0,IPC_NOWAIT);
   printf("I am child ,recevie time is %d:%d:%d\n",s.h,s.m,s.s);
  sleep(2);
  } 
  }
  else {printf("fork fail\n");}
return 0 ;
}

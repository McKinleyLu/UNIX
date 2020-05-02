#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
struct signs{
    int op;
    char name[20];
    char mesgs[200];
};
struct operation {
    int sockfd;
    struct signs ms ;

};
// state information
void *fun(void *arg){
    struct operation* o1;
    o1 = (struct operation *)arg;
    int length;   
    while(1){
        bzero(&o1->ms,sizeof(o1->ms));
        length = recv(o1->sockfd,&o1->ms,sizeof(o1->ms),0);
        if(length > 0) {
          if(o1->ms.op == 1)       {printf("the user %s is login.\n",o1->ms.name);}
          else if(o1->ms.op == 2)  {printf("%s: %s\n",o1->ms.name,o1->ms.mesgs);}
          else if(o1->ms.op == 4)  {printf("the user %s is logout.\n",o1->ms.name);}
         }
    }
    free(o1);
    pthread_exit(NULL);
}
int main(){
      int sockfd = 0, port = 0;
      char ip[20];
      pthread_t tid;
      struct signs clients;
      struct sockaddr_in server;
      struct operation * o1;
      sockfd = socket(AF_INET,SOCK_STREAM,0);
      printf("please input the ip\n");
      scanf("%s",ip);
      printf("please input the port\n");
      scanf("%d",&port);
      bzero(&server,sizeof(server));  //初始化结构体
      server.sin_family = AF_INET;
      server.sin_port = htons(port);
      inet_aton(ip,&server.sin_addr);     
      if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))== -1){
        perror("connect fail\n");
        exit(-1);
      }
      printf("connect!\n");
      recv(sockfd,&clients,sizeof(clients),0);  

      if(clients.op == 3){
        o1 = (struct operation *)malloc(sizeof(struct operation));
        o1->sockfd = sockfd;
        pthread_create(&tid,NULL,fun,(void *)o1);


        // main thread
        printf("please input client name \n");
        scanf("%s",clients.name);
        clients.op = 1;
        send(sockfd,&clients,sizeof(clients),0);


        while(1){
            clients.op = 2 ;
            scanf("%s",clients.mesgs);
            if(strcmp("bye",clients.mesgs) == 0){
              clients.op = 4;
              send(sockfd,&clients,sizeof(clients),0);  
              break;
             }
              send(sockfd,&clients,sizeof(clients),0);
        }
              pthread_cancel(tid);     
      }
      else   { printf("client number is full\n");}
      close(sockfd);
     return 0 ;
}

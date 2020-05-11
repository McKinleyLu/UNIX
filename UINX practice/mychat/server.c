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
    int OP;
    char name[20];
    char mesgs[200];
};
struct operation {
    int sockfd;
    struct signs ms ;

};
struct users{
    int sockfd;
    char username[20];
    char buf[200];
    struct sockaddr_in client;
    int stat;
};


struct users user[10];


void communicate_process(int use){

    struct signs sendMsg;
    struct signs recvMsg;
    printf("sockfd:%d\n",user[use].sockfd );
    sendMsg.OP = 3;
    send(user[use].sockfd,&sendMsg,sizeof(sendMsg),0);

    while(1){
        bzero(&sendMsg,sizeof(sendMsg));
        bzero(&recvMsg,sizeof(recvMsg));
        int len =recv(user[use].sockfd,&recvMsg,sizeof(recvMsg),0);
        if(len > 0){
            if(recvMsg.OP == 1){
                printf("user %s login from ip:%s,port:%d\n",recvMsg.name,inet_ntoa(user[use].client.sin_addr),ntohs(user[use].client.sin_port) );
                bcopy(recvMsg.name,user[use].username,strlen(recvMsg.name));
                sendMsg.OP = 1;
            }
            else if(recvMsg.OP == 4){
                printf("user %s is logout\n",recvMsg.name );
                sendMsg.OP = 4;
                user[use].stat = 0;
                int i;
                for(i=0;i<10;i++){
                     if(user[i].stat == 1){                         
                         send(user[i].sockfd,&sendMsg,sizeof(sendMsg),0);
                     }
                 }
                break;
            }
            else if(recvMsg.OP == 2){
                sendMsg.OP = 2;
            }
            bcopy(recvMsg.name,sendMsg.name,strlen(recvMsg.name));
            bcopy(recvMsg.mesgs,sendMsg.mesgs,strlen(recvMsg.mesgs));
            int i;
            for(i=0;i<10;i++){
                 if(user[i].stat == 1){
                     printf("stat 1...%d\n",i);
                     send(user[i].sockfd,&sendMsg,sizeof(sendMsg),0);
                 }
             }
        }
        else{
            continue;
        }
    }
}

void *func(void *arg){
    int *information ;
    information = (int *)arg;
    communicate_process( *information);
    pthread_exit(NULL);
}

int main(){
    struct sockaddr_in server;
    struct sockaddr_in client;
    struct signs       message;
    int listenfd = 0 ,connetfd = 0;
    char ip[20];
    int port = 0, address = 0;
    int adderlen = 0;
    struct signs  signsmsg;
    int * arg ;
    pthread_t tid;
   if((listenfd = socket(AF_INET,SOCK_STREAM,0))== -1){
        perror("socket() error\n");
        exit(1);
    }

    printf("please input the ip : \n");
    scanf("%s",ip);
    printf("please input the port: \n");
    scanf("%d",&port);


    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_aton(ip,&server.sin_addr);   

      
    if(bind(listenfd,(struct sockaddr *)&server,sizeof(server))== -1){
        perror("bind() error\n");
        exit(1);
    }

    if (listen(listenfd,10)== -1){
        perror("listen() error\n");
        exit(1);
    }
   int i;
    for(i=0;i<10;i++){
        user[i].stat = 0;
    }
    while(1){
        adderlen = sizeof(client);
        if((connetfd = accept(listenfd,(struct sockaddr*)&client,&adderlen)) == -1) {
             perror("accept wrong\n");
             exit(-1);
          }
         int use = 10;
         for(i = 0 ; i < 10 ; ++i) {
           if(user[i].stat == 0)  {use = i ; break;}
         }
    
         if(use <= 9){
            printf("connetfd:%d\n",connetfd);
            user[use].client = client;
            user[use].sockfd = connetfd;
            user[use].stat   = 1 ;
            arg = malloc(sizeof(int));
            *arg = use;
            pthread_create(&tid,NULL,func,(void *)arg);
         }
         else{     
            bzero(&signsmsg,sizeof(signsmsg));
            signsmsg.OP = 4;
            send(connetfd,&signsmsg,sizeof(signsmsg),0);
            close(connetfd); 
             }
    }  
    close(listenfd);
    return 0;
}

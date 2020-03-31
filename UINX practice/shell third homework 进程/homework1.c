#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int global = 200;
int main(int argc , char* argv[]){
  
    pid_t pid ;
    int local = 100;
    int fd = open(argv[1],O_RDONLY);
    char buffer[10];
    int  *p = (int*)malloc(sizeof(int)*10);
    p[1] = 10 ; p[2] = 20 ;
    pid = fork();
    if(pid == -1)     {printf("Uasge: fork error \n"); exit(-1);}
    else if (pid == 0){
       p[1] = 100;
       printf("p1 is %d , p2 is %d\n",p[1],p[2]);
       global += 10 ;   //210
       local  += 20 ;   //120
       read(fd,buffer,10);
       printf("%s\n",buffer);
       printf("In child the global is %d , the local is %d \n",global,local);
    }
else{
       printf("p1 is %d , p2 is %d\n",p[1],p[2]);
       global += 11 ;  //211
       local  += 895;  //985
       read(fd,buffer,10);
       printf("%s\n",buffer);
       printf("In parent  the global is %d , the local is %d \n",global,local);

    }
return 0;
}
    

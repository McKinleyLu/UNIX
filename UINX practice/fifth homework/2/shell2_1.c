#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
    int fd1[2];
    int fd2[2];
    int x,y,sum;
    // father fd1[1] fd2[0]
    if(pipe(fd1) < 0)  {printf("pipe first  creat fail\n");}
    if(pipe(fd2) < 0)  {printf("pipe second creat fail\n");}
    pid_t pid;
    pid = fork();
    if(pid == 0) {
        close(fd1[0]);
        close(fd2[1]);
        dup2(fd2[0],STDIN_FILENO);
        dup2(fd1[1],STDOUT_FILENO);
        execlp("./add","./add",NULL);
        close(fd1[1]);
        close(fd2[0]);
    }
    else if(pid > 0){
        close(fd1[1]);
        close(fd2[0]);
        printf("please input a b for add \n");
        scanf("%d %d",&x,&y);
        write(fd2[1],&x,sizeof(int));
        write(fd2[1],&y,sizeof(int));
        read(fd1[0],&sum,sizeof(int));
        printf("sum is : %d\n",sum);
        close(fd1[0]);
        close(fd2[1]);
        wait(0);
     }
return 0 ;
}

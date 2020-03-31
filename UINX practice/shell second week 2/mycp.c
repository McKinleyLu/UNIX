#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc,char*argv[]){
     int fd1,i,fd2,n ;
     char buffer[100];
     if (argc < 3) {printf("Usage agrument number is not enough  error"); exit(-2);}
     for(i = 0 ; i< 3;++i) {printf("%s ",argv[i]);}
     fd1=open(argv[1],O_RDONLY);
     if(fd1 == -1) {printf("%d file open fail\n",fd1); exit(-1);}
     fd2=open(argv[2],O_WRONLY);
     if(fd2 == -1) {printf("%d filr open fail\n",fd2); exit(-1);}

     while(n = read(fd1,buffer,100)){ write(fd2,buffer,n); }
     close(fd1);
     close(fd2);

return 0 ;
}


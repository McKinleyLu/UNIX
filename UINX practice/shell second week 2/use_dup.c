#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
int main(){
   int  fd1,fd2;
   fd1=open("a.txt",O_RDONLY);
   printf("%d is fd1 \n",fd1);
   fd2=dup(fd1);
   printf("%d fd2 \n",fd2);

   int fd3,fd4;
   char ch[20];
   fd3=open("b.txt",O_RDONLY);
   printf("%d is fd3\n",fd3);
   dup2(fd1,fd3);
   read(fd3,ch,10);
   printf(" %s",ch);



return 0 ;
}

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
    int fd = 0 ;
    char ch[100];
    fd = open("./b.txt",O_RDONLY);
    if(fd != -1)  {printf("success\n");}
    else          {printf("not exist\n");}

    int  start=lseek(fd,0,SEEK_SET);
    int  end = lseek(fd,0,SEEK_END);
    lseek(fd,10,SEEK_CUR);
    printf("%d  %d\n",start,end);
    
    write(fd,100,ch);
    printf("%s\n",ch);
    return 0 ;

}

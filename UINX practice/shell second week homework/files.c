#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>
#define MAX_LINE 255
void menu()
{
printf("                                                                         ************************                                       \n");
printf("                                                                         ** welcome to maneger **                                       \n");
printf("                                                                         ************************                                       \n");
printf("                                                                         **     1.mycat        **                                       \n");
printf("                                                                         **     2.myls_ai      **                                       \n");
printf("                                                                         **     3.maycp        **                                       \n");
printf("                                                                         **     4.exit         **                                       \n");
printf("please input the order\n");
}
int main(int argc ,char* argv[])
{
  while(1){
       menu();
       int order = 0 ;
       scanf("%d",&order);
       fflush(stdin);
       fflush(stdout);
  switch(order){
  case 1:
       {
       int fd_in = 0 ,fd_out = 1;
       char buffer[MAX_LINE];
       if(argc == 1)
       {
           while(1)
           {
              int n = read(fd_in,buffer,MAX_LINE);
              write(fd_out,buffer,n);
           }
       } 
       else if(argc == 2)
       {
           int fd = open(argv[1],O_RDONLY);
           if(fd == -1)  {printf("file not exit\n"); break;}
           while(1)
           {
              int n = read(fd,buffer,MAX_LINE);
              write(fd_out,buffer,n);
           }
           close(fd);
       } 
       else if (argc == 3 && (strcmp(argv[1],"+")) == 0)
       {
           int fd = open(argv[2],O_CREAT|O_RDWR);
           while(1)
           {
              int n = read(fd_in,buffer,MAX_LINE);
              write(fd,buffer,n);
              write(fd_out,buffer,n);
           }
           close(fd);
       }
       else if (argc == 5 && (strcmp(argv[1],"-") == 0) && (strcmp(argv[3],"+") == 0))
       {

          int fda = open(argv[2],O_RDONLY);
          int fdb = open(argv[4],O_CREAT|O_RDWR);
          int  n = read(fda,buffer,MAX_LINE);
          write(fdb,buffer,n);
       }
       else {printf("wrong input\n"); break;}
       }
       break;
     case 2 :
             {

                 char *re = NULL;
                 re = getcwd(NULL,0);
                 DIR * dir;
                 dir = opendir(re);
                 struct dirent *d;
                 while((d=readdir(dir)) !=  NULL) {printf("%ld %s ",d->d_ino,d->d_name);}
                 printf("\n");
                 closedir(dir);
            }
            break;
    case 3 :
            {
              int fd1,i,fd2,n ;
              char buffer[100];
              if (argc < 3) {printf("Usage agrument number is not enough  error"); break;}
              //for(i = 0 ; i< 3;++i) {printf("%s ",argv[i]);}
              fd1=open(argv[1],O_RDONLY);
              if(fd1 == -1) {printf("%d file open fail\n",fd1); break;}
              fd2=open(argv[2],O_WRONLY|O_CREAT);
              if(fd2 == -1) {printf("%d filr open fail\n",fd2); break;}
              while(n = read(fd1,buffer,100)){ write(fd2,buffer,n); }
              close(fd1);
              close(fd2);
          }
          break;
  case 4 :   
          printf("good bye\n");
          return 0 ;
  default :
          printf("please input right order\n");
          break;
  }
}
return 0;
}

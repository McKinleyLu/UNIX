#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>                                                       
#include <sys/types.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <iostream>
#include <string.h>
using namespace std;
extern char **environ;
 int main()
  {
  pid_t pid;
  string buf[10];
 // char *envp[]={"PATH=/bin",NULL};//huang jing bian liang
  char *argv[]={NULL};//can shu biao
  char str[256][256];
  int i,j,k,m;
//  char path[256];
  printf("$");
  while(1)
  {
  memset(buf,0,256);
  char path[10]={"/bin/"};
   fflush(stdin);
//  memset(path,0,sizeof(path));//初始化
     //fgets(buf,256,stdin);
//  if(buf[strlen(buf)-1]=='\n')
  //   buf[strlen(buf)-1]='\0';
 /*  j=i=k=0;
  while(buf[j] !='\0')
  {
  if(buf[j]!=0x20)//kongge 
  {
    for(i=j ; buf[i] !=0x20 && buf[i] !='\0'; i++)
      str[k][i-j]=buf[i];
      str[k][i-j]='\0';
      k++;
      j=i;
  }	  
   else
   {
      j++;
   
   }
  }
  str[k+1][0]='\0';
  for(i=0;i<k;i++)
  argv[i]=str[i];
  argv[k]=NULL;
  strcat(path,str[0]);*/
    int i = 0 ;
     char s[10][10];
   while(1){
   
      cin >> buf[i++];  
      if(getchar() == '\n')  {break;}
    }
   if( i == 1)   {s[0] = buf[0].c_str();}
   if( i == 2)   {s[0] == buf[0].c_str() ; s[1] = buf[1].c_str();}
  pid=fork();
  if(pid<0)
   { printf("error");}
  else if(pid==0) 
 {   

    execve(path,s,environ);
//    perror("couldn't execut");
    exit(8);
  }
//  if((pid=waitpid(pid,&ss,0))<0)
  //  printf("wait pid error");

   if(pid > 0)   {  sleep(1) ;printf("$"); }  
//  printf("%s",path);
 //printf("%s",argv);
 // printf("%s",envp);
  }
wait(0);
    return 0;
}


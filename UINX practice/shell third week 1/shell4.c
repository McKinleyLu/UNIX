#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX_LINE 255
int main(){
       
     char path[MAX_LINE];
     char *re;
     re = getcwd(path,MAX_LINE);
     printf("%s\n",path);
     printf("%s\n",re);
     //change dirctor
     int n  =  chdir("..");
     if(n == -1)  {printf("wrong\n"); exit(-1);}
return 0 ;
}

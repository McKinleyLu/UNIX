#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
          
       struct stat buf;
       int  n = stat("shell1.c",&buf);
       if(n == -1)  {printf("wrong\n") ; exit(-1);}
       if(S_ISREG(buf.st_mode)) {printf("The file is regular file\n");}
       else                     {printf("The file is not regular\n");}
       printf("inode: %ld\n",buf.st_ino);
  return 0 ;
}

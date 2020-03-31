#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
int main()
       char* re = NULL;
       DIR*  dir;
       re = getcwp(NULL,0);
       printf("%s\n",re);
       
       dir = opendir(buf);
      
       struct dirent *d;
      while(( d = readdir(dir)) != NULL){
       
	      prinntf("%ld %s\n",d->d_ino,d->d_name);
      }
      closedir(dir);

return 0 ;
}

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
int main(int argc , char* argv[]){
      char *re = NULL;
      re = getcwd(NULL,0);
      DIR * dir;
      dir = opendir(re);
      struct dirent *d;
      if(argc > 3)
      {while((d=readdir(dir)) !=  NULL) {printf("%ld %s ",d->d_ino,d->d_name);}}
      else if (argc == 3)
      {while((d=readdir(dir)) !=  NULL) { if(d->d_type != 4){printf("%ld %s ",d->d_ino,d->d_name);}}}
      else 
      {while((d=readdir(dir)) !=  NULL) {printf("%s ",d->d_name);}}
      printf("\n");
      closedir(dir);
return 0 ;
}

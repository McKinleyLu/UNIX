#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<pwd.h>
#include <grp.h> 
#include <time.h>
//#define N_BITS 2
char *uid_to_name(uid_t uid)
{
   struct passwd *getpwuid(),*pw_ptr;
   static char numstr[10];
  
   if((pw_ptr=getpwuid(uid))==NULL)
   {
       sprintf(numstr,"%d",uid);
       return numstr;
   }
   else
       return pw_ptr->pw_name;
}
char *gid_to_name(gid_t gid)
{
   struct group *getgrgid(),*grp_ptr;
   static char numstr[10];
   if((grp_ptr=getgrgid(gid))==NULL)
   {
       sprintf(numstr,"%d",gid);
       return numstr;
   }
   else
       return grp_ptr->gr_name;
} 
typedef struct links{
    char d_name[256];
    struct links *next;
}dirlnk;
typedef struct item_info{
   unsigned long inode;
   char permisson[11];
   int owner;
   int group;
   off_t size;
   time_t mod_time;
   char name[256];
}info;

dirlnk* get_dir_detail(char *dirname)
{
    DIR*dir;
    int count = 0;
    struct dirent *dire;
    dirlnk *dir_head = NULL;
    dirlnk *cur_item = NULL;       
    dir = opendir(dirname); 
    if(dir == NULL)  {printf("open fail\n"); exit(-1);}
    while(1)
    {
       dire = readdir(dir);
       if(dire == NULL)  {break;}
       else
       {
           if( strcmp(dire->d_name,".") == 0 || strcmp(dire->d_name,"..") == 0 ) {continue;}
           dirlnk *tmp = (dirlnk*)malloc(sizeof(dirlnk));
           strcpy(tmp->d_name,dire->d_name);
           tmp->next = NULL;
           if(dir_head == NULL)  {dir_head = tmp ;  cur_item = tmp;++count;}
           else                 {cur_item->next = tmp; cur_item = tmp ; ++count;}
       }

    }
    cur_item->next = NULL;
    //printf("%d",count);
    //printf("%s\n",dir_head->next->next->d_name) ;
   return dir_head;
}
void printf_file_info(dirlnk *dir_head)
{
  static char *perm[] = {"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};
  unsigned int mask = 0700;
  struct stat file_stat;
  dirlnk *cur_dir = dir_head;
  //const int  N_BITS =  2;
  while(1)
  {
    if(cur_dir == NULL)   {break;}
    else
   {
        info file_info;
       mask = 00700;
      if(stat(cur_dir->d_name,&file_stat) == -1)
      {
         printf("current d_name is wrong!\n");
         cur_dir = cur_dir->next;
         continue;
      }
    if(S_ISREG(file_stat.st_mode)) {file_info.permisson[0] = '-';}
    if(S_ISDIR(file_stat.st_mode)) {file_info.permisson[0] = 'd';}
    int i = 3 , j = 0;
    while(i > 0)
    {
       file_info.permisson[1+j*3+0] = perm[ (file_stat.st_mode &mask) >> (i-1)*3][0];     
       file_info.permisson[1+j*3+1] = perm[ (file_stat.st_mode &mask) >> (i-1)*3][1];     
       file_info.permisson[1+j*3+2] = perm[ (file_stat.st_mode &mask) >> (i-1)*3][2];
       mask >>= 3;
       --i;
       ++j;
    }
    //printf("%s %s\n",file_info.permisson,cur_dir->d_name);
     char* chs = uid_to_name(file_stat.st_uid);
     char* chss = gid_to_name(file_stat.st_gid);
     printf("%ld %s %ld  %s           ",file_stat.st_ino,file_info.permisson,file_stat.st_nlink,chs);
     if(strcmp(chss,"root") == 0)  {printf("      ");}
     printf("%s  %d",chss,(int)file_stat.st_size);  	
     char  timestrcur[40]; 
     struct  tm  *tmtest = NULL;
     tmtest = localtime(&file_stat.st_mtime); 
          if(strcmp(chss,"root") == 0)  {printf("  ");}
     strftime(timestrcur,sizeof(timestrcur),"%Y-%m-%d %H-%M-%S",tmtest); 	
     printf(" %s  \n", timestrcur);  
     cur_dir = cur_dir->next;
   }
  }
}
int main()
{

    char *dirname = NULL;
    dirname = getcwd(NULL,0);
    dirlnk *p = NULL;
    p = get_dir_detail(dirname);
    printf_file_info(p);
  return 0 ;
}

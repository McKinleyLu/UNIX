#include<unistd.h>
#include<sys/types.h>
int main()
{
   pid_t pid ;
   int fd[2];
   int i ;
   char ch[20] = "hello world\n";
   int a = 80;
   int b ;
   pipe(fd);
   pid = fork();
   if(pid == 0)       {  
                       close(fd[1]); 
                       read(fd[0],ch_in,20);  
                       read(fd[0],&b,sizeof(int));
                       close(fd[0]); 
                      }
   else if (pid > 0 ) {    
                       close(fd[0]) ;   
                       write(fd[1],ch,sizeof(ch));  
                       write(fd[1],)
                     
                       }




}

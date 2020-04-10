#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
struct 
void *fun1(void * arg){
       int ra = (int)arg; 
       int i = 0;
       for(i = 0 ; i < ra ;++i)  { usleep(5) ; printf("rabbit : pid = %d , i = %d tid = %d\n",getpid(),i,(int)pthread_self());}
       
}
void *fun2(void *arg){
       int rt = (int)arg;
       int i = 0 ;
       for(i = 0 ;i <=rt ; ++i) {usleep(8) ;  printf("turtle :pid = %d , i = %d tid = %d\n",getpid(),i,(int)pthread_self());}
}
int main(){

        pthread_t  ptd_t1 ,ptd_t2;
        printf("please input rabbit ang turtle length\n");
        int ra,rt;
        int *endra,*endtr;
        scanf("%d%d",&ra,&rt);
        pthread_create(&ptd_t1,NULL,fun1,ra);
        pthread_create(&ptd_t2,NULL,fun2,rt);
        sleep(1);
        pthread_join(ptd_t1,(void*)&endra);
        pthread_join(ptd_t1,(void*)&endtr);
        

return 0 ;
}

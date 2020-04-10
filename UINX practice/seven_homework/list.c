#include <pthread.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
typedef struct LINK{
    int data;
    pthread_mutex_t mutex;
    struct LINK *next;
}linklist;

typedef struct op{
    int data;
    struct LINK *p;
    struct LINK *end;
}opertion;

void* init_list(void* arg){
      opertion * op = (opertion *)arg;
      linklist *node,*endlist;
      node = (linklist*)malloc(sizeof(linklist));
      node->data = op->data;
      op->p      = node ;
      pthread_mutex_init(&op->p->mutex,NULL);
      endlist  = node;
      endlist->next = NULL;
      op->end = endlist;     
}

void* insert_data(void* arg){
       opertion * op = (opertion *)arg;
       pthread_mutex_lock(&op->p->mutex);
       linklist *node ;
       node = (linklist*)malloc(sizeof(linklist));
       node->data = op->data;
       
       op->end->next = node;
       op->end = node ;
       op->end->next = NULL;   
       pthread_mutex_unlock(&op->p->mutex);      
}

void* delete_data(void * arg){
       opertion * op = (opertion *)arg;
       pthread_mutex_lock(&op->p->mutex);
       linklist * p = op->p;
       linklist * pre = NULL;
       int flag = 0; 
       while(p != NULL){
         if(p->data == op->data){
               if(p == op->p )   {op->p = op->p->next; free(p); flag = 1 ; break;}
               else            {pre->next = p->next; if(p == op->end) {op->end = pre ;} free(p); flag = 1 ;break;}             
           }   
           pre = p ;
           p = p->next;         
       }
      if(!flag)  {printf("node not exist\n");}
      pthread_mutex_unlock(&op->p->mutex); 
}


void display_data(void * arg){
       opertion * op = (opertion *)arg;
       pthread_mutex_lock(&op->p->mutex);
       linklist *p = op->p;
      while(1){
           if(p == NULL)  {break;}
           else {printf("%d.. ",p->data);}
           p = p->next;
      }
       printf("\n");
       pthread_mutex_unlock(&op->p->mutex);
}
void menu(){
printf("1.创建链表\n");
printf("2.插入节点\n");
printf("3.删除节点\n");
printf("4.打印所有节点\n");
printf("5.退出程序\n");
printf("请输入要执行的选项\n");
}
int main(){
    int order = 0,flag = 1; linklist *head = NULL ; linklist * end = NULL;
     while(flag){
        menu();
        while(1){
        scanf("%d",&order);
        if(order > 5 || order < 1)  {printf("输入错误，请重新输入\n");}
        else {break;}
        }
        switch(order){
        case 1:
               {
                opertion o1;
                pthread_t  girl ;
                printf("请输入第一个节点数据\n");
                scanf("%d",&o1.data);
                fflush(stdin);
                o1.p = head;
                int erro = 0;
                erro = pthread_create(&girl,NULL,init_list,(void*)&o1);
                if(erro != 0)  {fprintf(stderr,"%s\n",strerror(erro));}
                pthread_join(girl,NULL);
                head = o1.p;
                end  = o1.end;
                printf("创建成功\n");
                break;
               }
        
        case 2 :
               {
                 opertion o1;
                 pthread_t dog;
                 printf("请输入数据\n");
                 int data = 0;
                 scanf("%d",&data);
                 o1.data = data;
                 o1.p = head;
                 o1.end = end;
                 int erro =  pthread_create(&dog,NULL,insert_data,(void*)&o1);
                 if(erro != 0)  {fprintf(stderr,"%s\n",strerror(erro));}  
                 pthread_join(dog,NULL);
                 end = o1.end;
                 printf("插入成功\n");
                 //printf("%d\n",end->data);
                 break;                       
               }
      case 3 : 
             {
                 opertion o1;
                 pthread_t dog;
                 printf("请输入删除节点数据\n");
                 int data = 0;
                 scanf("%d",&data);
                 o1.data = data;
                 o1.p = head;
                 o1.end = end;
                 int erro =  pthread_create(&dog,NULL,delete_data,(void*)&o1);
                 if(erro != 0)  {fprintf(stderr,"%s\n",strerror(erro));}  
                 pthread_join(dog,NULL);
                 end = o1.end;
                 head = o1.p;              
                break;
             }
      case 4: {
                 opertion o1;
                 pthread_t dog;
                 printf("打印结果\n");
                 o1.p = head;
                 o1.end = end;
                 int erro =  pthread_create(&dog,NULL,display_data,(void*)&o1);
                 if(erro != 0)  {fprintf(stderr,"%s\n",strerror(erro));}  
                 pthread_join(dog,NULL);
                 end = o1.end;               
                break;
              }
      case 5 : {
                  printf("即将退出程序...\n");
                  sleep(1);
                  flag = 0 ;
                  break;
               }
      }
  }
   return 0 ;
}

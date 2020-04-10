#include <pthread.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
typedef struct{
	int code;
	char name[20];
	double balance;
	pthread_mutex_t mutex;
}Account;

typedef struct{
	int    code;
	double amt;
	Account *pa;
}Operation;

Account* init_account(int code,char *name, double balance)
{
	Account *pa = (Account*)calloc(1,sizeof(Account));
	assert(pa != NULL);
	pa->code = code;
	if(name == NULL) strcpy(pa->name,"unknow");
	else strcpy(pa->name,name);
	pa->balance = balance;
	pthread_mutex_init(&pa->mutex,NULL);
	return pa;
}

void     *destroy_account(void * arg)
{
         Operation *o3 = (Operation*)arg; 
	 pthread_mutex_destroy(&o3->pa->mutex);
	 free(o3->pa);
         printf("用户已被删除\n");
}


void    *withdraw_account(void * arg)
{
        Operation *o1 = (Operation*)arg;
	int err;
	assert(o1->pa != NULL);
	err = pthread_mutex_lock(&(o1->pa->mutex));
	assert(err == 0);

	double balance = o1->pa->balance;
	usleep(100);
	if(o1->amt < 0 || o1->amt > o1->pa->balance){
		err=pthread_mutex_unlock(&(o1->pa->mutex));
		assert(err == 0);
                printf("卡内金额不足，取出金额失败...即将返回\n");
	 	return 0;
	}
	o1->pa->balance -= o1->amt;
        //printf("%f\n",o1->pa->balance);
	err = pthread_mutex_unlock(&(o1->pa->mutex));
	assert(err == 0);
}




double   check_balance(Account *pa)
{
	assert(pa != NULL);
	double amt = pa->balance;
	usleep(10000);
	return amt;
}
void    deposit_account(void *arg)
{
        Operation * o2 = (Operation*)arg;
	assert(o2->pa != NULL);
	pthread_mutex_lock(&o2->pa->mutex);
	double balance = o2->pa->balance;
	usleep(100);
	if(o2->amt < 0){
                printf("atm can not < 0\n");
		pthread_mutex_unlock(&o2->pa->mutex);
	 	return 0;
	}
	balance += o2->amt;
	o2->pa->balance = balance;
	pthread_mutex_unlock(&o2->pa->mutex);
}

void meun(void){
printf("1.创建账户\n");
printf("2.查询金额\n");
printf("3.存入金额\n");
printf("4.取出金额\n");
printf("5.销毁账户\n");
printf("6.退出程序\n");
printf("请输入要执行的命令\n");
}


int main(void)
{
   int cnt = 0 , flags = 1,order = 0;
   Account *p[11];
   while(flags){
   meun();
   while(1){
   int r = scanf("%d",&order);
   if(!r | order > 6 | order < 1){printf("输入错误，请重新输入\n");}
   else                          {break;}
   } 
   switch(order){
   case 1:
          printf("请输入要创建的用户ID，用户名称name，用户现存金额\n");
          int id = 0; char name[20]; double m = 0 ; int i = 0; int flag = 0;
          scanf("%d",&id); scanf("%s",name); scanf("%lf",&m);
          for(i = 1 ; i <= cnt ; ++i){
             Account *tmp = p[i];
             if(id == p[i]->code)  {printf("用户已存在，无法再次创建\n"); break; flag = 1 ;}
          }
          if(flag){break;}
          else    {p[++cnt] = init_account(id,name,m);}
          break;
   
  case 2 :
            printf("请输入用户ID\n");
            int idm = 0 ,  js = 0 , fla = 1 ;
            scanf("%d",&idm);
            for(js = 1 ; js <= cnt ; ++js) {
              if(p[js]->code == idm){
              printf("您的余额为%f...\n",check_balance(p[js]));
              fla = 0 ;
              break; 
              }
            }
            if(fla) {printf("用户不存在\n");}
            break;
  case 3 :
            printf("请输入用户ID\n");
            int idd = 0 ,  jm = 0 , fl = 1 ,error;
            pthread_t girl;
            Operation o2 ;
            scanf("%d",&idd);
            for(jm = 1 ; jm <= cnt ; ++jm) {
              if(p[jm]->code == idd){
               printf("当前余额为%f ..\n",p[jm]->balance);
               printf("请输入存款金额\n");
               scanf("%lf",&o2.amt);
               o2.pa = p[jm]; o2.code = idd ;
               error = pthread_create(&girl,NULL,deposit_account,(void*)&o2);  
               if(error != 0)  {fprintf(stderr,"%s\n",strerror(error));}
               pthread_join(girl,NULL);
               printf("当前余额为%f ..\n",p[jm]->balance);
               fl = 0 ;
              break; 
              }
            }
            if(fl) {printf("用户不存在\n");}       
            break;
  case 4 :
           printf("请输入用户ID\n");
           int ids = 0 , j = 1 , flagm = 1 ;
           scanf("%d",&ids);
           for(int j = 1 ;j <= cnt ; ++i) {
              if(p[j]->code == ids)  {
                 flagm = 0;
                 printf("此时卡内金额为%f ..\n",p[j]->balance);
                 printf("请输入要取出的金额\n");
                 double mon = 0;  scanf("%lf",&mon);
                 Operation o1;  pthread_t boy ;
                 o1.code = id ; o1.amt = mon ; o1.pa = p[j];
                 int err = pthread_create(&boy,NULL,withdraw_account,(void*)&o1);
	         if(err != 0) {fprintf(stderr,"%s\n",strerror(err));}
                 pthread_join(boy,NULL);
                 printf("此时剩余金额为%lf ..\n",p[j]->balance);
                 break;
              }
           } 
            if (flagm)  {printf("用户不存在\n");}
            break;
   case 5 :
            printf("请输入用户ID\n");
            int idds = 0 ,  jms = 0 , fls = 1 ,errors;
            pthread_t dog;
            Operation o3 ;
            scanf("%d",&idds);
            for(jms = 1 ; jms <= cnt ; ++jms) {
              if(p[jms]->code == idds){
               o3.pa = p[jms]; o3.code = idds ;
               errors = pthread_create(&dog,NULL,destroy_account,(void*)&o3);  
               if(error != 0)  {fprintf(stderr,"%s\n",strerror(error));}
               pthread_join(dog,NULL);
               fls = 0 ;
              break; 
              }
            }
            if(fls) {printf("用户不存在\n");}       
            break;
   case 6 :
            flags = 0;
            printf("即将退出......\n");
            sleep(1);
            break;
  }
 }
 return 0 ;
}




















	/*pthread_t boy,girl;
	int       err;
	Account *pa = init_account(1001,NULL,10000);
	//---first thread
	Operation o1;
	strcpy(o1.name,"boy");
	o1.amt = 10000;
	o1.pa = pa;
	err = pthread_create(&boy,NULL,withdraw_account,(void*)&o1);
	if(err != 0){
		fprintf(stderr,"%s\n",strerror(err));
	}
        printf("%f ..\n",pa->balance);
	//---second thread
	Operation o2;
	strcpy(o2.name,"girl");
	o2.amt = 10000;
	o2.pa = pa;
	err = pthread_create(&girl,NULL,withdraw_account,(void *)&o2);
	if(err != 0){
		fprintf(stderr,"%s\n",strerror(err));
	}
	pthread_join(boy,NULL);
	pthread_join(girl,NULL);
	double balance = check_balance(pa);
	printf("account balance: %8.3f\n",balance);
	destroy_account(pa);*/


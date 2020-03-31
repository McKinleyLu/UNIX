#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	pid_t pid;
	char cmd1[10],cmd2[10];
	char cmd[10];
	int i,a1,a2,flag=0,ret1,ret2;
	printf("$");
	while(1){
		scanf("%[^\n]",cmd);
		a1=0;
		a2=0;
		for(i=0;i<10;i++){
			if(cmd[i]==" " & cmd[i+1]!=" "){
				flag=1;
				i=i+1;
			}else if(cmd[i]==" " & cmd[i+1]==" "){
				break;
			}
			if(flag==0){
				cmd1[a1]=cmd[i];
				a1=a1+1;
			}
			if(flag==1){
				cmd2[a2]=cmd[i];
				a2=a2+1;
			}
		}
		pid=fork();
		if(pid==-1){
			printf("Usage:fork error\n");
			exit(-1);
		}else if(pid==0){
			if(a2==0){
				execlp(cmd1,cmd1,NULL);
			}else{
				execlp(cmd1,cmd1,cmd2,NULL);
			}
		}
		wait(0);
		printf("\n$");
	}
	return 0;
}

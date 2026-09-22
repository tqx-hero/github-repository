#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int num =10;
int main(){
	int sum =100;
	pid_t pid;
	printf("......\n");
	if((pid = fork()) <0){
		perror("");
		exit(-1);
	}
	if(!pid){
		//子进程中进行处理
		printf("进行子进程处理....\n");
		while(sum <200){
			num++;
			++sum;
		}
		printf("子进程中： sum = %d,num = %d\n",sum,num);
	}else{
		if(waitpid(-1,NULL,0))
			fprintf(stdout,"父进程中: sum = %d,num = %d\n",sum,num);
	}
	return 0;
}

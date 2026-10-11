#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
//生成5个子进程
int count;
void collection_child(int signum){
	pid_t pid;
	//千万不要使用if，因为信号不能排队，当多个子进程同时发送SIGCHLD时，信号只会记录一次
	//使用if会出现回收不全的情况
	while((pid = waitpid(-1,NULL,WNOHANG)) >0)//使用while循环回收，直到没有可回收的子进程退出
		printf("已回收第 %d 个子进程 : %d\n",++count,pid);
}

int main(){
	count = 0;
	pid_t pid;
	//注册信号handler
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = collection_child;
	sigaction(SIGCHLD,&sa,NULL);
	for(int i=0;i < 5;++i){
		if((pid = fork()) < 0 )
			perror("");
		else if(pid ==0){
			fprintf(stdout,"子进程已创建，pid = %d\n",getpid());
			sleep(4);
			exit(0);
		}
	}
	while(count < 5);
	printf("已全部回收所有的子进程\n");
	return 0;
}

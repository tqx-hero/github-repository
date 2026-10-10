#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//使用sa_sigaction()处理
int flag;
void act_handler(int signum,siginfo_t * info,void* ucontext){
	printf("信号编号 = %d\n",signum);
//	printf("传入的参数 = %d\n",info->si_value);
	flag = 0;
}

int main(){
	flag = 1;
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = act_handler;
	act.sa_flags = SA_SIGINFO | SA_RESETHAND;
	sigaction(SIGINT,&act,NULL);
	while(flag){
		printf("1...\n");
		sleep(1);
	}
	while(1){
		printf("2..\n");
		sleep(1);
	}
	return 0;
}

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int flag;
//修改SIGINT信号的处理逻辑
void sigint_handler(int signum){
	printf("SIGINT 信号被发送过来了 ,num = %d\n",signum);
	flag = 0;
}
int main(){
	flag = 1;
	struct sigaction sat,oldsat;
	bzero(&sat,sizeof(sat));
	sat.sa_handler = sigint_handler;
	sigaction(SIGINT,&sat,&oldsat);
	while(flag){
		printf("正在循环1...\n");
		sleep(1);
	}
	//SIGINT信号处理完成后，恢复其默认信号
	sigaction(SIGINT,&oldsat,NULL);
	while(1){
		printf("正在循环2...\n");
		sleep(1);
	}
	return 0;
}

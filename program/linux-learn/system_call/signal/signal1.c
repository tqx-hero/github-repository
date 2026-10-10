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
	__sighandler_t old_hdr;
	old_hdr = signal(SIGINT,sigint_handler);
	while(flag){
		printf("正在循环1...\n");
		sleep(1);
	}
	printf("old handler = %d\n",(old_hdr == SIG_DFL));
	//SIGINT信号处理完成后，恢复其默认信号
	signal(SIGINT,old_hdr);
	while(1){
		printf("正在循环2...\n");
		sleep(1);
	}
	return 0;
}

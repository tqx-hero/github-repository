#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//setitimer(2)
int count = 0;
void sig_handler(int signum){
	printf("SIGARLM 定时器到时\n");
	count++;
	//让定时器循环5次结束
	if(count == 5){
		struct itimerval itl;
		bzero(&itl,sizeof(itl));
		if(setitimer(ITIMER_REAL,&itl,NULL) == -1)
			perror("reset timer error");
	}
}

int main(){
	struct itimerval itl;
	//设置定时器,设定初始间隔与后续间隔都为1s
	itl.it_interval.tv_sec = 1;
	itl.it_value.tv_sec =1;
	if(setitimer(ITIMER_REAL,&itl,NULL) == -1){
		perror("setitimer error");
		exit(-1);
	}
	//注册信号handler
	struct sigaction sgn;
	sigemptyset(&sgn.sa_mask);
	sgn.sa_handler = sig_handler;
	sgn.sa_flags = 0;
	sigaction(SIGALRM,&sgn,NULL);
	while(1){
		printf("循环中...\n");
		usleep(1000* 500);
	}
	return 0;
}

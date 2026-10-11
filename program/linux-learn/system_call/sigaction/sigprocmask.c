#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//sigprocmask(2)的错误使用：
int main(){
	sigset_t newset;
	sigemptyset(&newset);	//初始化信号集
	sigaddset(&newset,SIGINT); //将SIGINT添加到信号集
	if(sigprocmask(SIG_BLOCK,&newset,NULL) == -1){ //将信号集添加到阻塞集
		perror("sigprocmask blocked error");
		exit(-1);
	}
	while(1){
		printf("循环停不下来\n");
		sleep(5);
		sigprocmask(SIG_UNBLOCK,&newset,NULL);
		printf("可以停下来了\n");
		sleep(10);
	}
	return 0;
}

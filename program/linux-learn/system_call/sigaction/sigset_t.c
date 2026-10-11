#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//sigset_t的操作
int main(){
	struct sigaction sg;
	sigfillset(&sg.sa_mask); //将sigset所有位置1	
	printf("sigfill SIGINT是否存在于这个屏蔽字 = %d\n",sigismember(&sg.sa_mask,SIGINT));
	sigemptyset(&sg.sa_mask); //将sigset所有位置0
	printf("sigempty SIGINT是否存在于这个屏蔽字 = %d\n",sigismember(&sg.sa_mask,SIGINT));
	sigaddset(&sg.sa_mask,SIGINT); //将信号添加到屏蔽字
	printf("sigaddset SIGINT是否存在于这个屏蔽字 = %d\n",sigismember(&sg.sa_mask,SIGINT));
	sigdelset(&sg.sa_mask,SIGINT); //将信号从屏蔽字删除
	printf("sigdelset SIGINT是否存在于这个屏蔽字 = %d\n",sigismember(&sg.sa_mask,SIGINT));
	return 0;
}

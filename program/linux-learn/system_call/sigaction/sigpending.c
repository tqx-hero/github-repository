#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//sigpending(2)
int main(){
	//将SIGINT放入阻塞集，阻塞期间使用ctrl+c给进程发送SIGINT信号
	sigset_t bset,p_set;
	sigemptyset(&bset);
	sigaddset(&bset,SIGINT);
	sigprocmask(SIG_BLOCK,&bset,NULL);
	printf("设置SIGINT到阻塞集成功，现在可以发信号了\n");
	sleep(5);
	//显示它的未决信号
	if(sigpending(&p_set) == -1){
		perror("sigpending error");
		exit(-1);
	}
	//查看未决信号是否存在SIGINT
	printf("当前未决信号是否存在SIGINT? : %d\n",sigismember(&p_set,SIGINT));

	return 0;
}

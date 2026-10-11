#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
//回收5个子进程

int main(){
	pid_t pid;
	//注册信号handler
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags |= SA_NOCLDWAIT;
	sa.sa_handler = SIG_DFL;
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
	while(1);
	return 0;
}

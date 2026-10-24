#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
void child_exec(){
	while(1){
		printf("子进程正在执行...\n");
		sleep(1);
	}
}

void sigint_handler(int signum){
	const char *str = "主进程收到SIGINT信号!\n";
	write(STDOUT_FILENO,str,strlen(str) + 1);
}

int main(){
	pid_t pid;
	pid =fork();
	struct sigaction act;
	act.sa_handler = sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESETHAND;
	sigaction(SIGINT,&act,NULL);
	switch(pid){
		case -1:
			perror("fork error");
			exit(EXIT_FAILURE);
		case 0 :
			child_exec();
			exit(EXIT_SUCCESS);
		default:
			break;
	}
	//父进程使用sigsuspend()等待信号
	sigset_t set;
	sigfillset(&set);
	sigdelset(&set,SIGINT);
	//等待进程被唤醒
	sigsuspend(&set);
	//给子进程发送信号SIGQUIT
	if(kill(pid,SIGQUIT)){
		perror("给子进程发送信号失败");
		exit(EXIT_FAILURE);
	}
	while(waitpid(pid,NULL,0) <= 0);
	printf("子进程回收成功，主进程退出\n");
	return 0;
}

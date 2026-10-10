#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
//使用fork生成子进程，父进程循环打印，子进程5秒后给父进程发送SIGINT信号
int main(){
	pid_t pid;
	if((pid = fork()) == -1){
		perror("fork error");
		exit(-1);
	}
	if(pid  ==0){
		while(1){
			printf("子进程正在执行...\n");
			usleep(1000 * 500);
		}
	}
	sleep(5);
	kill(pid,SIGINT);
	if(waitpid(pid,NULL,0) == -1)
		perror("waitpid error");
	return 0;
}

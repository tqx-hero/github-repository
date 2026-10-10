#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
//raise()
int main(){
	pid_t pid;
	if((pid = fork()) == -1){
		perror("fork error");
		exit(-1);
	}
	if(pid == 0){
		sleep(5);
		//5秒后子进程给自己发送终止信号
		raise(SIGTERM);
		printf("子进程给自己发送信号成功\n");
		exit(0);
	}
	if(waitpid(pid,NULL,0) == -1)
		perror("waitpid error");
	return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	if((pid = fork()) <0)
		perror("");
	else if(pid == 0){
		printf("子进程: %d 执行...\n",getpid());
		sleep(2);
		exit(2);
	}else{
		int status;
		pid_t cid;
		while(1){
			printf("父进程正在执行...\n");
			if((cid = wait(&status)) >0){
				if(WIFEXITED(status))
					printf("子进程: %d 已被回收,status = %d\n",cid,WEXITSTATUS(status));
			}
			sleep(1);
		}
	}
	return 0;
}

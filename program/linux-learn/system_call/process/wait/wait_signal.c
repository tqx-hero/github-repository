#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
//测试通过信号中断子进程
int main(){
	pid_t pid;
	if((pid = fork()) <0)
		perror("");
	else if(pid == 0){
		while(1){
			fprintf(stdout,"子进程执行中...\n");
			sleep(1);
		}
	}else{
		int status;
		if(wait(&status) > 0){
			if(WIFEXITED(status))
				fprintf(stdout,"子进程正常退出，退出码 = %d\n",WEXITSTATUS(status));
			else if(WIFSIGNALED(status))
				fprintf(stdout,"子进程被信号中断，信号类型 = %d\n",WTERMSIG(status));			
		}
		
	}
	return 0;
}

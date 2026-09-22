#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
//生成5个子进程
int main(){
	pid_t pid;
	for(int i=0;i < 5;++i){
		if((pid = fork()) < 0 )
			perror("");
		else if(pid ==0){
			fprintf(stdout,"子进程已创建，pid = %d\n",getpid());
			exit(0);
		}
	}

	return 0;
}

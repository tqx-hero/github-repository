#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
//创建7个子进程
int main(){
	int i,status = 0;
	pid_t pid;
	for(i=0;i<7;++i){
		if((pid = fork()) == -1){
			perror("");
			exit(-1);
		}else if(pid == 0){
			fprintf(stdout,"子进程ID = %d\n",getpid());
			sleep(i+1);
			break;
		}else{
			pid_t pd;
			while((pd = waitpid(-1,&status,WNOHANG)) == 0);
			if(pd > 0)
				fprintf(stdout,"退出的子进程 = %d\n",pd);
			else
				fprintf(stdout,"所有子进程已经全部退出!\n");
		}
	}
	return 0;
}

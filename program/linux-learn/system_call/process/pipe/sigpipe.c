#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//测试sigpipe信号
int main(){
	int fds[2];
	pid_t pid;
	if(pipe(fds) == -1){
		perror("pipe error");
		return -1;
	}
	if((pid = fork()) == -1){
		perror("fork error");
		close(fds[0]);
		close(fds[1]);
		return -1;
	}
	if(pid ==0){
		char buf[1024];
		close(fds[0]);
		printf("子进程中...\n");
		memset(buf,'a',sizeof(buf));
		int i=1;
		ssize_t nbytes;
		while(1){
			sleep(2);
			nbytes = write(fds[1],buf,sizeof(buf));
			if(nbytes == -1){
				perror("write error");
				break;
			}
			printf("i = %d\n",i++);
		}
	}
	else{
		close(fds[0]);
		waitpid(-1,NULL,0);
	}
//	close(fds[0]);
	close(fds[1]);
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>
//测试管道的大小。
//结果输出为i=64，即放入64k数据后管道满
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
		printf("子进程中...\n");
		memset(buf,'a',sizeof(buf));
		int i=1;
		while(1){
			write(fds[1],buf,sizeof(buf));
			printf("i = %d\n",i++);
		}
	}
	else{
		while(1);
	}
	close(fds[0]);
	close(fds[1]);
	return 0;
}

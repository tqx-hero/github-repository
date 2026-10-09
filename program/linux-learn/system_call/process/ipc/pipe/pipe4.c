#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
int main(){
	int filedes[2];
	if(pipe(filedes) == -1){
		perror("create pipe error");
		exit(-1);
	}
	pid_t pid;	
	char buf[128];
	if((pid = fork()) == -1){
		perror("fork error");
		exit(-1);
	}else if(pid ==0){
		//子进程的处理
		close(filedes[1]);	//子进程只负责读，关闭写
		//循环读，设置描述符为非阻塞状态
		int flag = fcntl(filedes[0],F_GETFL);
		flag |= O_NONBLOCK;
		fcntl(filedes[0],F_SETFL,flag);
		ssize_t nbytes;
		while(1){
			nbytes = read(filedes[0],buf,sizeof(buf));
			if(nbytes == -1 &&  errno == EAGAIN){
				//printf("未读到消息..\n");
				continue;
			}
			if (nbytes == -1){
				perror("read fd error");
				close(filedes[0]);
				exit(-1);
			}
			if(!nbytes){
				fprintf(stdout,"读取结束\n");
				close(filedes[0]);
				exit(0);
			}
			fprintf(stdout,"%s\n",buf);
		}
	}else{
		close(filedes[0]);
		int i=0;
		while(1){
			char message[] = "hello world!";
			write(filedes[1],message,sizeof(message));
			sleep(1);
		}
	}
	
	return 0;
}

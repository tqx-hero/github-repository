#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
//定义需要开启的管道
#define BUF_SIZE 256
typedef struct {
	pid_t pid;
	char buf[BUF_SIZE];
} message_t;
int main(int argc,char ** argv){
	if(argc < 3){
		fprintf(stderr,"参数必须要有读管道文件、写管道文件\n");
		exit(-1);		
	}
	//判断管道是否存在
	if(access(argv[1],F_OK) == -1 && mkfifo(argv[1],0644) == -1){
		//创建管道
		perror("mk fifo1 error");
		exit(-1);
	}
	if(access(argv[2],F_OK) == -1 && mkfifo(argv[2],0644) == -1){
		//创建管道
		perror("mk fifo2 error");
		exit(-1);
	}
	//打开文件描述符
	int r_fd= -1,w_fd = -1;
	ssize_t nbytes;
	message_t msg;
	//创建子进程，分别对管道进行读写
	pid_t pid;
	if((pid = fork()) == -1){
		perror("fork error");
		goto fail_ret;
	}
	//子进程负责读取管道
	if(pid == 0){
		if((r_fd = open(argv[1],O_RDONLY)) == -1){
			perror("open fifo1 error");
			goto fail_ret;
		}
		while(1){
			nbytes = read(r_fd,&msg,sizeof(message_t));
			if(nbytes == 0){
				printf("对方已关闭对话\n");
				break;
			}
			fprintf(stdout,"%d : %s\n",msg.pid,msg.buf);
		}
		close(r_fd);
		unlink(argv[1]);
		exit(0);
	}else{
		if((w_fd = open(argv[2],O_WRONLY)) == -1){
			perror("open fifo2 error");
			goto fail_ret;
		}
		//父进程负责写入管道
		msg.pid = getpid();
		while(1){
			scanf("%s",msg.buf);
			nbytes = write(w_fd,&msg,sizeof(message_t));
			//完善还需要注册SIGCHLD信号的处理事件，以免默认SIGIGN被忽略。
			printf("nbytes = %ld\n",nbytes);
			/*
			if(nbytes == -1){
				perror("write error");
				waitpid(pid,NULL,0);
				break;
			}
			*/
		}
	}
	close(w_fd);
	unlink(argv[2]);
	return 0;
fail_ret:
	if(r_fd != -1){
		close(r_fd);
		unlink(argv[1]);
	}
	if(w_fd != -1){
		close(w_fd);
		unlink(argv[2]);
	}
	exit(-1);
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//创建有名管道fifo
int main(){
	char *path = "./myfifo";
	struct stat st;
	//判断管道是否已经命名
	if(stat(path,&st) == 0){
		if(!S_ISFIFO(st.st_mode)){
			fprintf(stderr,"该文件不是管道文件，请重命名!\n");
			exit(-1);
		}
	} 
	//如果管道还不存在，创建管道
	else if(mkfifo(path,0666) == -1){
		perror("mkfifo error");
		exit(-1);
	}
	pid_t pid;
	int fd;
	if((pid = fork()) == -1){
		perror("fork error");
		exit(-1);
	}
	if(pid ==0){
		//打开管道.子进程以写入方式打开
		fd = open(path,O_WRONLY);
		if(fd == -1){
			perror("open fifo error");
			exit(-1);
		}
		char buf[128]= "hello world!";
		write(fd,buf,sizeof(buf));
	}else{
		fd = open(path,O_RDONLY);
		if(fd == -1){
			perror("open fifo error");
			return -1;
		}
		char buf[128];
		read(fd,buf,sizeof(buf));
		fprintf(stdout,"%s\n",buf);
	}
	close(fd);
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int fds[2];
	ssize_t nbytes;
	//创建管道，生成读写2端的文件描述符
	if(pipe(fds) == -1){
		perror("pipe create error");
		exit(-1);
	}
	switch(fork()){
		case -1:
			perror("fork error");
			break;
		case 0:
			//子进程，仅读取管道内的数据
			close(fds[1]);	//关闭写管道，因为只用读取
			char buf[128];
			nbytes = read(fds[0],buf,sizeof(buf));
			fprintf(stdout,"读到的管道内容：%s\n",buf);
			close(fds[0]);
			break;
		default:
			//父进程，只写入管道
			close(fds[0]);
			char* rstr = "国庆快乐，同志们!";
			write(fds[1],rstr,strlen(rstr)+1);
			close(fds[1]);
			break;
	}
	return 0;
}

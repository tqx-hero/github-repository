#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
//使用dup(2)实现标准输出重定向
int main(int argc,char **argv){
	int fd;
	if(argc < 2){
		fprintf(stderr,"Usage main : <argv[1]> must not be empty!\n");
		exit(EXIT_FAILURE);
	}
	
	//打开文件
	fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(fd < 0){
		perror("open file error");
		exit(EXIT_FAILURE);
	}

	//关闭标准输出，将fd重定向到新的描述符，即标准输出(原理是定向到最小可用的描述符)
//	close(STDOUT_FILENO);
//	dup(fd);

	//需要使用原子操作的dup2，避免多线程对描述符表修改出现的同步问题
	dup2(fd,STDOUT_FILENO);

	if(fd != STDOUT_FILENO)
		close(fd);//fd描述符提前关闭，防泄露,注意一定要先判断fd是否是标准输出

	puts("hello!");
	return 0;
}

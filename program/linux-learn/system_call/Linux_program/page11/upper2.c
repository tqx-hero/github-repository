#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
//重定向,使用freopen()函数
int main(int argc,char** argv){
	if(argc < 2){
		fprintf(stderr,"参数必须不少于2个\n");
		exit(EXIT_FAILURE);
	}
	//将文件打开，标准输入关闭，将文件重定向到标准输入
	//等价于fd = open();dup2(fd,0)
	/**
	if(!freopen(argv[1],"r",stdin)){
		perror("open fd error");
		exit(EXIT_FAILURE);
	}
	*/
	int fd = open(argv[1],O_RDONLY);
	if(dup2(fd,0) == -1){
		perror("dup2 error");
		exit(EXIT_FAILURE);
	}
	close(fd);
	//执行upper程序,该程序以O_RDONLY方式打开/dev/tty，从中read(0)，然后强转成大写write(1)
	execl("./upper","upper",NULL);
	return 0;
}

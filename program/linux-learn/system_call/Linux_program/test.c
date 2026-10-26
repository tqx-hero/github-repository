#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
//示例重定向文件描述符、复制文件描述符
int main(){
	dup2(1,2);
	int fd = open("./txt",O_RDWR | O_CREAT,0666);
	dup2(fd,1);
	close(fd);
	printf("hello world\n");
	fprintf(stderr,"错误信息打印...\n");
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
//使用非阻塞方式只读打开有名管道
int main(){
	mkfifo("./myfifo1",0666);
	int fd = open("./myfifo1",O_RDONLY | O_NONBLOCK);
	if(fd == -1)
		perror("open fifo error");
	printf("管道打开成功, fd = %d\n",fd);
	return 0;
}

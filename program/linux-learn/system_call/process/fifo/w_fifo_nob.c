#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
//只写方式非阻塞打开管道
int main(){
	mkfifo("./myfifo1",0666);
	int fd = open("./myfifo1",O_WRONLY | O_NONBLOCK);
	if(fd == -1){
		perror("open fifo error");
		return -1;
	}
	printf("管道打开成功, fd = %d\n",fd);
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
//验证以只读方式、阻塞形式打开管道时，会阻塞到其他进程写打开后才会打开管道
int main(){
	mkfifo("./myfifo1",0666);
	int fd = open("./myfifo1",O_RDONLY);
	if(fd == -1)
		perror("open fifo error");
	printf("管道打开成功, fd = %d\n",fd);
	return 0;
}

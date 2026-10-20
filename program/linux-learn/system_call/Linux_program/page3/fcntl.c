#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//fcntl用法
int main(){
	int fd;
	if((fd = open("./test.txt",O_CREAT | O_RDWR | O_NONBLOCK,0600)) == -1){
		perror("open fd error");
		exit(-1);
	}
	int config = fcntl(fd,F_GETFD);
	printf("是否exec执行后自动关闭的fd? : %d\n",(config & FD_CLOEXEC) != 0);
	fcntl(fd,F_SETFD,config | FD_CLOEXEC);
	
	config = fcntl(fd,F_GETFD);
	printf("exec执行后自动关闭的fd? : %d\n",(config & FD_CLOEXEC) != 0);
	
	int fdl = fcntl(fd,F_GETFL);
	printf("是否是阻塞文件 : %d\n",(fdl & O_NONBLOCK) != 0);
	
	return 0;
}

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
//设置设备文件为非阻塞
int main(){
	//方案1：打开文件时设置打开方式 | O_NONBLOCK
	//int fd = open("/dev/tty",O_RDONLY | O_NONBLOCK );
	int fd = open("/dev/tty",O_RDONLY);
	if(fd == -1){
		perror("");
		exit(-1);
	}
	//方案2：使用系统调用fcntl设置文件的属性
	int flags = fcntl(fd,F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(fd,F_SETFL,flags);
	fprintf(stdout,"设备的fd = %d\n",fd);
	char buf[128];
	read(fd,buf,sizeof(buf));
	printf("buf = %s\n",buf);
	close(fd);
	return 0;
}

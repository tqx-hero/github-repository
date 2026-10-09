#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//pipe2子进程执行的程序，用于输出父进程写入管道的内容
int main(int argc,char** argv){
	int rfd,wfd;
	sscanf(argv[1],"%d",&rfd);
	sscanf(argv[2],"%d",&wfd);
	printf("rfd = %d\n",rfd);
	printf("wfd = %d\n",wfd);
	close(wfd); //关闭写描述符
	char buf[128];
	read(rfd,buf,sizeof(buf));
	printf("管道中的内容：%s\n",buf);
	close(rfd);
	return 0;
}

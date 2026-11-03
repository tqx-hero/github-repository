#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
//pread()/write()系统调用
int main(){
	int fd;
	if((fd = open("./test",O_RDWR,0600)) == -1){
		perror("open file error");
		exit(-1);
	}
	//读写
	char buf[4096];
	if(pread(fd,buf,sizeof(buf),100) == -1){
		perror("pread error");
		exit(-1);
	}
	printf("读取的内容 : %s\n",buf);
	sprintf(buf,"%s","你是我的，我是你的谁!");
	write(fd,buf,strlen(buf) +1);
	return 0;
}

#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define MMAP_BUF_SIZE 16
//使用msync()主动刷新到文件
int main(){
	int fd;
	if((fd = open("./test.txt",O_CREAT | O_APPEND | O_RDWR,0644)) == -1){
		perror("open file error");
		exit(-1);
	}
	char* buf = mmap(NULL,MMAP_BUF_SIZE,PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
	close(fd);
	if(buf == MAP_FAILED){
		perror("mmap error");
		exit(-1);
	}
	int cnt =1;
	cnt++;
	char msg_buf[]="hello world";
	memcpy(buf,msg_buf,sizeof(msg_buf)-1);
	if(msync(buf,sizeof(msg_buf)-1,MS_SYNC | MS_INVALIDATE) == -1)
		perror("msync error");
	if(munmap(buf,MMAP_BUF_SIZE) == -1)
		perror("munmap error");
	return 0;
}


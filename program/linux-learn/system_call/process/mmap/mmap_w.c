#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define MMAP_BUF_SIZE 16
//mmap()修改文件
int main(){
	int fd;
	if((fd = open("./test.txt",O_CREAT | O_APPEND | O_RDWR,0644)) == -1){
		perror("open file error");
		exit(-1);
	}
	printf("页大小 = %ld\n",sysconf(_SC_PAGE_SIZE));
	char* buf = mmap(NULL,MMAP_BUF_SIZE,PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
	if(buf == MAP_FAILED){
		perror("mmap error");
		exit(-1);
	}
	char msg_buf[]="hello world";
	memcpy(buf,msg_buf,sizeof(msg_buf));
	if(munmap(buf,MMAP_BUF_SIZE) == -1)
		perror("munmap error");
	close(fd);
	return 0;
}


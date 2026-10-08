#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define MMAP_BUF_SIZE 16
//mmap()文件映射初体验
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
	char msg_buf[MMAP_BUF_SIZE];
	memcpy(msg_buf,buf,MMAP_BUF_SIZE);
	msg_buf[MMAP_BUF_SIZE] = '\0';
	fprintf(stdout,"该文件内容: %s\n",msg_buf);
	if(munmap(buf,MMAP_BUF_SIZE) == -1)
		perror("munmap error");
	close(fd);
	return 0;
}


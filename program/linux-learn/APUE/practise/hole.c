#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define HOLE_NAME "/tmp/hole.dat"

#define EXIT(exitnum) if(fd >= 0) \
			close(fd);\
			exit(exitnum)
//创建空洞文件
int main(){
	int fd = -1;
	fd = open(HOLE_NAME,O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(fd < 0){
		perror("open file error");
		EXIT(1);
	}

	if(write(fd,"hello",5) < 5){
		perror("write error");
		EXIT(1);
	}

	lseek(fd,1024,SEEK_CUR);
	if(write(fd,"world",5) < 5){
		perror("write end error");
		EXIT(1);
	}
	EXIT(0);
}

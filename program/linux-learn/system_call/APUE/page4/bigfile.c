#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

//设置空洞文件，观察它的属性：文件大小、所占磁盘块数量
int main(int argc,char ** argv){
	int fd;

	if(argc < 2){
		fprintf(stderr,"usage main():参数不足! \n");
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC,0600);
	if(fd < 0){
		perror("open file error");
		exit(EXIT_FAILURE);
	}

	if(ftruncate(fd,5LL * 1024LL * 1024LL * 1024LL - 1LL) < 0){
		perror("ftruncate() error");
		exit(EXIT_FAILURE);
	}
	write(fd,"h",1);

	close(fd);
	return 0;
}

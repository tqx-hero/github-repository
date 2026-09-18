#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>       
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char** argv,char** env){
	if(argc != 2){
		fprintf(stderr,"请输入要写入文件的内容\n");
		return -1;
	}
	int fd = open("test.txt",O_CREAT | O_RDWR | O_APPEND,0644);
	if(fd == -1){
		fprintf(stderr,"文件打开失败\n");
		return -1;
	}
	write(fd,argv[1],strlen(argv[1]));
	close(fd);
	return 0;
}

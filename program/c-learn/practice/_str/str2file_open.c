#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
//将输入的参数写入文件
int main(int argc,char** argv,char** env){
	if(argc ==1){
		fprintf(stderr,"请输入字符串\n");
		exit(-1);
	}
	int fd = open("test.txt",O_CREAT | O_RDWR | O_TRUNC,0644);
	if(fd == -1){
		fprintf(stderr,"创建文件失败: %s\n",strerror(errno));
		exit(-1);
	}
	int i;
	for(i=1;i< argc;++i){
		write(fd,argv[i],strlen(argv[i]));
		write(fd,"\n",1);
	}
	close(fd);
	return 0;
}

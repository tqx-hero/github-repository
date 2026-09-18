#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>       
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char** argv,char** env){
	int fd = open("test.txt",O_RDONLY);
	if(fd == -1){
		fprintf(stderr,"没有该文件\n");
		return -1;
	}
	char buf[128]={0};
	int r_len = read(fd,buf,sizeof(buf));
	if(r_len){
		printf("读取的文件长度=%d\n",r_len);
		fprintf(stdout,"%s\n",buf);
	}
	close(fd);
	return 0;
}

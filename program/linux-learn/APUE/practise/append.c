#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define FILE_NAME "/tmp/appendlog"
#define EXIT(status)	if(fd >= 0)	\
			   close(fd);	\
			   exit(status)

int main(){
	int fd;
	char buf[128];
	fd = open(FILE_NAME,O_WRONLY | O_CREAT | O_APPEND,0644);
	if(fd < 0){
		perror("open() error");
		EXIT(1);
	}
	
	while(1){
		if(fgets(buf,sizeof(buf),stdin) == NULL){
			perror("fgets() error");
			EXIT(1);
		}
		
		//判断是否是结束
		if(strncasecmp(buf,"end",3) == 0)
			break;

		//写入文件流
		if(write(fd,buf,strlen(buf)) < 0){
			perror("write() error");
			EXIT(1);
		}
	}
	EXIT(0);
}

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
int main(){
	int fd;
	if((fd = open("./test",O_CREAT | O_RDWR | O_TRUNC,0600)) == -1){
		perror("open file error");
		exit(EXIT_FAILURE);
	}
	char buf[1024] = "你好我好大家好";
	write(fd,buf,strlen(buf) + 1);
	//移动指针
	if(lseek(fd,100,SEEK_END) == -1){
		perror("lseek fail");
		goto fail_ret;
	}
	buf[0] = 0;
	//尝试读：
	if(read(fd,buf,sizeof(buf)) == -1){
		fprintf(stderr,"读取失败\n");
		goto write_func;
	}
	printf("读取成功：%s\n",buf);
write_func:
	strcpy(buf,"好个屁!");
	//尝试写
	if(write(fd,buf,strlen(buf) + 1) == -1){
		perror("write error");
		goto fail_ret;
	}
	//读取内容
	lseek(fd,0,SEEK_SET);
	ssize_t bytes = read(fd,buf,sizeof(buf));
	fprintf(stdout,"读到的字节数 ：%ld,文件的内容:%s\n",bytes,buf);
	close(fd);
	return 0;
fail_ret:
	close(fd);
	exit(EXIT_FAILURE);
}

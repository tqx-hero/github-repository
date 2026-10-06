#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
//使用dup()函数复制文件描述符
int main(){
	int fd = open("./dup.txt",O_CREAT | O_RDWR,0644);
	if(fd == -1){
		perror("open file error");
		exit(-1);
	}
	printf("请输入要写入的文件内容: ");
	fflush(stdout);
	char buf[128];
	fgets(buf,sizeof(buf),stdin);
	write(fd,buf,strlen(buf)+1);
	int newfd = dup(fd);
	lseek(fd,0,SEEK_SET);
	char r_buf[128];
	read(newfd,r_buf,sizeof(r_buf));
	//printf("写入文件的内容 : %s\n",r_buf);
	fputs("读出的内容: ",stdout);
	fputs(r_buf,stdout);
	close(fd);
	close(newfd);
	return 0;
}

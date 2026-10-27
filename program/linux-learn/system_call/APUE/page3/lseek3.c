#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
//使用leek函数，通过输入的文件类型来查看是否可以移动读写指针
int main(){
	int fd;
	if((fd = open("./test",O_RDWR | O_APPEND)) == -1){
		perror("open error");
		return -1;
	}
	lseek(fd,0,SEEK_SET);
	char r_buf[1024];
	read(fd,r_buf,sizeof(r_buf));
	printf("读取的内容1 = %s\n",r_buf);
	char buf[] = "helloworld!!!";
	write(fd,buf,sizeof(buf));
	r_buf[0] = 0;
	ssize_t bytes = read(fd,r_buf,sizeof(r_buf));
	printf("bytes = %ld\n",bytes);
	printf("读取的内容2 = %s\n",r_buf);
	return 0;
}

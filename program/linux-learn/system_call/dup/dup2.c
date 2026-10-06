#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
//将标准输出文件绑定a.out的文件描述符
//使用printf()进行输出时,底层调用的write(1,"",..)会将内容重定向输出到a.out文件
int main(){
	int fd = open("./a2.out",O_CREAT | O_RDWR, 0644);
	if(fd == -1){
		perror("open fd error");
		exit(-1);
	}
	int newfd = dup2(fd,1);	//复制a.out的fd,dup()选取的fd是最小可用的fd，关闭1之后，newfd必为1
	char buf[128];
	fgets(buf,sizeof(buf),stdin);
	printf("输入的内容 : %s\n",buf);
	close(fd);
	return 0;
}

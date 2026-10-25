#include <stdio.h>
#include <string.h>
#include <unistd.h>
//popen()打开管道,以写入方式打开
int main(){
	FILE* fptr = popen("grep tqx","w");
	if(!fptr){
		perror("popen error");
		return -1;
	}
	//读取管道内的数据
	char buf[1024];
	printf("请输入字符串:\n");
	scanf("%s",buf);
	write(fileno(fptr),buf,strlen(buf) + 1);
	pclose(fptr);
	return 0;
}

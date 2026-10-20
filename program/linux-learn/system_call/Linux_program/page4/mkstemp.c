#include <stdlib.h>
#include <stdio.h>
//mkstemp()函数的用法
int main(){
	int fd;
	char template[] ="helloworld_XXXXXX";
	if((fd = mkstemp(template)) == -1){
		perror("make temp file error");
		exit(EXIT_FAILURE);
	}
	printf("生成临时文件成功，文件名 = %s\n",template);
	return 0;
}

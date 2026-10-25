#include <stdio.h>
//popen()打开管道
int main(){
	FILE* fptr = popen("uname -a","r");
	if(!fptr){
		perror("popen error");
		return -1;
	}
	//读取管道内的数据
	char buf[1024];
	ssize_t bytes = fread(buf,1,sizeof(buf),fptr);
	printf("%s\n",buf);
	pclose(fptr);
	return 0;
}

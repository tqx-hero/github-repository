#include <unistd.h>
#include <stdio.h>
//#include <unistd.h>
//popen()函数的r使用
int main(){
	FILE* fptr = popen("uname -a","r"); //以读取的方式打开一个管道，该管道从第一个参数(命令)中读取
	char buf[128];
	if(fptr){
		fread(buf,1,sizeof(buf),fptr);
		fprintf(stdout,"%s\n",buf);
	}
	pclose(fptr);
	return 0;
}

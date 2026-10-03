#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFSIZE 1023
//读取ps -aux并输出
int main(){
	FILE* rptr = popen("ps -aux","r");
	if(!rptr){
		perror("popen ps -aux error");
		return -1;
	}
	//读取管道内的数据
	char buf[BUFSIZE+1];
	ssize_t nbytes;
	while(1){
		nbytes = fread(buf,sizeof(char),BUFSIZE,rptr);
		buf[nbytes]=0;
		fprintf(stdout,"%s",buf);
		if(nbytes < BUFSIZE)
			break;
	}
	fclose(rptr);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//验证putenv(3)放入环境变量的是字符串地址

int main(){
	char buf[128] = "MYVAL=tqx";
	if(putenv(buf)){
		perror("putenv() error");
		exit(1);
	}

	strcpy(buf,"MYVAL=abc");
	//返回值为abc
	fprintf(stdout,"%s\n",getenv("MYVAL"));
	exit(0);
}

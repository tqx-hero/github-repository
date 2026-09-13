#include <stdio.h>
#include <stdlib.h>
/**
	获取环境变量
*/
int main(){
	printf("PWD=%s\n",getenv("PWD"));
	printf("JAVA_HOME=%s\n",getenv("JAVA_HOME"));
	return 0;
}

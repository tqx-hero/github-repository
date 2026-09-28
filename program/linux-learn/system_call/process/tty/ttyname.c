#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char* stdin_name =  ttyname(0);
	fprintf(stdout,"标准输入的文件 = %s\n",stdin_name);
	char* stdout_name =  ttyname(1);
	fprintf(stdout,"标准输出的文件 = %s\n",stdout_name);
	char* stderr_name =  ttyname(2);
	fprintf(stdout,"标准错误的文件 = %s\n",stderr_name);
	return 0;
}

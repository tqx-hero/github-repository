#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//测试修改环境变量是否生效
int main(){
	printf("path = %s\n",getenv("PATH"));
	return 0;
}

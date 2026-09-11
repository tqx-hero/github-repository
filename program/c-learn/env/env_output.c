#include <stdio.h>
/**
	获取环境变量的方式
*/
int main(int argc,char** argv,char** env){
	char** ptr = env;
	while(*ptr){
		printf("%s\n",*ptr);
		++ptr;
	}
	return 0;
}

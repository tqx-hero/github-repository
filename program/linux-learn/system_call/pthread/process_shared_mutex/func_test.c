#include <stdio.h>

void init(){
	const char* s = __FUNCTION__;
	const char* s1 = __func__;
	printf("函数 = %s\n",s1);
}

int main(){
	init();
	return 0;
}

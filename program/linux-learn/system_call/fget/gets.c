#include <stdio.h>
//gets()用法
int main(){
	char buf[128];
	gets(buf);
	printf("%s\n",buf);
	return 0;
}

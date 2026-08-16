#include <stdio.h>
extern void * asm_memset(void *buf,char c,int n);
int main(){
	char buf[20] = "hello";
	asm_memset(buf,'A',3);
	printf("%s\n",buf);
	return 0;
}

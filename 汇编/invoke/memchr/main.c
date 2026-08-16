#include <stdio.h>
extern void* asm_memchr(const void* buf,char ch,int len);
int main(){
	char s[] = "hello world";
	char *p = asm_memchr(s,'w',11);
	printf("Found at : %s\n",p);
	return 0;
}

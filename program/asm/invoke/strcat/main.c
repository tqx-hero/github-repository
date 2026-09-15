#include <stdio.h>
extern void asm_strcat(char * dst,char *src);
int main(){
	char buf[20] = "hello,";
	asm_strcat(buf,"world");
	printf("%s\n",buf);
	return 0;
}

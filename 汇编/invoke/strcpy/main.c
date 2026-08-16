#include <stdio.h>
extern void asm_strcpy(char * dst,char * src);
int main(){

	char a[20];
	asm_strcpy(a,"hello");
	printf("%s\n",a);
	return 0;
}

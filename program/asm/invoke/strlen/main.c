#include <stdio.h>
extern int asm_strlen(char * str);
int main(){
	char s[] = "hello";
	printf("len = %d\n",asm_strlen(s));
	return 0;
}

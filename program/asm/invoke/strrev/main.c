#include <stdio.h>
extern void asm_strrev(char *str);
int main(){
	char s[] ="assembly";
	asm_strrev(s);
	printf("%s\n",s);
	return 0;
}

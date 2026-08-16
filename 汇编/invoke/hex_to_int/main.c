#include <stdio.h>
extern int asm_hex2int(char c);
int main(){
	printf("%d\n",asm_hex2int('A'));
	printf("%d\n",asm_hex2int('5'));
	return 0;
}

#include <stdio.h>
extern int asm_not(int x);
int main(){
	printf("%x\n",asm_not(0xFFFFFF00));
	return 0;
}

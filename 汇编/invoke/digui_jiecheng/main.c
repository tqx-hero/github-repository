#include <stdio.h>
extern int asm_fact(int n);
int main(){
	printf("5! = %d\n",asm_fact(5));
	return 0;
}

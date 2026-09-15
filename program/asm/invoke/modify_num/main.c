#include <stdio.h>
extern int asm_double(int * p);
int main(){
	int a=10;
	asm_double(&a);
	printf("%d\n",a);
	return 0;
}

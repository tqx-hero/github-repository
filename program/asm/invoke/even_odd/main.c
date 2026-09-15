#include <stdio.h>
extern int asm_is_odd(int x);
int main(){

	int res= asm_is_odd(10);
	printf("is odd? : %d\n",res);
	return 0;
}

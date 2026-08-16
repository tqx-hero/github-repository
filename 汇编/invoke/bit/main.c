#include <stdio.h>
extern int asm_count_bits(int x);
int main(){
	printf("%d\n",asm_count_bits(10));
	return 0;
}

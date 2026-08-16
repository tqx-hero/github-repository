#include <stdio.h>
extern int asm_mul(int x,int y);
int main(){
	int res = asm_mul(50,20);
	printf("from C : res = %d\n",res);
	return 0;
}

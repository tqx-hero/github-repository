#include <stdio.h>
extern int asm_sub(int x,int y);
int main(){
	int res = asm_sub(50,20);
	printf("res = %d\n",res);
	return 0;	
}

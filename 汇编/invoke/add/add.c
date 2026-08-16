#include <stdio.h>
extern int asm_add(int a,int b);
int main(){
	int a=10,b=20;
	int c= asm_add(a,b);
	printf("from C:%d\n",c);
	return 0;
}

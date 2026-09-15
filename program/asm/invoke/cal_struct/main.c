#include <stdio.h>

typedef struct {
	int x;
	int y;
}Demo;

extern int asm_sum_struct(Demo * s);
int main(){
	Demo s = {10,20};
	printf("%d\n", asm_sum_struct(&s));
	return 0;
}

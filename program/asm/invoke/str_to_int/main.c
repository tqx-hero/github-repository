#include <stdio.h>
extern int asm_atoi(char *str);
int main(){
	int res = asm_atoi("1234");
	printf("num = %d\n",res);
	return 0;
}

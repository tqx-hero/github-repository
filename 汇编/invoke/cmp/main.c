#include <stdio.h>
extern int asm_max(int x,int y);
void print_max(int max){
	printf("max = %d\n",max);
}
int main(){
	int res = asm_max(10,20);
	printf("from C: max = %d\n",res);
	return 0;
}

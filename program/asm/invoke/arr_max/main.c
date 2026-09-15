#include <stdio.h>
extern int asm_array_max(int * p,int len);

void print_max(int m){
	printf("max = %d\n",m);
}

int main(){
	int a[] ={3,1,4,1,5,9};
	int res = asm_array_max(a,6);
	printf("from C : max = %d\n",res);
	return 0;
}

#include <stdio.h>
int add(int a,int b){
	return a+b;
}

int sub(int a,int b){
	return a-b;
}

extern int asm_call_func(int (*func)(int,int),int a,int b);

int main(){
	int r1= asm_call_func(add,10,3);
	printf("add = %d \n",r1);

	int r2= asm_call_func(sub,10,3);
	printf("sub = %d \n",r2);
	return 0;
}

#include <stdio.h>
extern void asm_bubble(int * p ,int len);
int main(){
	int a[] ={5,3,8,1,9};
	asm_bubble(a,5);
	for(int i=0;i<5;i++)
		printf("%d ",a[i]);
	return 0;
}

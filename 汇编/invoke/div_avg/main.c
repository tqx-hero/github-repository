#include <stdio.h>
extern int asm_avg(int arr[],int len);
int main(){
	int a[] = {-10,20,-30,40};
	printf("Avg = %d\n",asm_avg(a,4));
	return 0;
}

#include <stdio.h>
extern int asm_sum(int arr[],int len);
int main(){
	int arr[] ={1,2,3,4,5};
	int res = asm_sum(arr,5);
	printf("sum = %d\n",res);
	return 0;
}

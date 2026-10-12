#include <stdio.h>

void* get_static(){
	static int a =10;
	return &a;
}

int main(){
	int *ap =(int *)get_static();
	(*ap)++;
	printf("a = %d\n",*ap);
	return 0;
}

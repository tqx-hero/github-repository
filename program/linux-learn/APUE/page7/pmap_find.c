#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static int data_i = 100;
int global_i = 1000;
static int bss_static;
int bss_global;
int main(){
	int stack_i;
	int *heap_ptr = malloc(sizeof(int));
	pause();
	return 0;
}

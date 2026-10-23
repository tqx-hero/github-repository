#include <stdlib.h>
#include <stdio.h>

int main(){
	char* ptr = (char*)malloc(1024);
	ptr[1024] =0;
	return 0;
}

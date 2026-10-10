#include <unistd.h>
#include <stdio.h>

int main(){
	printf("hello\n");
	alarm(5);
	printf("exit..\n");
	while(1);
	return 0;
}

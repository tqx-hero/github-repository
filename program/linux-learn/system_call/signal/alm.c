#include <unistd.h>
#include <stdio.h>
int main(){
	printf("hello\n");
	alarm(5);
	printf("exit..\n");
	sleep(10);
	return 0;
}

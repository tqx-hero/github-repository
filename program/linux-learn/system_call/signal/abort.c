#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
//abort()
int main(){
	sleep(1);
	printf("执行abort()之前...");
	abort();
	while(1);
	return 0;
}

#include <unistd.h>
#include <stdio.h>
//重新设置alarm()
int main(){
	printf("hello\n");
	alarm(5);
	printf("exit..\n");
	sleep(2);
	printf("%u\n",alarm(2));
	while(1);
	return 0;
}

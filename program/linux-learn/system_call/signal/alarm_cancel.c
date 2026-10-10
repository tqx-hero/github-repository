#include <unistd.h>
#include <stdio.h>
//取消alarm()
int main(){
	printf("hello\n");
	alarm(2);
	printf("exit..\n");
	alarm(0);
	while(1);
	return 0;
}

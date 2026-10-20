#include <stdlib.h>
#include <stdio.h>
//getenv、setenv
int main(){
	printf("PWD = %s\n",getenv("PWD"));
	printf("myname = %s\n",getenv("myname"));
	putenv("myname=tqx");
	printf("myname = %s\n",getenv("myname"));
	return 0;
}

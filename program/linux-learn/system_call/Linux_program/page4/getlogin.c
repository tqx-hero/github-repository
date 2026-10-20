#include <unistd.h>
#include <stdio.h>
//getuid/geteuid
int main(){
	printf("login name = %s\n",getlogin());
	return 0;
}

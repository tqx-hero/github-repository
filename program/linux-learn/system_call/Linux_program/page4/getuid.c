#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
//getuid/geteuid
int main(){
	
	printf("uid = %u\n",getuid());
	printf("uid = %u\n",geteuid());
	return 0;
}

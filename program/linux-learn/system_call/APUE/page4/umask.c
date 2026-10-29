#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(){
	umask(0);
	if(creat("foo",0666) ==-1)
		perror("create error");
	umask(0066);
	if(creat("bar",0666) == -1)
		perror("create bar error");
	return 0;
}

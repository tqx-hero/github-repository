#include <unistd.h>
#include <stdio.h>

int main(){
	if(chown("./test.txt",getuid(),getgid()) == -1)
		perror("chown file error");
	return 0;
}

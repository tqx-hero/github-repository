#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	if(chmod("./test.txt",0644) ==-1)
		perror("chmod test.txt error");
	return 0;
}

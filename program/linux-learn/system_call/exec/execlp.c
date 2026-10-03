#include <unistd.h>
#include <stdio.h>

int main(){
	if(execlp("myexecl","myexecl",NULL) == -1)
		perror("execlp error");
	return 0;
}

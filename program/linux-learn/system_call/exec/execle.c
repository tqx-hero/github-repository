#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	char path[256];
	sprintf(path,"PATH=%s:%s",getenv("PATH"),getenv("PWD"));
	char* envp[]={path,NULL};
	if(execle("./myecho","myecho",NULL,envp) == -1)
		perror("execle error ");
	return 0;
}

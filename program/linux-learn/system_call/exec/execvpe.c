#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//execvpe()函数
int main(){
	char * argv[] ={"myecho",NULL};
	char path[128];
	sprintf(path,"PATH=%s:%s",getenv("PATH"),getenv("PWD"));
	char * env[] ={path,NULL};
	if(execvpe("./myecho",argv,env) == -1)
		perror("myecho error");
	return 0;
}

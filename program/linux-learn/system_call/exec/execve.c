#include <stdio.h>
#include <unistd.h>
//execve()系统调用
int main(){
	char* argv[] ={"myexec","hello","world",NULL};
	char* env[] = {NULL};
	execve("./myexecve",argv,env);
	perror("execve error");
	return 0;
}

#include <unistd.h>
#include <string.h>
#include <stdio.h>
//execv函数使用
int main(){
	char* env[] = {"ls","-l","-h",NULL};
	if(execv("/bin/ls",env) == -1)
		perror("execv error");
	return 0;
}

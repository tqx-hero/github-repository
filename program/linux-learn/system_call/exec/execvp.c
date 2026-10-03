#include <stdio.h>
#include <unistd.h>
//execvp函数使用
int main(){
	char* env[] = {"ls","-l","-h",NULL};
	execvp("ls",env);
	return 0;
}

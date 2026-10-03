#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
//vfork的使用
int main(){
	pid_t pid;
	int a = 20;
	if((pid = vfork()) == -1){
		perror("");
		exit(-1);
	}else if(pid == 0){
		fprintf(stdout,"这是子进程...\n");
		a+=10;
		sleep(2);
		_exit(0);
	}else {
		printf("这是父进程...\n");
		printf("a = %d\n",a);
	}
	return 0;
}

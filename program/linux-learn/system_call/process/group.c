#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t cur_pid = getpid();
	printf("当前的组id = %d\n",getpgid(cur_pid));
	printf("当前父进程id = %d\n",getppid());
	printf("当前的组id2 = %d\n",getpgid(0));
	return 0;

}

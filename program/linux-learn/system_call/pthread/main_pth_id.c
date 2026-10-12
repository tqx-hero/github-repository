#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t p1 = syscall(SYS_gettid);
	pid_t p2 = getpid();
	printf("主线程ID = %d\n",p1);
	printf("进程ID = %d\n",p2);
}
	


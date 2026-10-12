#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//创建线程，并执行打印任务

void* printf_cnt(void* arg){
	pid_t pid,tid;
	tid = syscall(SYS_gettid);
	pid = getpid();
	while(1){
		sleep(1);
		printf("子线程 id = %d,进程ID = %d\n",tid,pid);
	}
}

int main(){
	pthread_t pt,pt1;
	if((pthread_create(&pt,NULL,printf_cnt,NULL)) != 0){
		fprintf(stderr,"创建线程失败\n");
		exit(-1);
	}
	if((pthread_create(&pt1,NULL,printf_cnt,NULL)) != 0){
		fprintf(stderr,"创建线程失败\n");
		exit(-1);
	}
	pid_t pid = getpid();
	while(1){
		sleep(1);
		printf("主线程 id = %d\n",pid);
	}
	return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//不进行回收的线程，会变成僵尸线程

void* pth_exec(void* arg){
	printf("子线程已经执行，正在退出\n");
	//exit(0); //子线程中不要使用exit(2),该函数会导致进程退出，而不是线程退出，可以使用pthread_exit或return
	pthread_exit(0);
}

int main(){
	pthread_t pt;
	if(pthread_create(&pt,NULL,pth_exec,NULL) != 0){
		fprintf(stderr,"创建线程失败\n");
		exit(-1);
	}
	printf("创建线程成功!\n");
	while(1);
	return 0;
}

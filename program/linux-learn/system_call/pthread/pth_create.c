#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//创建线程，并执行打印任务

void* printf_cnt(void* arg){
	int cnt = (int)(long) arg,i;
	for(i=1;i <= cnt;++i)
		printf("子进程执行第[%d]打印任务...\n",i);
	printf("子进程打印任务完成,正在退出\n");
	pthread_exit(0);
}

int main(){
	pthread_t pt;
	int i =10;
	if((pthread_create(&pt,NULL,printf_cnt,(void*)(long)i)) != 0){
		fprintf(stderr,"创建线程失败\n");
		exit(-1);
	}
	pthread_join(pt,NULL);
	printf("主线程退出..\n");
	return 0;
}

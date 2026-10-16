#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define THREAD_COUNT 10

//使用信号量实现互斥锁的功能
sem_t sm;
long int cur_cnt;
void* th_printer(void* arg){
	pid_t tid = syscall(SYS_gettid);
	long total_cnt = (long) arg;
	while(1){
		sem_wait(&sm);//P操作
		if(cur_cnt >= total_cnt)
			break;
		//次数不到，执行打印
		printf("线程[%d]正在打印第[%ld]份文件...\n",tid,++cur_cnt);
		sem_post(&sm);
		usleep(1000 * 200);
	}
	sem_post(&sm);//退出之前千万不要忘了V操作
	printf("线程[%d]退出.\n",tid);
	pthread_exit(NULL);
}

int main(int argc,char** argv){
	if(argc <2){
		fprintf(stderr,"请输入打印次数\n");
		exit(-1);
	}
	long int cnt = atol(argv[1]);
	if(cnt <= 0){
		fprintf(stderr,"请输入正确的打印次数(>0)!\n");
		exit(-1);
	}
	sem_init(&sm,0,1);//设置信号量初值为1
	//创建线程执行打印任务
	pthread_t threads[THREAD_COUNT];
	int i;
	for(i = 0; i < THREAD_COUNT;++i)
		pthread_create(&threads[i],NULL,th_printer,(void*)cnt);
	for(i = 0; i < THREAD_COUNT; ++i)
		pthread_join(threads[i],NULL);
	sem_destroy(&sm);
	printf("打印任务全部完成，总打印数量:[%ld],实际打印数量:[%ld].\n",cnt,cur_cnt);
	return 0;
}

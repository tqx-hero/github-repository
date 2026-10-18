#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "ArrayDeque.h"		//消息队列
#define THREAD_COUNT 10 	//生产者消费者各5个
#define MSG_MAX_SIZE MAX_SIZE

//定义一个对象结构体
typedef struct Object {
    int num;
} Object;

//生产者消费者模型mutex+cond
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//创建2个条件
//empty:满足缓冲区空时，消费者阻塞在该条件队列
//full:缓冲区满时，生产者阻塞在该条件队列
pthread_cond_t empty = PTHREAD_COND_INITIALIZER,full = PTHREAD_COND_INITIALIZER;
pthread_t threads[THREAD_COUNT];
ArrayDeque* msgque;
int num;
int running = 1;//执行总开关
void init_src(){
	//加载消息队列
	arrayDeque_initQueue(&msgque,0);
}
//生产者
void* provider(void* arg){
	pid_t tid = syscall(SYS_gettid);
	while(running){
		pthread_mutex_lock(&lock);
		//判断队列是否为满,满了的话入full条件队列
		while(running && arrayDeque_isFull(msgque))
			pthread_cond_wait(&full,&lock);
		if(!running)
			break;
		//队列不满就放入消息
		Object obj = {num++};
		arrayDeque_offer(msgque,&obj,sizeof(Object));
		printf("生产线程[%d] 生产了消息: %d\n",tid,obj.num);
		pthread_mutex_unlock(&lock);
		//pthread_cond_broadcast(&empty);
		pthread_cond_signal(&empty);
		usleep(1000 * 100);
	}
	//解锁
	pthread_mutex_unlock(&lock);
	printf("生产线程[%d]已退出\n",tid);
	pthread_exit(NULL);
}
//消费者
void* consumer(void* arg){
	pid_t tid = syscall(SYS_gettid);
	while(running){
		pthread_mutex_lock(&lock);
		//队列空，消费者线程阻塞到empty条件队列
		while(running && arrayDeque_isEmpty(msgque))
			pthread_cond_wait(&empty,&lock);
		if(!running)
			break;
		Object obj;
		//消费消息
		arrayDeque_poll(msgque,&obj,sizeof(Object));
		printf("消费者线程[%d]消费了消息: %d\n",tid,obj.num);
		pthread_mutex_unlock(&lock);
		//pthread_cond_broadcast(&full);
		pthread_cond_signal(&full);
		usleep(1000 * 100);
	}
	pthread_mutex_unlock(&lock);
	printf("消费线程[%d]已退出\n",tid);
	pthread_exit(NULL);
}

void sigint_handler(int signum){
	running = 0;
	printf("已进入终止执行流程，开始回收资源\n");
	return;
}
//回收资源
void destory_src(){
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&full);
	//回收消息队列
	arrayDeque_destory(msgque);
}

int main(){
	//注册信号SIGINT处理，回收资源(虽然该信号会终止进程自动回收所有资源，没什么实际用途,这里是以该信号为例作为练习)
	struct sigaction sigact;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_handler = sigint_handler;
	if(sigaction(SIGINT,&sigact,NULL)){
		perror("sigaction SIGINT error");
		exit(-1);
	}
	init_src();
	//创建线程
	int i;
	for(i = 0;i < THREAD_COUNT;++i){
		if(i % 2 ==0)
			pthread_create(&threads[i],NULL,provider,NULL);
		else 
			pthread_create(&threads[i],NULL,consumer,NULL);
		//pthread_detach(threads[i]);
	}
	while(running)
		sleep(10);
	//开始回收资源
	int j;
	//唤醒所有阻塞的线程
	pthread_cond_broadcast(&empty);
	pthread_cond_broadcast(&full);
	for(j = 0;j < i;++j)
		pthread_join(threads[j],NULL);
	//线程全部退出后，回收条件变量、互斥锁、消息队列
	destory_src();
	printf("所有资源已回收，程序退出.\n");
	return 0;
}

#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayDeque.h"
#define MQ_SIZE ARRAYDEQUE_MAX_SIZE
#define CON_THREAD_COUNT 10
#define PRO_THREAD_COUNT 10
//pro_sem:生产者信号量,初值为队列总容量，表示一次性(原子操作)能放入的总数量
//con_sem:消费者信号量，初值为0，需要等生产者V操作后会的信号量
//mutex: 对临界资源消息队列进行互斥量定义，给它加锁
sem_t pro_sem,con_sem,mutex;
pthread_t pro_th[PRO_THREAD_COUNT],con_th[CON_THREAD_COUNT];
long cur_num;
ArrayDeque queue;
typedef struct {
	long num;
	pid_t tid;
}msg_t;

void* pro_handler(void* arg){
	pid_t tid = syscall(SYS_gettid);
	msg_t* msg = (msg_t*)malloc(sizeof(msg_t));
	if(!msg){
		perror("malloc error");
		exit(-1);
	}
	while(1){
		sem_wait(&pro_sem);//P操作
		msg->num = ++cur_num;
		msg->tid = tid;
		sem_wait(&mutex);
		arrayDeque_offer(&queue,msg,sizeof(msg_t));
		sem_post(&mutex);
		fprintf(stdout,"线程[%d]放入了第[%ld]条消息.\n",tid,cur_num);
		sem_post(&con_sem);//唤醒消费者
		//usleep(1000 * 200);
	}
	free(msg);
	pthread_exit(NULL);
}

void* con_handler(void* arg){
	pid_t tid = syscall(SYS_gettid);
	msg_t* msg = (msg_t*)malloc(sizeof(msg_t));
	if(!msg){
		perror("malloc error");
		exit(-1);
	}
	while(1){
		sem_wait(&con_sem);
		//消费消息
		sem_wait(&mutex);
		arrayDeque_poll(&queue,msg,sizeof(msg_t));
		sem_post(&mutex);
		fprintf(stdout,"消费线程[%d]: [%d] > [%ld].\n",tid,msg->tid,msg->num);
		sem_post(&pro_sem);
		//usleep(1000 * 200);
	}
	free(msg);//释放内存
	return NULL;
}

int main(){
	//加载生产者的信号量，初值等于消息队列的size
	//消费者信号量，初值等于0，刚开始没有消息，
	//需要阻塞等待生产者生产消息给con_sem+1
	arrayDeque_initQueue(&queue);
	sem_init(&pro_sem,0,MQ_SIZE);
	sem_init(&con_sem,0,0);
	sem_init(&mutex,0,1);
	//创建生产者、消费者线程
	int i,max = PRO_THREAD_COUNT > CON_THREAD_COUNT ? PRO_THREAD_COUNT : CON_THREAD_COUNT;
	for(i=0;i<max;++i){
		if(i < PRO_THREAD_COUNT)
			pthread_create(&pro_th[i],NULL,pro_handler,NULL);
		if(i < CON_THREAD_COUNT)
			pthread_create(&con_th[i],NULL,con_handler,NULL);
	}
	
	for(i=0;i<max;++i){
		if(i < PRO_THREAD_COUNT)
			pthread_join(pro_th[i],NULL);
		if(i < CON_THREAD_COUNT)
			pthread_join(con_th[i],NULL);
	}
	sem_destroy(&pro_sem);
	sem_destroy(&con_sem);
	sem_destroy(&mutex);
	arrayDeque_destory(&queue);
	return 0;
}

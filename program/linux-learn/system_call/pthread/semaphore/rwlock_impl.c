#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RD_THREAD_COUNT 10
#define WR_THREAD_COUNT 2
//实现读者写者问题,设定2个写线程，10个读线程
pthread_t rd_threads[RD_THREAD_COUNT],wr_threads[WR_THREAD_COUNT];
//设置打印数据num
//当前读线程的个数rd_cnt,当值=0，释放锁
long num,rd_cnt;

//设置信号量mutex代替锁，cnt_sem为保护临界资源rd_cnt的互斥锁
sem_t mutex,cnt_sem;
char msg_buf[128]="hello world!";

void* read_handler(void* arg){
	pid_t tid = syscall(SYS_gettid);
	while(1){
		//给rd_cnt加锁，修改它的值
		sem_wait(&cnt_sem);
		if(!rd_cnt++)	//当rd_cnt为0，还没有读线程，信号量P,如果不为0，代表已经存在读线程，不执行P操作
			sem_wait(&mutex);
		sem_post(&cnt_sem);
		printf("线程[%d]读取的消息: %s\n",tid,msg_buf);
		//修改读线程-1，还需要信号量P
		sem_wait(&cnt_sem);
		if(!--rd_cnt)//如果退出后没有读线程，信号量V
			sem_post(&mutex);
		sem_post(&cnt_sem);
		usleep(1000 * 200);	
	}
}

void* write_handler(void* arg){
	pid_t tid = syscall(SYS_gettid);
	while(1){
		sem_wait(&mutex);//执行信号量P操作		
		sprintf(msg_buf,"[%d] > [%ld]",tid,++num);
		printf("写进程[%d]写入数据...\n",tid);
		sem_post(&mutex);
		usleep(1000 * 200);	
	}

}

int main(){
	//初始化信号量,设定1个读信号量，1个写信号量
	sem_init(&cnt_sem,0,1);
	sem_init(&mutex,0,1);
	int i,max = RD_THREAD_COUNT > WR_THREAD_COUNT ? RD_THREAD_COUNT : WR_THREAD_COUNT;
	for(i=0;i < max;++i){
		if(i < RD_THREAD_COUNT)
			pthread_create(&rd_threads[i],NULL,read_handler,NULL);
		if(i < WR_THREAD_COUNT)
			pthread_create(&wr_threads[i],NULL,write_handler,NULL);
	}
	//阻塞等待
	for(i=0;i<max;++i){
		if(i < RD_THREAD_COUNT)
			pthread_join(rd_threads[i],NULL);
		if(i < WR_THREAD_COUNT)
			pthread_join(wr_threads[i],NULL);
	}
	//回收信号量
	sem_destroy(&mutex);
	sem_destroy(&cnt_sem);
	return 0;
}


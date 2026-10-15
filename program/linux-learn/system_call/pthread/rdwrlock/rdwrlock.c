#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RD_THREAD_COUNT 10
#define WR_THREAD_COUNT 2
//读写锁的使用,创建2个写线程，10个读线程
char message_buf[512]="hello world!";
char wr_buf[512];
//初始化读写锁
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
//写线程
void* write_handler(void* arg){
	pid_t tid = syscall(SYS_gettid);
	while(1){
		pthread_rwlock_wrlock(&rwlock);//添加写锁
		sprintf(message_buf,"From[%d] > 你好朋友!!",tid);
		printf("线程[%d],写入缓冲区消息:%s\n",tid,message_buf);
		sleep(1);
		pthread_rwlock_unlock(&rwlock);		
	}
	return NULL;
}
//读线程
void* read_handler(void* arg){
	pid_t tid = syscall(SYS_gettid);
	while(1){
		pthread_rwlock_rdlock(&rwlock);//尝试加读锁
		printf("线程[%d]读取缓冲区消息：%s\n",tid,message_buf);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
}

int main(){
	pthread_t rth[RD_THREAD_COUNT],wth[WR_THREAD_COUNT];
	int i;
	for(i=0;i<WR_THREAD_COUNT;++i){
		pthread_create(&wth[i],NULL,write_handler,NULL);
		pthread_detach(wth[i]);
	}
	for(i=0;i<RD_THREAD_COUNT;++i){
		pthread_create(&rth[i],NULL,read_handler,NULL);
		pthread_detach(rth[i]);
	}
	while(1)
		sleep(10);
	pthread_rwlock_destroy(&rwlock);
	return 0;
}

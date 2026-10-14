#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PRINT_MAX_COUNT 1000
//互斥锁mutex的使用

typedef struct {
	pid_t tid;
	char* wordp;
}print_msg_t;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//创建2个子线程，竞争同一把锁，获取锁后可以使用打印机printer(),要求所有线程一共能打印PRINT_MAX_COUNT次
int count;
void printer(void* arg){
	print_msg_t* mptp = (print_msg_t*) arg;
	char* word = mptp->wordp;
	while(*word){
		putchar(*word);
		word++;
	}
	printf("\n");
	printf("线程: %d 打印完成，正在退出\n",mptp->tid);
}

void* th_callback(void* arg){
	char* word = (char*) arg;
	int ret;
	print_msg_t pmt;
	pmt.tid = syscall(SYS_gettid);
	pmt.wordp = (char*)arg;
	while(1){
		if(ret = pthread_mutex_lock(&lock)){
			//加锁出现错误
			printf("加锁出现错误，错误码 = %d\n",ret);
			continue;
		}
		//先判断次数是否已经超过10次
		if(count >= PRINT_MAX_COUNT){
			printf("%d次打印已完成，子线程退出...\n",PRINT_MAX_COUNT);
			pthread_mutex_unlock(&lock);
			break;
		}
		printer(&pmt);
		count++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(){
	pthread_t tid[2];
	char * word[] = {"hello world","你好朋友！"};
	int i;
	for(i = 0;i < 2;++i)
		pthread_create(&tid[i],NULL,th_callback,word[i]);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}

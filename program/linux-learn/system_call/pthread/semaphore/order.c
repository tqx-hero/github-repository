#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
//信号量实现2个线程交替执行
sem_t sem1,sem2;
long cur_cnt;
typedef struct {
	long total_count;
}pth_msg_t;

void* t1_exec(void* arg){
	pth_msg_t* msgp = (pth_msg_t*)arg;
	long total_count = msgp->total_count;
	pid_t tid = syscall(SYS_gettid);
	while(1){
		sem_wait(&sem1);
		if(cur_cnt >= total_count){
			sem_post(&sem2);
			break;
		}
		++cur_cnt;
		fprintf(stdout,"线程[%d]执行第[%ld]次\n",tid,cur_cnt);
		sem_post(&sem2);
		usleep(1000 * 100);
	}
	pthread_exit(NULL);
}

void* t2_exec(void* arg){
	pth_msg_t* msgp = (pth_msg_t*)arg;
	long total_count = msgp->total_count;
	pid_t tid = syscall(SYS_gettid);
	while(1){
		sem_wait(&sem2);
		if(cur_cnt >= total_count){
			sem_post(&sem1);
			break;
		}
		++cur_cnt;
		fprintf(stdout,"线程[%d]执行第[%ld]次\n",tid,cur_cnt);
		sem_post(&sem1);
		usleep(1000 * 100);
	}
	pthread_exit(NULL);
}

void* Malloc(size_t size){
	void* ret;
	if(!(ret = malloc(size))){
		perror("malloc error");
		exit(-1);
	}
	return ret;
}

int main(int argc,char** argv){
	if(argc <2){
		fprintf(stderr,"请输入要执行的总次数\n");
		exit(-1);
	}
	long total_cnt = atol(argv[1]);
	if(total_cnt < 1){
		fprintf(stderr,"输入的执行总次数要大于1\n");
		exit(-1);
	}
	pth_msg_t* pmsg = NULL;
	pthread_t t1,t2;//创建2个线程
	pmsg = (pth_msg_t*)Malloc(sizeof(pth_msg_t));
	pmsg->total_count = total_cnt;
	//谁先开始谁信号量为1
	sem_init(&sem1,0,1);
	sem_init(&sem2,0,0);
	pthread_create(&t1,NULL,t1_exec,pmsg);
	pthread_create(&t2,NULL,t2_exec,pmsg);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	fprintf(stdout,"任务结束!总次数:[%ld],实际次数:[%ld].\n",total_cnt,cur_cnt);
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	free(pmsg);
	return 0;
}

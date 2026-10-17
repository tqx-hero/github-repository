#include <sys/syscall.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PRINT_COUNT 1000
#define THREAD_MAX_COUNT 5
//使用System V的信号量实现互斥锁功能
//这里测试semop执行PV进行加减>1是否正常运行

union semun {
    int              val;    /* SETVAL 使用的值 */
    struct semid_ds *buf;    /* IPC_STAT、IPC_SET 使用的缓冲区 */
    unsigned short  *array;  /* GETALL、SETALL 使用的数组 */
    struct seminfo  *__buf;  /* IPC_INFO 使用的缓冲区 */
    void *__pad;            /* (Linux 特有) */
};

//定义临界资源
typedef struct {
	int sem_id;
	int cur_cnt;
}shared_src_t;

void* th_callback(void* arg){
	shared_src_t* sst = (shared_src_t*) arg;
	pid_t tid = syscall(SYS_gettid);
	const int sem_id = sst->sem_id;
	//设置操作信号量的结构体
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = -2;
	sb.sem_flg = 0 | SEM_UNDO;
	while(1){
		//获取互斥锁
		semop(sem_id,&sb,1);
		sb.sem_op = 2;
		//查看打印次数是否已经到要求次数
		if(sst->cur_cnt >= PRINT_COUNT){
			//次数已到，退出线程
			semop(sem_id,&sb,1);
			break;
		}
		//打印
		++sst->cur_cnt;
		fprintf(stdout,"线程[%d] 已打印第[%d]份文件.\n",tid,sst->cur_cnt);
		semop(sem_id,&sb,1);
	}
	fprintf(stdout,"子线程[%d]退出.\n",tid);
	pthread_exit(NULL);
}

int main(){
	key_t kt;
	int sem_id;
	int i;
	pthread_t threads[THREAD_MAX_COUNT];
	shared_src_t* sst =NULL;
	union semun sm;
	if((kt = ftok("./",1)) == -1){
		perror("ftok error");
		exit(-1);
	}
	//创建、获取信号量ID,这里创建了一个信号量
	if((sem_id = semget(kt,1,IPC_CREAT | 0666)) == -1){
		perror("semget error");
		exit(-1);
	}
	sst = (shared_src_t*)malloc(sizeof(shared_src_t));
	if(!sst){
		perror("malloc error");
		exit(-1);
	}
	sst->sem_id = sem_id;
	sst->cur_cnt = 0;
	//设置信号量的初值为2，每次PV都是加减2
	sm.val = 2;
	if(semctl(sem_id,0,SETVAL,sm)){
		perror("semctl SETVAL error");
		exit(-1);
	}
	//创建线程执行任务
	for(i=0;i<THREAD_MAX_COUNT;++i)
		pthread_create(&threads[i],NULL,th_callback,sst);
	
	//阻塞等待线程退出
	for(i=0;i<THREAD_MAX_COUNT;++i)
		pthread_join(threads[i],NULL);
	fprintf(stdout,"任务结束!要求打印次数:[%d],实际打印次数:[%d].\n",PRINT_COUNT,sst->cur_cnt);
	//回收资源
	free(sst);
	//删除信号量
	if(semctl(sem_id,0,IPC_RMID,NULL)){
		perror("semctl IPC_RMID error");
		exit(-1);
	}
	return 0;
}

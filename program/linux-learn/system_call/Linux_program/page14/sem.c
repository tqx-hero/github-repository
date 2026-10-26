#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#define PRINT_MAX_CNT 1000
#define EXIT(__msg) perror(__msg); \
			exit(EXIT_FAILURE)
#define PRINT_LOOP while(1){	\
			sem_p(semid,-1);	\
			if(((shared_t*)ptr)->num >= PRINT_MAX_CNT){ \
				sem_v(semid,1);	\
				break;		\
			}			\
			print_num(ptr);		\
			sem_v(semid,1);		\
		   }				\
		if(shmdt(ptr)){			\
			EXIT("卸载共享内存失败");\
		}
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short  *array; 
	struct seminfo  *__buf; 
};
static int set_semval(int,int);
static int sem_p(int semid,int num);
static int sem_destory(int);
static int sem_v(int semid,int num);

typedef struct {
	int num;
}shared_t;
//System V  sem*()用法
void print_num(void* ptr){
	printf("进程[%d]正在进行第[%d]次打印\n",getpid(),++((shared_t*)ptr)->num);
}
int main(){
	key_t kt;
	int shmid,semid;
	void* ptr;
	kt = ftok("/name",1);
	semid = semget(kt,1,IPC_CREAT | 0666);
	if(semid == -1){
		EXIT("get sem error");
	}
	//设置初始值
	set_semval(semid,1);
	//进程间通信必须借助那几个手段，这里以共享内存为例
	if((shmid = shmget(kt,1024,IPC_CREAT | 0666)) == -1){
		EXIT("开启共享内存失败");
	}
	if((ptr = shmat(shmid,NULL,0)) == (void*)-1){
		EXIT("挂载共享内存失败");
	}
	//设置共享结构体到共享内存
	((shared_t*) ptr)->num = 0;
	//创建进程
	if(!fork()){
		PRINT_LOOP
		fprintf(stdout,"子进程[%d] 正在退出\n",getpid());
		exit(EXIT_SUCCESS);
	}
	//父进程同时进行打印
	PRINT_LOOP
	pid_t pid;
	if((pid = waitpid(-1,NULL,0)) > 0)
		fprintf(stdout,"子进程已退出!\n");
	//销毁信号量
	sem_destory(semid);
	//销毁共享内存
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}

static int sem_destory(int semid){
	if(semctl(semid,0,IPC_RMID)){
		EXIT("rm sem error");
	}
	return 0;
}

static int sem_v(int semid,int num){
	if(num <= 0){
		fprintf(stderr,"v操作值必须大于0!\n");
		exit(EXIT_FAILURE);
	}
	return sem_p(semid,num);
}

static int sem_p(int semid,int num){
	struct sembuf sb;
	sb.sem_num =0;
	sb.sem_op = num;
	sb.sem_flg = SEM_UNDO;
	if(semop(semid,&sb,1)){
		EXIT("sem p error");
	}
	return 0;
}

static int set_semval(int semid,int val){
	union semun sm;
	sm.val = val;
	if(semctl(semid,0,SETVAL,sm)){
		EXIT("sem setval error");
	}
	return 0;
}


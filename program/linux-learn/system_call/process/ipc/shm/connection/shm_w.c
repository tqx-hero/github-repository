#include "shm_t.h"
int main(){
	key_t kt;
	int shm_id;
	char * shmp;
	//创建key
	if((kt = ftok("./",1)) == -1){
		perror("ftok error");
		exit(-1);
	}
	//通过key创建、打开共享内存
	if((shm_id =  shmget(kt,1024,IPC_CREAT | 0666)) == -1){
		perror("shmget error");
		exit(-1);
	}
	printf("已创建共享内存，id = %d\n",shm_id);
	//shmat()绑定当前进程的逻辑地址
	shmp = shmat(shm_id,NULL,0);
	if(shmp == (void*)-1){
		perror("shmat error");
		exit(-1);
	}
	printf("绑定当前进程成功，逻辑地址 = %p\n",shmp);
	//写入数据
	shm_msg_t *shg = (shm_msg_t*) shmp;
	shg->pid = getpid();
	strcpy(shg->msg,"大家好才是真的好!");
	if(shmdt(shmp) == -1)
		perror("shmdt error");
	return 0;
}

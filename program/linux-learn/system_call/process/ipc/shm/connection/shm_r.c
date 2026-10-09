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
	//shmat()绑定当前进程的逻辑地址
	shmp = shmat(shm_id,NULL,0);
	if(shmp == (void*)-1){
		perror("shmat error");
		exit(-1);
	}
	printf("绑定当前进程成功，逻辑地址 = %p\n",shmp);
	//读取数据
	shm_msg_t *shg = (shm_msg_t*) shmp;
	printf("共享内存中的结构体信息： pid = %d , msg = %s\n",shg->pid,shg->msg);
	if(shmdt(shmp) == -1)
		perror("shmdt error");
	//给共享内存打上删除标记，当无进程使用该内存段，删除它
	if(shmctl(shm_id,IPC_RMID,NULL) == -1)
		perror("shmctl rm error");
	return 0;
}

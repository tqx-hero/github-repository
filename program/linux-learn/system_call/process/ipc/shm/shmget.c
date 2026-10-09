#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//shmget()
int main(){
	key_t kt;
	int shm_id;
	//创建key
	if((kt = ftok("./",1)) == -1){
		perror("ftok error");
		exit(-1);
	}
	//通过key创建、打开共享内存
	//if((shm_id =  shmget(kt,sysconf(_SC_PAGE_SIZE),IPC_CREAT | 0666)) == -1){
	if((shm_id =  shmget(kt,1024,IPC_CREAT | 0666)) == -1){
		perror("shmget error");
		exit(-1);
	}
	printf("已创建共享内存，id = %d\n",shm_id);
	return 0;
}

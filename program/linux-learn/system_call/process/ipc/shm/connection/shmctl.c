#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//使用shmctl()控制共享内存
int main(){
	struct shmid_ds shd;
	shd.shm_perm.mode = 0644;
	shd.shm_segsz = 64;
	if(shmctl(32780,IPC_SET,&shd) ==-1)
		perror("shmctl error");
	shmctl(32780,IPC_RMID,NULL);
	return 0;
}

#include "shared.h"

//子进程执行的新程序,即开启线程执行打印任务

void* th_handler(void* arg){
	pid_t tid = syscall(SYS_gettid);
	shared_info_t * shp = (shared_info_t*) arg;
	while(1){
		//加锁
		pthread_mutex_lock(&shp->lock);
		//判断当前打印次数是否已经超过最大次数
		if(shp->cur_cnt >= shp->total_cnt){
			printf("打印已完成，线程[%d] 退出\n",tid);
			break;
		}
		//打印输出的内容,简化起见输出当前的次数
		printf("线程[%d]执行第[%d]次打印\n",tid,++shp->cur_cnt);
		pthread_mutex_unlock(&shp->lock);
	}
	pthread_mutex_unlock(&shp->lock);
	return NULL;
}

int main(int argc,char** argv){
	if(argc < 2){
		fprintf(stderr,"参数不足!\n");
		goto fail_ret;
	}
	pid_t pid = getpid();
	//从参数拿到共享内存ID
	int shm_id = atoi(argv[1]);
	printf("进程：%d 开始执行打印任务程序,shm_id = %d\n",getpid(),shm_id);
	//挂载共享内存到进程
	void * shm_ptr = shmat(shm_id,NULL,0);
	if(shm_ptr == SHMAT_FAIL){
		perror("shmat error");
		goto fail_ret;
	}
	//创建子线程执行打印任务
	pthread_t pth;
	pthread_create(&pth,NULL,th_handler,shm_ptr); //将共享内存的地址以传参形式传给子线程
	pthread_join(pth,NULL);
	printf("全部打印完成，子进程[%d]正在退出\n",pid);
	//卸载共享内存映射关系
	if(shmdt(shm_ptr)){
		perror("子进程 shmdt error");
		goto fail_ret;
	}
	return 0;

fail_ret:
	printf("子进程[%d]正在退出\n",pid);
	exit(-1);
}

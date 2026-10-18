#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#define SHM_NAME "/name"
#define SHM_BUF_SIZE 1024
#define SHM_TRUNCATE_SIZE 1024

typedef struct {
	sem_t full,empty;
} sem_info_t;

typedef struct {
	pid_t pid;
	int num;
	char buf[SHM_BUF_SIZE];
} shminfo_t;

//使用POSIX标准的共享内存
//父子进程进行简单的同步
int main(){
	pid_t pid;
	int fd;
	char* start_ptr;
	shminfo_t* shmp;
	off_t fd_size = SHM_TRUNCATE_SIZE;
//	pthread_mutex_t *mutex;
	sem_info_t * semp;
	fd = shm_open(SHM_NAME,O_CREAT | O_RDWR | O_EXCL,0666);
	if(fd == -1){
		//如果内存段已存在，直接打开
		if(errno == EEXIST){
			fd = shm_open(SHM_NAME,O_RDWR,0666);
			//获取内存段的大小
			struct stat st;
			fstat(fd,&st);
			fd_size = st.st_size;
			printf("内存段已存在，大小 ：%ld\n",fd_size);
		}
		else{
			perror("open shared mem error");
			exit(-1);
		}
	}else{ //内存段不存在，创建成功，设置内存段的大小
		if(ftruncate(fd,SHM_TRUNCATE_SIZE)){
			perror("truncate shm error");
			exit(-1);
		}
	}
	start_ptr = (char*) mmap(NULL,fd_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	shm_unlink(SHM_NAME); //fork()的子进程因为有继承关系，所以可直接先把名称去掉
	//在共享内存设置互斥对象，用于后续父子进程同步,设定共享内存起始偏移0位置为互斥对象的地址
	//mutex = (pthread_mutex_t*)start_ptr;
	//pthread_mutex_init(mutex,NULL);
	//*mutex = PTHREAD_MUTEX_INITIALIZER;
	//使用信号量
	semp = (sem_info_t*) start_ptr;
	sem_init(&semp-> full,1,0);
	sem_init(&semp-> empty,1,1);
	//给出可用内存的起始地址,即从起始偏移+ 互斥对象大小
	shmp =(shminfo_t*)(start_ptr + sizeof(sem_info_t));
	if(!(pid = fork())){//子进程
		int num=0;
		shmp->pid = getpid();
		while(1){
			//pthread_mutex_lock(mutex);
			sem_wait(&semp->empty);
			shmp->num = num;
			sprintf(shmp->buf,"这是第[%d]条消息.\n",num);
			++num;
			//pthread_mutex_unlock(mutex);
			sem_post(&semp->full);
		}
		if(munmap(start_ptr,fd_size)){
			perror("子进程解除内存映射mmap失败:");
			exit(-1);
		}
		exit(0);
	}else{//父进程
		while(1){
//			pthread_mutex_lock(mutex);
			sem_wait(&semp->full);
			printf("共享内存内容：%d > [%d] %s\n",shmp->pid,shmp->num,shmp->buf);
//			pthread_mutex_unlock(mutex);
			sem_post(&semp->empty);
		}
		//在解除内存映射前销毁信号量
		sem_destroy(&semp->full);
		sem_destroy(&semp->empty);
		munmap(start_ptr,fd_size);
	}
//	pthread_mutex_destroy(mutex);
	return 0;
}

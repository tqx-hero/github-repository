#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define SHM_NAME "/name"
#define SHM_BUF_SIZE 1024
#define SHM_TRUNCATE_SIZE 1024

typedef struct {
	pid_t pid;
	char buf[SHM_BUF_SIZE];
} shminfo_t;

//使用POSIX标准的共享内存
int main(){
	pid_t pid;
	int fd;
	shminfo_t* shmp;
	off_t fd_size = SHM_TRUNCATE_SIZE;
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
	shmp = (shminfo_t*) mmap(NULL,fd_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	shm_unlink(SHM_NAME); //fork()的子进程因为有继承关系，所以可直接先把名称去掉
	if(!(pid = fork())){//子进程
		shmp->pid = getpid();
		strcpy(shmp->buf,"你好我好大家好....");
		if(munmap(shmp,fd_size)){
			perror("子进程解除内存映射mmap失败:");
			exit(-1);
		}
		exit(0);
	}else{//父进程
		sleep(1);
		printf("共享内存内容：%d > %s\n",shmp->pid,shmp->buf);
		munmap(shmp,fd_size);
	}
	return 0;
}

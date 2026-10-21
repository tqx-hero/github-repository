#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_NAME "./segment.lock"
#define FAIL_EXIT(__MSG,__FD) perror(__MSG); \
                        if(__FD >= 0) \
                                close(__FD); \
                        exit(EXIT_FAILURE)
//输出锁结构体信息
void print_flock(struct flock*);
//获取锁的封装函数
void getflock(int ,struct flock*);
//测试区间锁
int main(){
	int fd;
	if((fd = open(FILE_NAME,O_RDWR)) == -1){
		FAIL_EXIT("open file error",-1);
	}
	//定义锁区间，测试锁
	struct flock test_region;
	//测试读锁
	test_region.l_type = F_RDLCK;
	test_region.l_whence = SEEK_SET;
	test_region.l_start = 0;
	test_region.l_len = 100;
	test_region.l_pid = -2;
	printf("测试0~127字节区间的读锁:\n");
	getflock(fd,&test_region);
	//测试写锁
	test_region.l_type = F_WRLCK;
	printf("测试0~127字节区间的写锁:\n");
	getflock(fd,&test_region);
	//测试256~655区间的读锁
	test_region.l_type = F_RDLCK;
	test_region.l_whence =SEEK_SET;
	test_region.l_start = 256;
	test_region.l_len = 400;
	test_region.l_pid = -2;
	printf("测试256~655区间的读锁:\n");
	getflock(fd,&test_region);

	//尝试在存在读锁的区间再次加读锁
	test_region.l_type = F_RDLCK;
	test_region.l_whence =SEEK_SET;
	test_region.l_start =0;
	test_region.l_len = 100;
	printf("尝试在0~99区间加读锁:\n");
	if(fcntl(fd,F_SETLKW,&test_region)){
		FAIL_EXIT("set rdlck error",fd);
	}
	printf("添加读锁成功\n");
	char buf[101]={0};
	if(read(fd,buf,100) < 0){
		FAIL_EXIT("read info error",fd);
	}
	printf("读到的内容 = %s\n",buf);
	test_region.l_type =F_UNLCK;
	if(fcntl(fd,F_SETLKW,&test_region)){
		FAIL_EXIT("unlock rdlck error",fd);
	}
	//测试是否在有写锁时可写
	printf("测试有写锁时在不测试锁的状态下能否写入\n");
	strcpy(buf,"hello");
	lseek(fd,256,SEEK_SET);
	if(write(fd,buf,strlen(buf)+1) <=0){
		FAIL_EXIT("不能写入!",fd);
	}

	/*
	test_region.l_type =F_UNLCK;
	if(fcntl(fd,F_SETLKW,&test_region)){
		FAIL_EXIT("unlock error",fd);
	}
	
	*/
	close(fd);
	return 0;
}

void getflock(int fd,struct flock* test_region){
	if(fcntl(fd,F_GETLK,test_region)){
		FAIL_EXIT("getlock error",fd);
	}
	print_flock(test_region);
}

void print_flock(struct flock* info){
	printf("l_type = %d\n",info->l_type);
	printf("l_whence = %d\n",info->l_whence);
	printf("l_start = %ld\n",info->l_start);
	printf("l_len = %ld\n",info->l_len);
	printf("l_pid = %d\n",info->l_pid);
}

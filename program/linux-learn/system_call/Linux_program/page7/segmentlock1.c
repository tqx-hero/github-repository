#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "./segment.lock"
#define FAIL_EXIT(__MSG,__FD) perror(__MSG); \
			if(__FD >= 0) \
				close(__FD); \
			exit(EXIT_FAILURE)
//使用fcntl()设置分段锁
int main(){
	int fd;
	if((fd = open(FILE_NAME,O_RDWR | O_CREAT | O_APPEND,0666))== -1){
		FAIL_EXIT("open file error",-1);
	}
	//设置文件大小
	//ftruncate(fd,1024);
	//设置分段锁
	struct flock region1,region2;
	//第一个区间0~127，128个字节设置读锁，即共享锁
	region1.l_type = F_RDLCK;
	region1.l_whence = SEEK_SET;
	region1.l_start = 0;
	region1.l_len = 128;
	//第二个区间 256~511,256个字节设置读锁
	region2.l_type = F_WRLCK;
	region2.l_whence = SEEK_SET;
	region2.l_start = 256;
	region2.l_len = 256;

	if(fcntl(fd,F_SETLKW,&region1)){
		FAIL_EXIT("lock region2 error",fd);
	}
	if(fcntl(fd,F_SETLKW,&region2)){
		FAIL_EXIT("lock region2 error",fd);
	}
	printf("分段锁加锁成功!\n");
	sleep(10);
	printf("10s时间到，释放写锁\n");
	region2.l_type = F_UNLCK;
	if(fcntl(fd,F_SETLKW,&region2)){
		FAIL_EXIT("unlock region2 error",fd);
	}
	printf("释放写锁成功.\n");
	sleep(60);
	printf("60s时间到，进程正在退出.\n");
	close(fd);
	//unlink(FILE_NAME);
	return 0;
}

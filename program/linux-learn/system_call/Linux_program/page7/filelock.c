#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define FILE_LOCK_NAME "./LOCK"
//使用 O_CREAT | O_EXCL 的原子性操作特性创建文件锁
int main(){
	int fd ;
	pid_t pid = getpid();
	while(1){
		//如果fd获取失败，说明已经有其他进程使用该锁
		if((fd = open(FILE_LOCK_NAME,O_RDONLY | O_CREAT | O_EXCL,0444)) == -1){
			//fprintf(stderr,"[%d]: 文件锁已被占用!\n",pid);
			//sleep(3);
			continue;
		}
		//fd获取成功，加锁成功，下面是执行临界区代码
		fprintf(stdout,"文件加锁成功,进程：[%d]正在执行临界区代码..\n",pid);
		sleep(1);
		close(fd);
		unlink(FILE_LOCK_NAME);//一定要注意删除文件，相当于解锁
	}
	return 0;
}

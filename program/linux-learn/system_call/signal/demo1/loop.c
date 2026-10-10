#include <stdio.h>
#include <unistd.h>
//测试函数，输出进程ID，之后循环，等待其他进程发送SIGINT信号
int main(){
	printf("当前进程id = %d\n",getpid());
	while(1){
		printf("循环中...\n");
		sleep(1);
	}
	printf("程序被中断\n");
	return 0;
}

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//getitimer(2)
int main(){
	//获取定时器
	struct itimerval itl;
	if(getitimer(ITIMER_REAL,&itl) == -1){
		perror("getitmer error");
		exit(-1);
	}
	//没有定时器，当前返回的结构体中全部为0
	printf("获取定时器成功\n");
	return 0;
}

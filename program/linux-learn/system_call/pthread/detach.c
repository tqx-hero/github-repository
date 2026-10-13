#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//设置detach属性

void * th_callback(void* arg){
	sleep(3);
	printf("线程退出\n");
}

int main(){
	pthread_t pdt;
	pthread_create(&pdt,NULL,th_callback,NULL);
	pthread_detach(pdt);
	while(1);
	return 0;
}

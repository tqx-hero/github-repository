#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//get/set attr

void* callback(void* arg){
	printf("子线程正在执行，退出中\n");
	sleep(5);
	printf("子线程退出\n");
	return NULL;
}

int main(){
	pthread_t tid;	
	pthread_attr_t pattr;
	//初始化attr属性
	pthread_attr_init(&pattr);
	pthread_attr_setdetachstate(&pattr,PTHREAD_CREATE_DETACHED);
	pthread_create(&tid,&pattr,callback,(void*)&pattr);
	pthread_attr_destroy(&pattr);
	while(1);
	return 0;
}

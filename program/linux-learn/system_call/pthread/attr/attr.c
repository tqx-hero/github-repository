#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//get/set attr

void* callback(void* arg){


}

int main(){
	pthread_t tid;	
	pthread_attr_t pattr;
	//初始化attr属性
	pthread_attr_init(&pattr);
	pthread_attr_getdetachstate
	pthread_create(&tid,&pattr,callback,(void*)&pattr);
	pthread_attr_destroy(&pattr);
	return 0;
}

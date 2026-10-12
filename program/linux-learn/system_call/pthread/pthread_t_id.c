#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//pthread_self()获取当前线程的pthread_t
int main(){
	pthread_t ptid = pthread_self();
	printf("当前线程ID = %ld\n",ptid);
	return 0;
}

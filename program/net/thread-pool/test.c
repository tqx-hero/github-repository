#include "thread-pool.h"
/**
 *线程池测试用例
 *
 */

void* print_message(void * arg){
	char * message = (char *)arg;
	pthread_t pid = pthread_self();
	printf(" [%lu] : %s\n",pid,message);
}

int main(int argc ,char ** argv,char ** env){
	pthread_pool_t * pool = pthread_pool_create(0);
	if(!pool)
		exit(-1);
	char *message=argv[1];
	for(int i=0;i<100;++i){
		pthread_pool_submit(pool,print_message,message);
	}
	pthread_pool_destory(pool,1);
	return 0;
}

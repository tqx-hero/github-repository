#include "thread-poll.h"
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
	pthread_poll_t * poll = pthread_poll_create(0);
	if(!poll)
		exit(-1);
	char *message=argv[1];
	for(int i=0;i<100;++i){
		pthread_poll_submit(poll,print_message,message);
	}
	pthread_poll_destory(poll,1);
	return 0;
}

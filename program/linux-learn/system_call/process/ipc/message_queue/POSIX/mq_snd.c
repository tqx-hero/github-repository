#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#define MQ_NAME "/mq"

int main(){
	mqd_t mqfd;
	mqfd = mq_open(MQ_NAME,O_WRONLY);
	if(mqfd == (mqd_t)-1){
		perror("open mq error");
		exit(EXIT_FAILURE);
	}
	if(mq_unlink(MQ_NAME)){
		perror("unlink mq error");
		exit(EXIT_FAILURE);
	}
	char buf[] = "你好吗，老朋友!";
	if(mq_send(mqfd,buf,sizeof(buf),0)){
		perror("send mq error");	
		exit(EXIT_FAILURE);
	}
	printf("消息发送成功\n");
	mq_close(mqfd);
	return 0;
}

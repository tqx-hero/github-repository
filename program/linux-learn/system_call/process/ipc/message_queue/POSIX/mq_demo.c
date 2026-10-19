#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#define MQ_NAME "/mq"
#define EXIT(__MSG,__CODE) perror(__MSG); \
			exit(__CODE)
//POSIX标准的mq使用demo
int main(){
	//创建消息队列
	mqd_t mqfd;
	pid_t pid;
	long int buffer_size;
	struct mq_attr attr;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = 1024;
	size_t rcv_len;
//	可以在创建消息队列时通过oflag设置它是否为非阻塞状态,但创建时不能通过attr设置非阻塞
//	创建阶段只能设置attr的mq_maxmsg与mq_msgsize这两个属性
	//if((mqfd = mq_open(MQ_NAME,O_RDWR | O_CREAT | O_EXCL , 0666,NULL)) < 0){
	//使用attr设置mq的属性
	if((mqfd = mq_open(MQ_NAME,O_RDWR | O_CREAT | O_EXCL , 0666,&attr)) < 0){
		if(errno == EEXIST)
			mqfd = mq_open(MQ_NAME,O_RDWR); //以阻塞模式开启
		else{
			EXIT("mq open error",EXIT_FAILURE);
		}
	}
	if(mq_unlink(MQ_NAME)){
		EXIT("unlink mq name error",EXIT_FAILURE);
	}
	//获取消息队列的属性值
	if(mq_getattr(mqfd,&attr)){
		EXIT("get mq attr error",EXIT_FAILURE);
	}
	buffer_size = attr.mq_msgsize;
	//输出属性值
	//printf("mq_flags is nonblock ?: %d, mq_maxmsg = %ld,mq_msgsize = %ld,mq_curmsgs = %ld\n",attr.mq_flags == O_NONBLOCK,
	//	attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);
		
	char * bufp = (char*) malloc(buffer_size);
	if(!bufp){
		EXIT("malloc error",EXIT_FAILURE);
	}
	//创建子进程
	if(!fork()){
		//子进程发送消息
		sprintf(bufp,"这是第一条消息...");
		if(mq_send(mqfd,bufp,strlen(bufp) + 1,0)){
			free(bufp);
			EXIT("send msg error",EXIT_FAILURE);
		}
		free(bufp);
		if(mq_close(mqfd)){
			EXIT("close mq error",EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	//父进程接收消息，注意：接收消息的len字段必须不小于mq_msgsize属性值
	if((rcv_len = mq_receive(mqfd,bufp,buffer_size,NULL)) == -1){
		free(bufp);
		EXIT("rcv msg error",EXIT_FAILURE);
	}
	printf("消息字节数 = %ld\n",rcv_len);
	printf("主线程收到的消息： %s\n",bufp);
	free(bufp);
	if(mq_close(mqfd)){
		EXIT("close mq error",EXIT_FAILURE);
	}
	return 0;
}

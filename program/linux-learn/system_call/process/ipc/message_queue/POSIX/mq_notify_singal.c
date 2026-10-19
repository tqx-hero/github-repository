#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <signal.h>
#define MQ_NAME "/mq"
#define ERR_EXIT(__MSG) perror(__MSG); \
			exit(EXIT_FAILURE)

//mq_notify()的demo,使用SIGEV_SIGNAL选项，给进程发送信号的方式处理

void sig_handler(int signum,siginfo_t * siginfo,void * ucontext){
	printf("回调函数处理线程ID = %ld\n",syscall(SYS_gettid));
	mqd_t mqfd = *((mqd_t*)siginfo->si_value.sival_ptr);
	//异步传过来的参数:
	printf("信号类型 == SIGINT ? : %d\n",siginfo->si_signo);
	struct mq_attr attr;
	if(mq_getattr(mqfd,&attr)){
		ERR_EXIT("get mq attr error");
	}
	char* buf = (char*) malloc(attr.mq_msgsize);
	ssize_t rcv_len;
	if((rcv_len = mq_receive(mqfd,buf,attr.mq_msgsize,NULL)) == -1){
		ERR_EXIT("rcv mq error");
	}
	mq_unlink(MQ_NAME);
	mq_close(mqfd);
	printf("收到的字节数 = %ld\n",rcv_len);
	printf("消息内容: %s\n",buf);
	free(buf);
	exit(EXIT_SUCCESS);
}

int main(){
	//注册信号驱动
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if(sigaction(SIGINT,&sa,NULL)){
		ERR_EXIT("sigaction error");
	}
	mqd_t mqfd;
	if((mqfd = mq_open(MQ_NAME,O_CREAT | O_RDWR,0666,NULL)) == (mqd_t)-1){
		ERR_EXIT("open mq error");
	}
	printf("进程ID = %d\n",getpid());
	//设置信号驱动,消息传来发送SIGINT信号
	struct sigevent event;
	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo = SIGINT;
	event.sigev_value.sival_ptr = &mqfd;
	if(mq_notify(mqfd,&event)){
		ERR_EXIT("mq notify error");
	}
	pause();
}

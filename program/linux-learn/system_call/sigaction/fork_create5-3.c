#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
//生成5个子进程
int count;
void collection_child(int signum){
	pid_t pid;
	//千万不要使用if，因为信号不能排队，当多个子进程同时发送SIGCHLD时，信号只会记录一次
	//使用if会出现回收不全的情况
	while((pid = waitpid(-1,NULL,WNOHANG)) >0)//使用while循环回收，直到没有可回收的子进程退出
		printf("已回收第 %d 个子进程 : %d\n",++count,pid);
}

int main(){
	count = 0;
	pid_t pid;
	//将SIGCHLD信号加入阻塞集，使得该信号成为未决信号
	//在父进程中再将信号注册，并从阻塞集删除，这样父进程就可以接收SIGCHLD信号了
	sigset_t newset,oldset;
	sigemptyset(&newset);
	//将SIGCHLD添加到阻塞集
	sigaddset(&newset,SIGCHLD);
	sigprocmask(SIG_BLOCK,&newset,&oldset);
	for(int i=0;i < 5;++i){
		if((pid = fork()) < 0 )
			perror("");
		else if(pid ==0){
			//子进程直接还原阻塞集
			sigprocmask(SIG_SETMASK,&oldset,NULL);
			fprintf(stdout,"子进程已创建，pid = %d\n",getpid());
			exit(0);
		}
	}
	sleep(4);
	//父进程注册SIGCHLD信号处理
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = collection_child;
	sigaction(SIGCHLD,&sa,NULL);
	//将SIGCHLD去除阻塞集,直接使用oldset还原
	sigprocmask(SIG_SETMASK,&oldset,NULL);
	while(count < 5);
	printf("已全部回收所有的子进程\n");
	return 0;
}

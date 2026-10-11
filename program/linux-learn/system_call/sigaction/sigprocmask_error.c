#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//sigprocmask(2)的错误使用：
//千万不要在信号处理函数handler内部修改PCB的属性值
//因为在handler函数进入之前，内核会先把进程的所有寄存器、堆栈、PCB等全部压栈保存现场
//然后进行中断处理程序跳转，执行handler。
//当处理完成后，调用sigreturn，通过保存的栈内存储的弹栈地址进行EIP重定向，即进行return
//return自动弹栈，恢复现场，恢复到进程执行handler之前的那个样子，属性还是恢复到原来的样子
//所以在handler进行对进程属性设置是无意义的，弹栈后会恢复到原来的样子。
void alarm_handler(int signum){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	if(sigprocmask(SIG_UNBLOCK,&set,NULL) == -1){
		perror("sigprocmask unblock error");
		exit(-1);
	}
	printf("将SIGINT去除阻塞集成功\n");
}

int main(){
	sigset_t newset,oldset;
	sigemptyset(&newset);	//初始化信号集
	sigaddset(&newset,SIGINT); //将SIGINT添加到信号集
	if(sigprocmask(SIG_BLOCK,&newset,&oldset) == -1){ //将信号集添加到阻塞集
		perror("sigprocmask blocked error");
		exit(-1);
	}
	//5s后使用SIGALRM信号将SIGINT信号的屏蔽效果去除
	struct sigaction sg;
	sigemptyset(&sg.sa_mask);
	sg.sa_handler = alarm_handler;
	sg.sa_flags = SA_RESETHAND;
	sigaction(SIGALRM,&sg,NULL);
	alarm(8);
	while(1){
		printf("循环停不下来\n");
		sleep(2);
	}
	return 0;
}

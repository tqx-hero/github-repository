#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
//给某个进程发送信号
#ifdef I
#define SIG SIGINT
#endif

#ifdef S
#define SIG SIGSTOP
#endif

#ifdef C
#define SIG SIGCONT
#endif

#ifdef K
#define SIG SIGKILL
#endif

#ifdef T
#define SIG SIGTERM
#endif
int main(int argc,char** argv){
	if(argc < 2){
		fprintf(stderr,"参数个数不足，应该包含: 进程号\n");	
		return -1;
	}
	pid_t pid = atoi(argv[1]);;
	printf("输入的进程号 = %d\n",pid);
	printf("要发送的信号 = %d\n",SIG);
	if(kill(pid,SIG) == -1)
		perror("kill error");
	return 0;
}

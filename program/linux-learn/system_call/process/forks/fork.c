#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv,char** env){
	//char buf[] = "这是系统";
	if(argc !=3){
		fprintf(stderr,"请输入父进程、子进程输入\n");
		return -1;
	}
	printf("父进程的输入：%s\n",argv[1]);
	printf("当前进程ID：%d\n",getpid());
	pid_t pid;
	if((pid = fork()) < 0 ){
		perror("");
	}
	if(!pid){
		printf("子进程输入:%s\n",argv[2]);
		printf("子进程中父进程的输入:%s\n",argv[1]);
		printf("当前进程ID2 = %d\n",getpid());
		printf("父进程ID= %d\n",getppid());
		exit(0);
	}else{
		printf("父进程fork(),子进程ID = %d\n",pid);
	}
	//当fork()完成后，会生成子进程共同执行该代码，一共2个进程执行，所以这条输出会生成2条。
	//不让子进程执行该代码，解决办法就是在子进程执行的代码最后添加退出语句exit
	printf("最后输出：pid = %d\n",getpid());
	return 0;
}

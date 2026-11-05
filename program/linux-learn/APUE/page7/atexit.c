#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static void e1(){
	fprintf(stdout,"进程[%d] 调用函数e1()\n",getpid());
}

static void e2(){
	fprintf(stdout,"进程[%d] 调用函数e2()\n",getpid());
}

int main(){

	if(atexit(e1))
		fprintf(stderr,"register e1() error\n");
	if(atexit(e1))
		fprintf(stderr,"register e1() error\n");
	if(atexit(e2))
		fprintf(stderr,"register e2() error\n");
	fprintf(stdout,"主进程[%d]结束\n",getpid());
	//终止处理程序只适用于标准库函数exit(3)或main函数return退出时执行，不适用于_exit(2)与_Exit(2)
	//_exit(0);
	while(1);
	exit(0);
}

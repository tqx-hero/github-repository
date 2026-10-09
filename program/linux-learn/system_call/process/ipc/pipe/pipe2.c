#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//使用pipe()+fork()+exec()实现跨进程之间的管道通信
//父进程负责往管道内写入，子进程负责读取出来
int main(){
	//pipe创建管道
	int filedes[2];
	pid_t pid;
	if(pipe(filedes) == -1){
		perror("create pipe error");
		exit(-1);
	}
	//创建子进程
	if((pid = fork()) == -1){
		perror("fork error");
		close(filedes[0]);
		close(filedes[1]);
		exit(-1);
	}
	if(pid == 0){
		//子进程去执行另一个程序
		char rfd[16],wfd[16];
		sprintf(rfd,"%d",filedes[0]);
		sprintf(wfd,"%d",filedes[1]);
		char * argv[] = {"pipe3",rfd,wfd,NULL};
		execv("./pipe3",argv);
		perror("execv pipe3 error");
		exit(-1);
	}
	//父进程负责写入数据
	char buf[] = "大家好才是真的好!";
	write(filedes[1],buf,sizeof(buf));
	close(filedes[0]);
	close(filedes[1]);
	//父进程等待子进程结束，回收PCB
	waitpid(pid,NULL,0);
	return 0;
}

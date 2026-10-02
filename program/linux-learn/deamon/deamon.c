#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	//fork创建子进程
	pid_t pid;
	if((pid = fork()) < 0)
	{
		perror("");
		return -1;
	}
	//父进程退出
	if(pid)
		return 0;
	//子进程创建会话
	setsid();
	//改变工作目录到根目录(可选)
	chdir("/");
	//关闭文件描述符(可选)
	close(0);
	close(1);
	close(2);
	//设置进程的掩码(可选)
	umask(0000);
	//设置执行任务
	//每5秒向日志文件中追加信息
	int fd = open("/home/tqx/linux-learn/deamon/deamon.log",O_CREAT | O_WRONLY | O_APPEND,0644);
	if(fd == -1){
		perror("");
		exit(-1);
	}
	char buf[] = "hello world\n";
	while(1){
		write(fd,buf,sizeof(buf));
		sleep(5);
	}
	return 0;
}

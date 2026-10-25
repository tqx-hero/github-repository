#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSG_BUF_SIZ 1024
//pipe()的使用
int main(){
	int fdes[2];
	if(pipe(fdes)){
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
	char * msg_buf = malloc(MSG_BUF_SIZ);
	if(!msg_buf){
		perror("malloc space error");
		exit(EXIT_FAILURE);
	}
	pid_t pid;
	ssize_t bytes;
	//子进程
	if(!(pid = fork())){
		//子进程读fd，可以提前关闭写
		close(fdes[1]);
		while(1){
			bytes = read(fdes[0],msg_buf,MSG_BUF_SIZ);
			if(bytes <= 0){
				fprintf(stdout,"管道写端已关闭，正在退出...\n");
				break;
			}
			printf("子进程读到的数据 = %s\n",msg_buf);
		}
		close(fdes[0]);
		free(msg_buf);
		exit(EXIT_SUCCESS);
	}
	//父进程开始写
	close(fdes[0]);
	while(1){
		printf("请输入要发送的消息：\n");
		fgets(msg_buf,MSG_BUF_SIZ,stdin);
		//如果输入的是end，结束进程
		if(strncasecmp("end",msg_buf,3) == 0){
			printf("正在退出...\n");
			break;
		}
		write(fdes[1],msg_buf,strlen(msg_buf) + 1);
	}
	close(fdes[1]);
	free(msg_buf);
	return 0;
}

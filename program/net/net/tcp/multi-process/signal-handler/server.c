#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <err.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
/**
 * 回收子进程PCB，避免僵尸进程
 */
void deal_with_child(int signo){
	printf("进入子进程回收函数\n");
	pid_t pid;
	int stat;
	while((pid = waitpid(-1,&stat,WNOHANG)) >0)
		printf("child process: %d shutdown\n",pid);
	return;
}

/**
 *创建多进程下的TCP服务器，并通过信号反馈回收子进程
 */
int main(int argc,char* argv[],char* env[]){
	//将信号添加到阻塞集
	//sigset_t sig_t;
	//sigemptyset(&sig_t);
	//设置信号的阻塞集为子进程信号
	//sigaddset(&sig_t,SIGCHLD);
	//sigprocmask(SIG_BLOCK,&sig_t,NULL);
	//1、创建监听socket
	int lfd =  socket(AF_INET,SOCK_STREAM,0);
	if(lfd ==-1)
		err(EXIT_FAILURE,"create listen socket");
	//2、绑定socket
	struct sockaddr_in server_addr;
	//bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int bind_status = bind(lfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(bind_status ==-1)
		err(EXIT_FAILURE,"bind socket");
	//3、设置socket为监听模式
	int listen_status = listen(lfd,4096);
	if(listen_status ==-1)
		err(EXIT_FAILURE,"create listen");
	//4、父进程accept监听连接的socket，并创建连接socket
	//设置父进程监听处理子进程的SIGCHLD信号
	struct sigaction act;
	act.sa_handler = deal_with_child;
	act.sa_flags =0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD,&act,NULL);
	while(1){
		struct sockaddr_in client_addr;
		socklen_t sk_len = sizeof(client_addr);
		int con_fd = accept(lfd,(struct sockaddr*)&client_addr,&sk_len);
		if(con_fd < 0){
			printf("........................\n");
			if(errno == EINTR)
				continue;
			else
				err(EXIT_FAILURE,"accept connection");
		}
		char client_ip[INET_ADDRSTRLEN] ;
	       	inet_ntop(AF_INET,&client_addr.sin_addr,client_ip,INET_ADDRSTRLEN);
		uint16_t cli_port = ntohs(client_addr.sin_port);
		printf("客户端:[%s:%d] 已上线\n",client_ip,cli_port);
		//5、父进程通过fork创建子进程，子进程执行连接socket的任务
		int pid;
		if((pid = fork())==0){
			close(lfd);
			char message_buffer[1024];
			while(1){
				int read_len = read(con_fd,message_buffer,sizeof(message_buffer));
				if(read_len <=0)
				{
					printf("客户端:[%s:%d] 已下线\n",client_ip,cli_port);
					break;
				}
				message_buffer[read_len] = 0;
				printf("[%s:%d] : %s\n",client_ip,cli_port,message_buffer);
				//把消息发送回客户端，模拟服务器处理socket的流程
				//message_buffer[read_len-1] = '\n';
				write(con_fd,message_buffer,read_len);
			}
			//close(con_fd);
			exit(0);
		}
		close(con_fd);
	//			struct sigaction act;
	//			act.sa_handler = deal_with_child;
	//			sigemptyset(&act.sa_mask);
	//			act.sa_flags = 0;
	//			sigaction(SIGCHLD,&act,NULL);
	//			sigprocmask(SIG_UNBLOCK,&sig_t,NULL);
		
	}
	return 0;
}

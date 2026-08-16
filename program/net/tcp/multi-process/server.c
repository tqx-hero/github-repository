#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <err.h>
#include <arpa/inet.h>
#include <string.h>
/**
 *多进程的TCP服务器实现
 */
int main(int argc,char* argv[],char * env[]){
	//1、创建监听socket
	int listen_fd = socket(AF_INET,SOCK_STREAM,0);
	if(listen_fd ==-1)
		err(EXIT_FAILURE,"socket");
	//2、绑定socket的IP、端口号(注意：必须是本主机的IP地址)
	struct sockaddr_in server_addr,client_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	int bstate = bind(listen_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(bstate == -1)
		err(EXIT_FAILURE,"bind");
	//3、将监听socket由主动连接模式设置为被动连接模式
	int lstate = listen(listen_fd,1024);
	if(lstate == -1)
		err(EXIT_FAILURE,"LISTEN");
	//开始去接收客户端，处理消息
	char message_buffer[1024];
	int pid;
	for(;;){
		struct sockaddr_in client_addr;
		socklen_t client_sock_len = sizeof(client_addr);
		int con_fd = accept(listen_fd,(struct sockaddr*)&client_addr,&client_sock_len);
		if(con_fd ==-1)
			err(EXIT_FAILURE,"accpet");
//		char * client_ip = inet_ntoa(client_addr.sin_addr);
//		uint16_t client_port = ntohs(client_addr.sin_port);
		//创建子进程处理与客户端的连接
		if((pid =fork()) ==0){
			close(listen_fd);
			struct sockaddr_in clientaddr;
//			socklen_t calen = sizeof(clientaddr);
//			//通过getpeername获取对方的ip地址与端口号,或者直接使用父进程accept之后保存下来的客户端信息
			int status =  getpeername(con_fd,(struct sockaddr *)&clientaddr,&client_sock_len);
			if(status ==-1)
				exit(0);
			char client_ip[INET_ADDRSTRLEN];
			inet_ntop(AF_INET,&clientaddr.sin_addr,client_ip,INET_ADDRSTRLEN);
			uint16_t client_port = ntohs(clientaddr.sin_port);
			printf("客户端:[%s:%d] 已连接\n",client_ip,client_port);
			//子进程复制了父进程的PCB，因为该进程是处理套接字通信的，所以应该先关闭监听的套接字
			//防止套接字泄露
			for(;;){
				//读取链接的socket发过来的数据
				int read_len = read(con_fd,message_buffer,sizeof(message_buffer));
				if(read_len <=0){
					printf("客户端:[%s:%d] 已断开\n",client_ip,client_port);
//					close(con_fd);
					break;
				}
				message_buffer[read_len]=0;
				printf("%s\n",message_buffer);
				//写入消息发送
				fgets(message_buffer,sizeof(message_buffer),stdin);
				int send_len = strlen(message_buffer);
				message_buffer[send_len-1]=0;
				write(con_fd,message_buffer,send_len);
			}
			close(con_fd);
			exit(0);
		}
		close(con_fd);
	}
	return 0;
}

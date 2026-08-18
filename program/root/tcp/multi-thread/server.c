#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <err.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include "../../wrapper/sockwrapper.h"
#define BUFFER_MAX_SIZE  512
int main(){
 	int lfd = Socket(AF_INET,SOCK_STREAM,0);
	//启用地址/端口复用设置必须在创建完成socket之后，绑定socket之前，顺序不要颠倒
	int reuser_resource =1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEPORT,&reuser_resource,sizeof(int));
       	//setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&reuser_resource,sizeof(int));
	//int reuseport_state;
	//socklen_t reuseport_len = sizeof(int);
	//getsockopt(lfd,SOL_SOCKET,SO_REUSEPORT,&reuseport_state,&reuseport_len);
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int bind_status = Bind(lfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	int lis_status = Listen(lfd,0);
	void * deal_with_child(void*);
	while(1){
	//	struct sockaddr_in client_addr;
	//	socklen_t cli_len = sizeof(client_addr);
		//int con_fd = accept(lfd,(struct sockaddr*)&client_addr,&cli_len);
		int con_fd = Accept(lfd,NULL,NULL);
		pthread_t th;
		pthread_create(&th,NULL,deal_with_child,(void*)(long)con_fd);
		pthread_detach(th);
	}
	close(lfd);
	return 0;
}

void * deal_with_child(void* arg){
	int con_fd = (int)(long)arg;
	struct sockaddr_in client_addr;
	socklen_t skt_len =sizeof(client_addr);
	int get_state = getpeername(con_fd,(struct sockaddr*)&client_addr,&skt_len);
	if(get_state == -1){
		perror("getpeername");
		goto func_return;
	}
	char cli_ip[INET_ADDRSTRLEN] ;
       	inet_ntop(AF_INET,&client_addr.sin_addr,cli_ip,INET_ADDRSTRLEN);
	uint16_t port = ntohs(client_addr.sin_port);
	printf("[%s:%d]已上线!\n",cli_ip,port);
	char message_buffer[BUFFER_MAX_SIZE];
	while(1){
		int read_len = read(con_fd,message_buffer,sizeof(message_buffer));
		if(read_len <=0)
			break;
		message_buffer[read_len] = 0;
		printf("[%s:%d]:%s\n",cli_ip,port,message_buffer);
		int write_len = write(con_fd,message_buffer,read_len);
		if(write < 0)
			break;
	}
	printf("[%s:%d]已下线!\n",cli_ip,port);
func_return:
	close(con_fd);
	pthread_exit(NULL);
}


#include "./function/header/http_handler.h"
#include <sys/epoll.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define SERVER_PORT 9000
#define EVENT_ARR_MAX_SIZE 1024
#define MESSAGE_MAX_SIZE 1500
/*
	重写web服务器
*/
int main(){
	int epfd = -1,lfd = -1;
	//创建监听套接字
	if((lfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("create socket error");
		goto close_resource;
	}
	int opt =1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
	setsockopt(lfd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(int));
	//绑定监听端口号
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	if(bind(lfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1){
		perror("bind error");
		goto close_resource;
	}
	listen(lfd,128);
	//创建epoll实例
	if((epfd = epoll_create(1)) == -1)
	{
		perror("create epoll instance error");
		goto close_resource;
	}
	//监听事件上树
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = lfd;
	if(epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&event) == -1){
		perror("epoll ctl add error");
		goto close_resource;
	}
	//循环监听
	struct epoll_event evt_arr[EVENT_ARR_MAX_SIZE];
	char message_buf[MESSAGE_MAX_SIZE];
	char error_buf[64];
	while(1){
		int ev_cnt;
		while (((ev_cnt = epoll_wait(epfd, evt_arr, EVENT_ARR_MAX_SIZE, -1)) == -1 && errno == EINTR) || ev_cnt == 0)
			;
		for(int i=0;i < ev_cnt;++i){
			struct epoll_event evt =  evt_arr[i];
			int cur_fd = evt.data.fd;
			//判断是监听的fd还是连接的fd
			//监听的fd处理
			if(cur_fd == lfd && (evt.events & EPOLLIN)){
				printf("有新的连接进入\n");
				//accept获取连接的套接字，将其添加到epoll树上
				struct sockaddr_in client_addr;
				socklen_t skt_len = sizeof(client_addr);
				char cli_ip[INET_ADDRSTRLEN];
				int con_fd = accept(cur_fd,(struct sockaddr*)&client_addr,&skt_len);
				printf("[%s : %d] 上线\n",
					inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cli_ip,INET_ADDRSTRLEN),ntohs(client_addr.sin_port));
				//新连接上树
				//设置套接字为非阻塞
				int flags = fcntl(con_fd,F_GETFL,0);
				flags |= O_NONBLOCK;
				fcntl(con_fd,F_SETFL,flags);
				event.events = EPOLLIN;
				event.data.fd = con_fd;
				epoll_ctl(epfd,EPOLL_CTL_ADD,con_fd,&event);
			}else if(evt.events & EPOLLIN){
				printf("有新的读事件\n");
				//连接套接字的读事件
				int r_len = read(cur_fd,message_buf,sizeof(message_buf));
				if(r_len <= 0){
					//关闭连接，下树
					printf("client close\n");
					epoll_ctl(epfd,EPOLL_CTL_DEL,cur_fd,NULL);
					close(cur_fd);
					continue;
				}
				//处理事件
				if(parse_http_request(cur_fd,message_buf,r_len,error_buf) == -1)
					printf("http request error : %s\n",error_buf);
				
			}else if(evt.events & EPOLLOUT){
				printf("写事件\n");
			}
		}
	}
	close(lfd);
	return 0;
close_resource:
	if(lfd !=-1)
		close(lfd);
	if(epfd != -1)
		close(epfd);
	return -1;
}

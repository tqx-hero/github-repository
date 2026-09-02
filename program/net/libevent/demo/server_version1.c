#include <event.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SERVER_PORT 9999
/*
	libevent实现的服务器版本1
*/
void handler_new_socket(evutil_socket_t, short, void *);
int main(){
	//创建socket
	int lfd = -1;
	struct event_base* e_base =NULL;
	struct event* ev = NULL;
	lfd = socket(AF_INET,SOCK_STREAM,0);
	if(lfd == -1){
		perror("create socket error");
		goto fail_ret;
	}
	//设置socket端口、地址复用
	int opt =1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	setsockopt(lfd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));
	//绑定端口号
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	if(bind(lfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
	{
		perror("bind socket error");
		goto fail_ret;
	}
	//设置socket为监听模式
	listen(lfd,0);	
	//创建libevent的base根节点
	e_base = event_base_new();
	if(!e_base){
		perror("new event base error");
		goto fail_ret;
	}
	//创建监听事件
	ev = event_new(e_base,lfd,EV_READ | EV_PERSIST,handler_new_socket,e_base);
	if(!ev){
		perror("new event error");
		goto fail_ret;
	}
	//上树。将创建的监听事件添加到事件管理树
	if(event_add(ev,NULL) == -1){
		perror("add event error");
		goto fail_ret;
	}
	//持续监听,以下两种方式都可以，等价
	//event_base_loop(e_base,0);
	event_base_dispatch(e_base);
	close(lfd);
	event_base_free(e_base);
	event_free(ev);
	return 0;
fail_ret:
	if(lfd != -1)
		close(lfd);
	if(e_base)
		event_base_free(e_base);
	if(ev)
		event_free(ev);
	return -1;
}

void read_connection(evutil_socket_t con_fd, short event_type, void * arg){
	printf("..................\n");
	char message_buf[1500];
	int r_len = read(con_fd,message_buf,sizeof(message_buf));
	if(r_len >0){
		message_buf[r_len] = 0;	
		printf("info: %s\n",message_buf);
		write(con_fd,message_buf,r_len);
		return;
	}
	else if(r_len ==0)
		printf("client close\n");
	else if(r_len  == -1)
		printf("client error\n");
	//下树
	close(con_fd);
	event_del((struct event*)arg);
	event_free((struct event*)arg);
	
}

//回调函数,添加新的连接事件
void handler_new_socket(evutil_socket_t lfd, short event_type, void * arg){
	printf("有新的连接到达\n");
	printf("事件类型 = %d\n",event_type);
	struct sockaddr_in client;
	socklen_t skt_len = sizeof(client);
	//获取新的连接
	int con_fd = accept(lfd,(struct sockaddr*)&client,&skt_len);
	if(con_fd == -1)
		return;
	char cli_ip[INET_ADDRSTRLEN];
	printf("[%s:%d]已上线!\n",inet_ntop(AF_INET,&client.sin_addr.s_addr,cli_ip,INET_ADDRSTRLEN),ntohs(client.sin_port));
	//创建新的监听事件,上树
	struct event* ev = event_new((struct event_base*)arg,con_fd,EV_READ | EV_PERSIST,read_connection,event_self_cbarg());
	event_add(ev,NULL);
}


#include "sockwrapper.h"

void perror_exit(const char * msg);

int Socket(int domain,int type,int protocol){
	int ret;
	if((ret = socket(domain,type,protocol)) == -1)
		perror_exit("socket create");
	return ret;
}

int Bind(int sock_fd,const struct sockaddr* addr,socklen_t len){
	int ret;
	if((ret = bind(sock_fd,addr,len)) == -1)
		perror_exit("bind");
	return ret;
}

int Listen(int sock_fd,int backlog){
	int ret;
	if(backlog <=0)
		backlog = BACK_LOG_DEFAULT;
	if((ret = listen(sock_fd,backlog)) == -1)
		perror_exit("listen");
	return ret;
}

int Accept(int sock_fd,struct sockaddr* addr,socklen_t * addrlen){
	int ret;
	while((ret = accept(sock_fd,addr,addrlen)) == -1){
		//两种情况：被信号中断或者三次握手失败客户端断开连接
		//此时监听套接字没有出现故障，需要继续监听
		if(errno == EINTR || errno == ECONNABORTED)
			continue;
		perror_exit("accept");
	}
	return ret;	
}


//int Pthread_create(pthread_t* ph,const pthread_attr_t * attr,void*(* func)(void*),void* arg){
//	int ret;
//	if((ret = pthread_create(ph,attr,func,arg)) == -1)
//		perror_exit("pthread_create");
//	return ret;
//}

int Epoll_ctl(int epfd,int op,int fd,struct epoll_event* event){
	int ret;
	if((ret = epoll_ctl(epfd,op,fd,event)) == -1)
		perror_exit("epoll_ctl error");
	return ret;
}

ssize_t Read(int fd,void* buffer,size_t len){
	int ret;
	while((ret = read(fd,buffer,len)) == -1){
		//如果是被信号中断，读取继续
		if(errno == EINTR)
			continue; 
		break;
	}
	return ret;
}

ssize_t Write(int fd,void* buffer,size_t len){
	int ret;
	while((ret = write(fd,buffer,len)) == -1){
		if(errno == EINTR)
			continue;
		break;
	}
	return ret;
}

int Getpeername(int fd,struct sockaddr* addr,socklen_t * len){
	int ret;
	if(getpeername(fd,addr,len) == -1)
		perror_exit("getpeername fail");
	return ret;
}

int Epoll_create(int size){
	int ret;
	if((ret = epoll_create(size)) == -1)
		perror_exit("epoll create error");
	return ret;
}

int get_client_info_ipv4(struct sockaddr_in* addr,void* client_ip,uint16_t* client_port){
	inet_ntop(AF_INET,&addr->sin_addr.s_addr,client_ip,INET_ADDRSTRLEN);
 	*client_port = ntohs(addr->sin_port);
	return 0;
}


void perror_exit(const char * msg){
	perror(msg);
	exit(-1);
}

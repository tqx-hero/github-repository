#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/epoll.h>
//#include <pthread.h>
#define BACK_LOG_DEFAULT 128
int Socket(int domain,int type,int protocol);

int Bind(int sock_fd,const struct sockaddr* addr,socklen_t len);

int Listen(int sock_fd,int backlog);

int Accept(int sock_fd,struct sockaddr* addr,socklen_t * addrlen);

//int Pthread_create(pthread_t* ph,const pthread_attr_t * attr,void*(* func)(void*),void* arg);

ssize_t Read(int fd,void* buffer,size_t len);

ssize_t Write(int fd,void* buffer,size_t len); 

int Getpeername(int fd,struct sockaddr* addr,socklen_t * len);

int Epoll_ctl(int epfd,int op,int fd,struct epoll_event* event);

int Epoll_create(int size);

int get_client_info_ipv4(struct sockaddr_in* addr,void* client_ip,uint16_t* client_port);


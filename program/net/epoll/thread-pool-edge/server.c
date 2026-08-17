#include "/home/tqx/net/wrapper/sockwrapper.h"
#include "/home/tqx/net/thread-pool/thread-pool.h"
#include <fcntl.h>
#include <sys/syscall.h>
#define SERVER_PORT 9000
#define EVENT_BUFFER_SIZE 1024
#define MESSAGE_BUFFER_SIZE 1499
/**
 *在边沿触发事件的基础上实现线程池处理连接套接字业务的功能
 *epoll实现多路复用服务器
 *监听边沿触发事件改动：
 *1、设置监听套接字、连接的套接字为非阻塞模式
 *2、设置epoll树上的各套接字节点的监听事件为边沿触发
 *3、由于边沿触发模式，只有当缓冲区数据有变动才会触发一次，读事件中必须循环读取才能保证把数据全部读完
 *   又因为read、write默认为阻塞模式，当缓冲区读完数据后会阻塞，所以需要将套接字设置成非阻塞模式(步骤1).
 */
typedef struct epoll_event event_type;
typedef struct sockaddr sock_addr_type;

typedef struct {
	int epfd;
	int con_fd;
	uint16_t cli_port;
	char cli_ip[INET_ADDRSTRLEN];
}con_sock_t;

int main(){
	//创建监听套接字,设置为非阻塞
	int lfd = Socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK,0);
	//设置套接字端口、地址复用
	int opt =1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
	setsockopt(lfd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(int));
	//绑定
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind(lfd,(sock_addr_type*)&server_addr,sizeof(server_addr));
	//使监听套接字属性由主动连接变为被动链接
	Listen(lfd,0);
	//创建epoll实例
	int epfd = Epoll_create(1);
	//绑定套接字的要监听的事件
	event_type ep_event;
	ep_event.events = EPOLLIN ; //可以用或运算进行添加 | EPOLLOUT
	ep_event.data.fd = lfd;
	Epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ep_event);
	//内核监听事件
	event_type event_buffer[EVENT_BUFFER_SIZE];
	//创建线程池，用线程池来处理连接的各种业务
	pthread_pool_t * pool = pthread_pool_create(20);
	if(!pool)
		exit(-1);
	void * deal_with_socket(void *);
	while(1){
		//判断一下是否是被信号中断的，如果是
		int event_count;
	       while(((event_count = epoll_wait(epfd,event_buffer,EVENT_BUFFER_SIZE,-1))
			 == -1 && errno == EINTR)
			|| event_count == 0	       
				       );
		for(int i=0;i<event_count;i++){
			event_type event = event_buffer[i];
			int cur_fd = event.data.fd;
			struct sockaddr_in cli_addr;
			socklen_t stk_len = sizeof(cli_addr);
			char cli_ip[INET_ADDRSTRLEN];
			uint16_t cli_port;
			//查看文件描述符是否为监听套接字
			//并且监听套接字是否为读事件
			if(cur_fd == lfd && (event.events & EPOLLIN)){
				//如果是监听套接字，那就accept连接，并将新的
				//连接套接字注册到epoll红黑树结构中监听
				int con_fd = Accept(lfd,(sock_addr_type*)&cli_addr,&stk_len);
				//设置新连接的套接字为非阻塞模式
				int flags = fcntl(con_fd,F_GETFL,0);
				fcntl(con_fd,F_SETFL,flags | O_NONBLOCK);
				get_client_info_ipv4(&cli_addr,cli_ip,&cli_port);
				printf("[%s:%d]已上线!\n",cli_ip,cli_port);
				//将已连接的socket注册监听事件
				//设置事件触发为边沿触发
				//注意：当监听写事件时，必须设置为边沿触发，以免不必要的状态切换
				ep_event.events = EPOLLIN | EPOLLET; // | EPOLLOUT;
				ep_event.data.fd = con_fd;
				Epoll_ctl(epfd,EPOLL_CTL_ADD,con_fd,&ep_event);
			}else if(event.events & EPOLLIN){
				//如果是连接的套接字，那就读取该套接字缓冲区中的内容
				//使用线程池提交该任务
				con_sock_t * con_sock =  malloc(sizeof(con_sock_t));
				if(!con_sock){
					perror("malloc con_sock_t error");
					close(cur_fd);
					continue;
				}
				Getpeername(cur_fd,(sock_addr_type*)&cli_addr,&stk_len);
				con_sock ->epfd = epfd;
				con_sock -> con_fd = cur_fd;
				con_sock -> cli_port = cli_port;
				get_client_info_ipv4(&cli_addr,con_sock->cli_ip,&con_sock->cli_port);
				//提交任务到线程池
				pthread_pool_submit(pool,deal_with_socket,(void*)con_sock);
			}
		
		}
	}
	pthread_pool_destory(pool,1);
	close(lfd);
	return 0;
}
//需要修改arg参数为一个结构体：结构体分别存放当前套接字cur_fd与epoll根节点的描述符epfd

void * deal_with_socket(void *arg){
	con_sock_t * con_sock = (con_sock_t*) arg;
	if(!con_sock)
	{
		perror("con_sock_t* format error");
		return NULL;
	}
	int epfd = con_sock->epfd,cur_fd = con_sock->con_fd;
	char *cli_ip = con_sock->cli_ip;
	uint16_t cli_port= con_sock->cli_port;	
	char recv_buffer[MESSAGE_BUFFER_SIZE+1];
	pid_t tid = syscall(SYS_gettid);
	while(1){	
		int r_len = Read(cur_fd,recv_buffer,MESSAGE_BUFFER_SIZE);
		if(r_len == 0){
			printf("%d::[%s:%d]已下线!\n",tid,cli_ip,cli_port);
			goto return_func;
		}
		if(r_len == -1){
		//由于设置了非阻塞，read可能读不到数据返回-1，此时需要判断
		//是否为正常读不到数据还是异常
			if(!(errno == EAGAIN || errno == EWOULDBLOCK))
			//如果是非正常读取，将该socket关闭，从epoll结构中删除
				perror("read error");
			else
				cur_fd = -1;
			goto return_func;
		}
		recv_buffer[r_len] =0;
		printf("%d::[%s:%d]:%s\n",tid,cli_ip,cli_port,recv_buffer);
		Write(cur_fd,recv_buffer,r_len);
	}
return_func:
	if(cur_fd >=0){
		//需要将这个socket从epoll红黑树中去除
		//下线断开连接
		Epoll_ctl(epfd,EPOLL_CTL_DEL,cur_fd,NULL);
		close(cur_fd);
	}
	//释放资源
	free(con_sock);
	return NULL;
}


#include "../wrapper/sockwrapper.h"
#include <sys/select.h>
/**
 *定义select版本的多路复用服务器
 */
int main(){
	//创建socket
	int listen_fd = Socket(AF_INET,SOCK_STREAM,0);
	//设置端口/地址复用
	int opt =1;
	setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(int));
	setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
	//绑定
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//	socklen_t skt_len= sizeof(server_addr);
	Bind(listen_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	//监听
	Listen(listen_fd,0);
	//设置内核监听事件select
	fd_set r_set,old_set;
	//设置需要监听的socket集合
	FD_ZERO(&old_set);
	FD_SET(listen_fd,&old_set);
	int max_fd=listen_fd,event_size;
	while(1){
		//设置监听集合，并开始监听
		r_set = old_set;
		event_size = select(max_fd+1,&r_set,NULL,NULL,NULL);
		if(event_size <= 0)
		{
			perror("select error");
			break;	
		}else{
			struct sockaddr_in client_addr;
			socklen_t stk_len = sizeof(client_addr);
			char cli_ip[INET_ADDRSTRLEN];
			uint16_t cli_port;
			//有事件发生，提取
			//先判断有没有连接，有连接就先处理连接
			if(FD_ISSET(listen_fd,&r_set)){
				int con_fd = Accept(listen_fd,(struct sockaddr*)&client_addr,&stk_len);
				printf("[%s:%d]已上线!\n",inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cli_ip,INET_ADDRSTRLEN),ntohs(client_addr.sin_port));
				//将连接的socket放入监听集合，并更新最大描述符
				FD_SET(con_fd,&old_set);
				if(max_fd < con_fd)
					max_fd = con_fd;
				//判断是否只有这一个事件，如果是，就不需要再遍历后面的集合
				if(--event_size == 0)
					continue;
			}
			//遍历查找其他有事件的socket
			char recv_buffer[512];
			for(int i = listen_fd+1; i<= max_fd;i++){
				if(FD_ISSET(i,&r_set)){
					inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,cli_ip,INET_ADDRSTRLEN);
					cli_port = ntohs(client_addr.sin_port);
					--event_size;
					//处理这个socket
					int r_len = Read(i,recv_buffer,sizeof(recv_buffer));
					if(r_len == 0){
						//下线处理
						Getpeername(i,(struct sockaddr*)&client_addr,&stk_len);
						printf("[%s:%d]已下线!\n",cli_ip,cli_port);
						//将该套接字从集合中去除
						FD_CLR(i,&old_set);
						close(i);
					}else{
						recv_buffer[r_len]=0;
						printf("[%s:%d]: %s\n",cli_ip,cli_port,recv_buffer);
						Write(i,recv_buffer,r_len);	
					}
				}
				//判断是否已处理完有事件的socket，如果是，直接跳出循环
				if(event_size == 0)
					break;
			}		
		}
	}
	close(listen_fd);

	return 0;
}

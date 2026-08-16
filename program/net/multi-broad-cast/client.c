#include <sys/socket.h>
#include <arpa/inet.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
 *多播组的创建
 */
int main(int argc,char * argv[],char* env[]){
	int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd ==-1)
		err(EXIT_FAILURE,"socket");
	
	//定义一个多播组地址：224.0.0.1，并将其绑定到socket
	char multi_ip[] ="224.0.0.1";
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(multi_ip);
	//将主机所有的IP全部加入到多播组
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(sock_fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));

	//bind端口号
	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(18000);
	addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock_fd,(struct sockaddr *) &addr_in,sizeof(addr_in));
	//创建接收消息的缓冲区
	char buffer[512]={0};
	struct sockaddr server_addr;
	socklen_t slen;
	//接收消息
	int recv_len = recvfrom(sock_fd,buffer,sizeof(buffer),0,&server_addr,&slen);
	if(recv_len <=0)
		err(EXIT_FAILURE,"recvfrom");
	printf("%s\n",buffer);
	return 0;
}

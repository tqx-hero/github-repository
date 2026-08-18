#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>

int main(){
	int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd < 0 ){
		printf("%s\n",strerror(errno));
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	//以下是给套接字对象的addr设置ip的两种方式
	//1、通过inet_pton转换函数，将字符串ip转换为整型形式
	//inet_pton(AF_INET,"192.168.1.7",&addr.sin_addr.s_addr);
	//2、使用通配地址方式
	addr.sin_addr.s_addr = INADDR_ANY;

	int success = bind(sock_fd,(struct sockaddr *)&addr,sizeof(addr));
	if(success < 0 ){
		printf("%s\n",strerror(errno));
		return -1;
	}
	//listen(sock_fd,50);
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);
	while(1){
		char buf[128]={0};
		int recv_len = recvfrom(sock_fd,buf,sizeof(buf),0,(struct sockaddr *)&client_addr,&len);
		printf("%s\n",buf);
	//	fgets(buf,sizeof(buf),stdin);
		sendto(sock_fd,buf,recv_len,0,(struct sockaddr *)&client_addr,len); 
	}
	return 0;
}

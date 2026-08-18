#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>
/**
 *发送广播
 */
int main(int argc ,char* argv[]){
	
	if(argc != 2)
		err(EXIT_FAILURE,"input paramaters error!");
	//获取第二个参数ip地址
	char *ip= argv[1];
	int sfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sfd== -1)
		err(EXIT_FAILURE,"create socket");
	int broadcast =1;
	//设置socket属性值
	int opts= setsockopt(sfd,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast));
	if(opts ==-1)
		err(EXIT_FAILURE,"setsockopt");
	char send_buf[1024];
	//设置发送的套接字属性值，包括协议族、端口号、ip地址等信息
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr(ip);
	strcpy(send_buf,"broadcast success!");
	//printf("send_buf len = %ld\n",strlen(send_buf));
	////发送信息
	int send_len = sendto(sfd,send_buf,strlen(send_buf),0,(struct sockaddr *)&addr,sizeof(addr));
	if(send_len <=0)
		err(EXIT_FAILURE,"sendto");
	return 0;	
}

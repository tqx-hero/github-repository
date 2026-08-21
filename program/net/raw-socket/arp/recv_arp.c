#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#define MAC_ADDR_SIZE 6
#define ETH_FRAM_SIZE 1500
#define PRO_TYPE_IPV4 0
#define PRO_TYPE_IPV6 1
#define PRO_TYPE_ARP 2
#define PRO_TYPE_RARP 3
/**
 *解析协议
 */
int main(int argc,char** argv,char** env){
	//创建原始套接字
	int sfd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	if(sfd == -1)
	{
		perror("create socket error!");
		exit(-1);
	}
/*
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	int bd = bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(bd ==-1)
	{
		perror("bind error");
		close(sfd);
		exit(-1);
	}
	*/
	uint8_t message_buffer[ETH_FRAM_SIZE]={0};
	//原mac地址与目的mac地址
	uint8_t src_mac[MAC_ADDR_SIZE]={0},dst_mac[MAC_ADDR_SIZE]={0};
	//源IP与目的IP地址
	uint8_t src_ip[4],dst_ip[4];
	while(1){
		//获取以太网帧数据
		int recv_len = recvfrom(sfd,message_buffer,sizeof(message_buffer),0,NULL,NULL);
		//2、第二种方法解析源MAC与目的MAC地址
		memcpy(dst_mac,message_buffer,MAC_ADDR_SIZE);
		memcpy(src_mac,message_buffer+6,MAC_ADDR_SIZE);
		//仅拦截arp应答报文
		if(*(uint16_t*)(message_buffer+12) == 0x0608 && *(uint16_t*)(message_buffer+20) == 0x0200){
			printf("arp reply .....\n");
			//解析arp响应报文：
			//发送方mac、ip
			memcpy(src_mac,message_buffer+22,MAC_ADDR_SIZE);
			memcpy(src_ip,message_buffer+28,4);
			printf("ip:[%d.%d.%d.%d]\n",src_ip[0],src_ip[1],src_ip[2],src_ip[3]);
			printf("mac:[%.2x:%.2x:%.2x:%.2x:%.2x:%.2x]\n",src_mac[0],
					src_mac[1],src_mac[2],src_mac[3],src_mac[4],src_mac[5]);
		}
	}
	close(sfd);
	return 0;
}

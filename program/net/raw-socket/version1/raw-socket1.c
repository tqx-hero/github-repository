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
	unsigned char message_buffer[ETH_FRAM_SIZE]={0};
	//原mac地址与目的mac地址
	unsigned char src_mac[MAC_ADDR_SIZE]={0},dst_mac[MAC_ADDR_SIZE]={0};
	//源IP与目的IP地址
	unsigned char src_ip[INET_ADDRSTRLEN],dst_ip[INET_ADDRSTRLEN];
	//上层(网络层)协议类型
	uint16_t pro_type;
	char *pro_type_str;
	void parse_ip_addr(int,void*,void*,void*,int);
	char * trans_type;
	while(1){
		//获取以太网帧数据
		int recv_len = recvfrom(sfd,message_buffer,sizeof(message_buffer),0,NULL,NULL);
		//解析源MAC与目的MAC地址
		memcpy(dst_mac,message_buffer,MAC_ADDR_SIZE);
		memcpy(src_mac,message_buffer+6,MAC_ADDR_SIZE);
		//解析网络层协议类型
		pro_type = ntohs(*(uint16_t*)(message_buffer+12));
		if(pro_type == 0x0800){
			pro_type_str = "IPV4";
			parse_ip_addr(PRO_TYPE_IPV4,(void*)message_buffer,(void*)src_ip,(void*)dst_ip,INET_ADDRSTRLEN);
		}
		else if(pro_type == 0x0806)
			pro_type_str = "ARP";
		else if(pro_type == 0x8035)
			pro_type_str = "RARP";
		else 
			pro_type_str = "undefined";
		printf("协议类型：%s\n",pro_type_str);
		printf("MAC: %x:%x:%x:%x:%x:%x  >>  %x:%x:%x:%x:%x:%x\n",
				src_mac[0],src_mac[1],src_mac[2],src_mac[3],src_mac[4],src_mac[5],
				dst_mac[0],dst_mac[1],dst_mac[2],dst_mac[3],dst_mac[4],dst_mac[5]
				);
		printf("IP: %s >> %s\n",src_ip,dst_ip);
		unsigned char tran_t = *(message_buffer+23);
		if(tran_t == 6)
			trans_type ="TCP";
		else if(tran_t == 17)
			trans_type ="UDP";
		printf("传输层协议: %s\n",trans_type);
	}
	close(sfd);
	return 0;
}
//解析ipv4协议下的ip地址
void parse_by_ipv4(void* frame_buf,void* src_ip,void * dst_ip,int ip_len){
	inet_ntop(AF_INET,((unsigned char*)frame_buf+26),(unsigned char*)src_ip,ip_len);
	inet_ntop(AF_INET,((unsigned char*)frame_buf+30),(unsigned char*)dst_ip,ip_len);
}

//解析IP地址
void parse_ip_addr(int pro_type,void* frame_buf,void* src_ip,void * dst_ip,int ip_len){
	switch (pro_type){
		case PRO_TYPE_IPV4 :
			parse_by_ipv4(frame_buf,src_ip,dst_ip,ip_len);
		break;
		case PRO_TYPE_ARP :
		break;
		default: 
		break;
	}
}


#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>
/**
	接收SYN包
*/
int main(){
	int sfd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_IP));
	if(sfd == -1)
		err(EXIT_FAILURE,"create socket error");
	uint8_t message_buf[1500];
	struct sockaddr_in con_addr;
	//定义协议栈各层指针，解包使用
	struct ether_header* eth_hdr_ptr;
	struct iphdr* ip_header_ptr;
	struct tcphdr* tcp_header_ptr; 
	while(1){
		socklen_t stklen = sizeof(con_addr);
		int recv_len = recvfrom(sfd,message_buf,sizeof(message_buf),0,(struct sockaddr*)&con_addr,&stklen);
		uint8_t ip[INET_ADDRSTRLEN]={0};
		/*
		inet_ntop(AF_INET,&con_addr.sin_addr.s_addr,ip,INET_ADDRSTRLEN);
		printf("ip = %s\n",ip);
		if(strcmp(inet_ntop(AF_INET,&con_addr.sin_addr.s_addr,ip,INET_ADDRSTRLEN),"192.168.1.7"))
			continue;
		*/
		eth_hdr_ptr = (struct ether_header*)message_buf;
		tcp_header_ptr = (struct tcphdr*)(message_buf+34);
		ip_header_ptr = (struct iphdr*)(message_buf+14);
		inet_ntop(AF_INET,&ip_header_ptr->saddr,ip,INET_ADDRSTRLEN);
		//判断是否为tcp协议
		if(strcmp(ip,"192.168.1.7") || ip_header_ptr->protocol == 17 || tcp_header_ptr->th_dport != htons(12000))
			continue;
		printf("拦截到192.168.1.7的tcp数据包\n");
		printf("数据帧长度 = %d\n",recv_len);
		printf("********************IP首部内容************************\n");
		printf("version = %d\n",ip_header_ptr->version);
		printf("首部长度 = %d\n",ip_header_ptr->ihl);
		printf("ip分组总长度 = %d\n",ntohs(ip_header_ptr->tot_len));
		printf("TTL = %d\n",ip_header_ptr->ttl);
		printf("上层协议 = %d\n",ip_header_ptr->protocol);
		printf("源IP = %s\n",inet_ntop(AF_INET,&ip_header_ptr->saddr,ip,INET_ADDRSTRLEN));
		printf("目的IP = %s\n",inet_ntop(AF_INET,&ip_header_ptr->daddr,ip,INET_ADDRSTRLEN));
		printf("********************TCP首部内容************************\n");
		printf("源端口号 = %d\n",ntohs(tcp_header_ptr->th_sport));
		printf("目的端口号 = %d\n",ntohs(tcp_header_ptr->th_dport));
		printf("序列号 = %d\n",ntohl(tcp_header_ptr->th_seq));
		printf("确认序列号 = %d\n",ntohl(tcp_header_ptr->th_ack));
		printf("TCP首部长度 = %d\n",tcp_header_ptr->th_off);
		printf("控制位 = %d\n",tcp_header_ptr->th_flags);
		printf("窗口大小 = %d\n",ntohs(tcp_header_ptr->th_win));
		break;
	}
	close(sfd);
	return 0;
}

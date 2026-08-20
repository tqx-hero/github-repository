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
	uint8_t message_buffer[ETH_FRAM_SIZE]={0};
	//原mac地址与目的mac地址
	uint8_t src_mac[MAC_ADDR_SIZE]={0},dst_mac[MAC_ADDR_SIZE]={0};
	//源IP与目的IP地址
	uint8_t src_ip[INET_ADDRSTRLEN],dst_ip[INET_ADDRSTRLEN];
	//上层(网络层)协议类型
	uint16_t pro_type;
	char *pro_type_str;
	void parse_ip_addr(int,void*,void*,void*,int);
	//传输层协议类型
	char * trans_type;
	uint8_t tran_t;
	//IP首部长度、ip分组长度、传输层数据包总长度、传输层数据载荷长度
	uint32_t ip_head_length,ip_package_length,trans_package_length,trans_payload_legth;
	//源端口与目的端口
	uint16_t src_port,dst_port;
	while(1){
		//获取以太网帧数据
		int recv_len = recvfrom(sfd,message_buffer,sizeof(message_buffer),0,NULL,NULL);
		//2、第二种方法解析源MAC与目的MAC地址
		memcpy(dst_mac,message_buffer,MAC_ADDR_SIZE);
		memcpy(src_mac,message_buffer+6,MAC_ADDR_SIZE);
		//解析网络层协议类型
		pro_type = ntohs(*(uint16_t*)(message_buffer+12));
		//获取IP首部长度
		ip_head_length = ((uint32_t)message_buffer[14] & 0xF) <<2;
		printf("IP首部长度=%d\n",ip_head_length);
		//获取IP分组长度
		ip_package_length = ntohs(*(uint16_t*)(message_buffer+16));
		printf("IP分组总长度=%d\n",ip_package_length);
		//计算传输层数据包总长度：
		trans_package_length = ip_package_length - ip_head_length;
		//获取传输层协议首部起始位置
		int ip_begin_index = 14+ip_head_length;
		//解析2个端口号
		src_port = ntohs(*(uint16_t*)(message_buffer+ip_begin_index));
		dst_port = ntohs(*(uint16_t*)(message_buffer+ip_begin_index+2));
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
		//1、可直接使用内存足够的数组来存放拼接好的MAC地址
		/*
		uint8_t src_mac_buf[18],dst_mac_buf[18];
		sprintf(dst_mac_buf,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",message_buffer[0],message_buffer[1],message_buffer[2],message_buffer[3],
				message_buffer[4],message_buffer[5]);
		sprintf(src_mac_buf,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",message_buffer[6],message_buffer[7],message_buffer[8],message_buffer[9],
				message_buffer[10],message_buffer[11]);
		printf("MAC: %s >> %s\n",src_mac_buf,dst_mac_buf); 
		*/
		//2、也可通过下面方式打印MAC地址，或者使用sprintf将MAC地址组包，以:分隔逐个字符放入一个够大的字符数组中
		printf("MAC: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x  >>  %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
				src_mac[0],src_mac[1],src_mac[2],src_mac[3],src_mac[4],src_mac[5],
				dst_mac[0],dst_mac[1],dst_mac[2],dst_mac[3],dst_mac[4],dst_mac[5]
				);
		printf("IP: [%s:%d] >> [%s:%d]\n",src_ip,src_port,dst_ip,dst_port);
		//获取传输层协议类型(TCP/UDP)，1个字节
		tran_t = message_buffer[23];
		if(tran_t == 0x06){
			trans_type ="TCP";
			//解析TCP首部长度
			uint32_t tcp_header_legth = (message_buffer[ip_begin_index+12] & 0xf0) >> 2;
			printf("TCP首部长度=%d\n",tcp_header_legth);
			//计算传输层数据载荷部分长度：
			trans_payload_legth = trans_package_length - tcp_header_legth;
			printf("应用层数据包总长度：%d\n",trans_package_length);
			//尝试打印应用层数据信息
			//printf("应用层数据：%s\n",message_buffer+ip_begin_index+tcp_header_legth);	
		}
		else if(tran_t == 0x11)
			trans_type ="UDP";
		printf("传输层协议: %s\n",trans_type);
	}
	close(sfd);
	return 0;
}
//解析ipv4协议下的ip地址
void parse_by_ipv4(void* frame_buf,void* src_ip,void * dst_ip,int ip_len){
	inet_ntop(AF_INET,((uint8_t*)frame_buf+26),(uint8_t*)src_ip,ip_len);
	inet_ntop(AF_INET,((uint8_t*)frame_buf+30),(uint8_t*)dst_ip,ip_len);
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


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#define FRAME_MAX_SIZE 1500
#define MAC_ADDR_SIZE 6
#define ARP_PADDING_SIZE 18
#define FRAME_HEADER_SIZE 14
#define FRAME_MIN_PAYLOAD_SIZE 46
/**
 *
 * 发送arp服务请求
 */

int init_arp_data(uint8_t* frame_buffer,uint8_t* src_mac,uint8_t * src_ip,uint8_t* dst_ip,int ip_len);
int init_frame_header(uint8_t* frame_buffer,uint8_t * src_mac_addr);
int main(int argc,char ** argv,char** env){
	//创建原始套接字
	int sfd;
	if((sfd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL))) == -1 ){
		perror("create socket error");
		exit(-1);
	}
	//定义以太网帧
	uint8_t frame_buffer[FRAME_MAX_SIZE];
	uint32_t frame_size = 0;
	//设置要发送的网卡
	struct ifreq ethreq;
	//设置网卡名称
	strncpy(ethreq.ifr_name,"ens33",IFNAMSIZ);
	if(ioctl(sfd,SIOCGIFINDEX,&ethreq) == -1){
		perror("ioctl get interface ethernet index error");
		close(sfd);
		exit(-1);
	}
	//给sock地址结构体设置要发送的网卡index
	struct sockaddr_ll addr;
	bzero(&addr,sizeof(addr));	
	addr.sll_ifindex = ethreq.ifr_ifindex;
	//arp组包
	//获取网卡的mac地址
	if(ioctl(sfd,SIOCGIFHWADDR,&ethreq) == -1){
		perror("get hardware address error");
		exit(-1);
	}
	uint8_t mac_addr[MAC_ADDR_SIZE],src_ip[4];
	memcpy(mac_addr,ethreq.ifr_hwaddr.sa_data,sizeof(mac_addr));
	//获取源IP地址
	if(ioctl(sfd,SIOCGIFADDR,&ethreq) == -1){
		perror("get ip address error");
		exit(-1);
	}
	memcpy(src_ip,&((struct sockaddr_in*)&ethreq.ifr_addr)->sin_addr.s_addr,sizeof(src_ip));
	frame_size+= init_frame_header(frame_buffer,mac_addr);
	//组装网络层-ARP报文
	uint8_t dst_ip[4]={192,168,1,1};
	//inet_pton(AF_INET,"192.168.1.7",dst_ip);
	for(int i=0;i<254;++i){
		int temp_size = frame_size;
		dst_ip[3]+=i;	
		frame_size+= init_arp_data(frame_buffer+temp_size,mac_addr,src_ip,dst_ip,sizeof(src_ip));	
		//发送arp报文
		sendto(sfd,frame_buffer,frame_size,0,(struct sockaddr*)&addr,sizeof(addr));
		frame_size = temp_size;
	}
	return 0;
}
//组装arp协议报文
int init_arp_data(uint8_t* frame_buffer,uint8_t* src_mac,uint8_t * src_ip,uint8_t* dst_ip,int ip_len){
	//硬件类型、协议类型、Mac长度、ip长度、src_mac,src_ip,dst_mac,dst_ip,padding
	*(uint16_t*)frame_buffer = htons(0x0001); // 2B
	frame_buffer+=2;
	//协议类型IP	
	*(uint16_t*)frame_buffer = htons(0x0800); //2B
	frame_buffer+=2;
	//mac长度，1B
	*frame_buffer = 0x06;
	//ip长度1B
	frame_buffer[1] =0x04;
	frame_buffer+=2;
	//op:1、发送arp请求；2、应答arp；3、发送rarp请求；4、应答rarp
	*(uint16_t*)frame_buffer = htons(0x0001);
	frame_buffer+=2;
	//组装源mac、源IP
	memcpy(frame_buffer,src_mac,MAC_ADDR_SIZE);
	frame_buffer+=MAC_ADDR_SIZE;
	memcpy(frame_buffer,src_ip,ip_len);
	frame_buffer+=ip_len;
	//目的mac、ip
	memset(frame_buffer,0x00,MAC_ADDR_SIZE);
	frame_buffer+=MAC_ADDR_SIZE;
	memcpy(frame_buffer,dst_ip,ip_len);
	frame_buffer+=ip_len;
	//填充18个字节0
	memset(frame_buffer,0x00,ARP_PADDING_SIZE);
	return FRAME_MIN_PAYLOAD_SIZE;	
}

//组装以太网帧头部
int init_frame_header(uint8_t* frame_buffer,uint8_t * src_mac_addr){
	//设置以太网帧头部：dst_mac,src_mac,type
	memset(frame_buffer,0xff,MAC_ADDR_SIZE); //6 byte
	memcpy(frame_buffer+MAC_ADDR_SIZE,src_mac_addr,MAC_ADDR_SIZE); //6 byte
	*(uint16_t*)(frame_buffer+12) = htons(0x0806); //2 byte
	return FRAME_HEADER_SIZE;
}


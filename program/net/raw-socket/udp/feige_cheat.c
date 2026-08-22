#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#define FRAME_MAX_SIZE 1500
#define MAC_ADDR_SIZE 6
#define IPV4_SIZE 4
/**
 *飞鸽欺骗报文
 */
void perror_exit(const char* message);
uint32_t build_app_package(uint8_t* app_buffer,uint8_t* message);
void close_exit(const char*,int);
int build_ipv4_package(uint8_t* dst_buffer,uint8_t* src_ip,uint8_t* dst_ip,uint8_t super_protocol,uint16_t super_protocol_max_size);
int build_frame_header(uint8_t* dst_buffer,uint8_t* src_mac,uint8_t* dst_mac,uint16_t len,uint16_t super_type);
uint32_t build_trans_udp_package(uint8_t* buffer,uint32_t message_size,uint16_t src_port,uint16_t dst_port,uint8_t* src_ip,uint8_t* dst_ip);
int main(int argc,char** argv,char ** env){
	if(argc == 1)
		perror_exit("请输入要传输的内容!");
	int sfd ;
       	if((sfd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL))) == -1)
		perror_exit("create socket error");
	//伪装的：ip : 192.168.1.105 mac: 00:d8:61:70:fd:45
	//目的：ip : 192.168.1.7 mac: 8C-32-23-0F-EA-D5
	uint8_t message_buffer[FRAME_MAX_SIZE]={0},
		src_mac[MAC_ADDR_SIZE]={0x00,0xd8,0x61,0x70,0xfd,0x45}, //伪装105的mac地址 
		dst_mac[MAC_ADDR_SIZE] ={0x8c,0x32,0x23,0x0f,0xea,0xd5}, // 目的mac地址
		src_ip[IPV4_SIZE] = {192,168,1,105},			//伪装的ip地址
		dst_ip[IPV4_SIZE] = {192,168,1,7};			//目的ip
	struct ifreq req;
	strncpy(req.ifr_name,"ens33",IFNAMSIZ);
	//获取自身的mac地址、ip地址
	/*
	//uint8_t* ip_str ="192.168.1.7";
	//inet_pton(AF_INET,ip_str,dst_ip);
	if(ioctl(sfd,SIOCGIFHWADDR,&req) == -1)
		close_exit("get hd addr error",sfd);
	memcpy(src_mac,req.ifr_hwaddr.sa_data,MAC_ADDR_SIZE);
	if(ioctl(sfd,SIOCGIFADDR,&req) == -1)
		close_exit("get ip addr error",sfd);
	memcpy(src_ip,&((struct sockaddr_in*)&req.ifr_addr)->sin_addr.s_addr,IPV4_SIZE);
	printf("源：[%d.%d.%d.%d] >> [%.2x:%.2x:%.2x:%.2x:%.2x:%.2x]\n",src_ip[0],src_ip[1],src_ip[2],src_ip[3], 
			src_mac[0],src_mac[1],src_mac[2],src_mac[3],src_mac[4],src_mac[5]);
	printf("目的：[%d.%d.%d.%d] >> [%.2x:%.2x:%.2x:%.2x:%.2x:%.2x]\n",dst_ip[0],dst_ip[1],dst_ip[2],dst_ip[3],
			dst_mac[0],dst_mac[1],dst_mac[2],dst_mac[3],dst_mac[4],dst_mac[5]);
	*/
	//组装帧头
	build_frame_header(message_buffer,src_mac,dst_mac,MAC_ADDR_SIZE,0x0800);
	//组装应用层
	uint32_t app_level_size = build_app_package(message_buffer+42,argv[1]);
	//组装传输层
	build_trans_udp_package(message_buffer+34,app_level_size,2425,2425,src_ip,dst_ip);
	//组ip头部
	build_ipv4_package(message_buffer+14,src_ip,dst_ip,0x11,8+app_level_size);
	struct sockaddr_ll addr;
	bzero(&addr,sizeof(addr));
	//获取自身的网卡index
	if(ioctl(sfd,SIOCGIFINDEX,&req)	==-1)
		close_exit("get hardware index error!",sfd);
	addr.sll_ifindex = req.ifr_ifindex;
	int total_size = 42 + app_level_size;
	if(total_size <60)
		total_size =60;
	sendto(sfd,message_buffer,total_size,0,(struct sockaddr*)&addr,sizeof(addr));	
	close(sfd);
	return 0;
}
//计算校验和
uint16_t check_sum(uint8_t* target,uint32_t target_size){
 	uint32_t sum = 0;
    	uint32_t i = 0;
   	 // 按大端序拼接16位字累加
   	while (i + 1 < target_size) {
		uint16_t word = (target[i] << 8) | target[i + 1];
		sum += word;
		i += 2;	
    	}
    	// 处理剩余单字节：高8位放数据，低8位补0
	if (i < target_size)
        	sum += (target[i]) << 8;
    	// 循环折叠进位，直到没有高位溢出
    	while (sum >> 16)
        	sum = (sum & 0xFFFF) + (sum >> 16);
	return (uint16_t)(~sum);
}

uint32_t build_fake_header_udp(uint8_t* fake_header,uint8_t * src_ip,uint8_t* dst_ip,uint16_t udp_packet_size){
	memcpy(fake_header,src_ip,IPV4_SIZE);
	memcpy(fake_header+4,dst_ip,IPV4_SIZE);
	fake_header[9] = 17;
	*(uint16_t*)(fake_header+10) = udp_packet_size;
	return 12;	
}

//组装传输层udp协议
uint32_t build_trans_udp_package(uint8_t* buffer,uint32_t message_size,uint16_t src_port,uint16_t dst_port,uint8_t* src_ip,uint8_t* dst_ip){
	*(uint16_t*)buffer = htons(src_port);
	*(uint16_t*)(buffer+2) = htons(dst_port);
	//udp包总长度 = 8+应用层数据包长度
	uint16_t udp_package_size = htons(8+message_size);
	*(uint16_t*)(buffer+4) = udp_package_size;
	//计算校验和
	//拼装伪首部:12B
	//源IP(4)、目的IP(4)、填充(1B)、协议号17(1B)、UDP包长度(2B)
	uint8_t fake_header[1500]={0};
	build_fake_header_udp(fake_header,src_ip,dst_ip,udp_package_size);
	memcpy(fake_header+12,buffer,8+message_size);
	*(uint16_t*)(buffer+6) = htons(check_sum(fake_header,20+message_size));
	return 8+message_size;
}

//组装应用层飞鸽协议
//协议：包号码：发送方名称：发送方主机：关键字32(文本):数据内容\0
uint32_t build_app_package(uint8_t* app_buffer,uint8_t* message){
	return  sprintf(app_buffer,"%d:%d:%s:%s:%d:%s%c",1,30,"tqx2","CH-202606031224",32,message,0);	
}

//组ipv4头部
int build_ipv4_package(uint8_t* dst_buffer,uint8_t* src_ip,uint8_t* dst_ip,uint8_t super_protocol,uint16_t super_protocol_max_size){
	//版本4、首部长度20
	dst_buffer[0] = 0x45;
	//服务区分默认为0，不需要填
	//总长度：为ip头长度+上层数据报长度(数据载荷)
	*(uint16_t*)&dst_buffer[2] = htons(20+super_protocol_max_size);
	//标识
	dst_buffer[5] = 0x01;
	//flags与片偏移在udp中默认为0即可
	//TTL写64
	dst_buffer[8] = 64;
	dst_buffer[9] = super_protocol;
	//源ip、目的ip
	memcpy(dst_buffer+12,src_ip,IPV4_SIZE);
	memcpy(dst_buffer+16,dst_ip,IPV4_SIZE);
	//头部校验和,把头部组装完成后计算
	*(uint16_t*)(dst_buffer+10) = htons(check_sum(dst_buffer,20));
	return 20;
}

//组帧头
int build_frame_header(uint8_t* dst_buffer,uint8_t* src_mac,uint8_t* dst_mac,uint16_t len,uint16_t super_protocol){
	memcpy(dst_buffer,dst_mac,len);
	memcpy(dst_buffer+len,src_mac,len);
	*(uint16_t*)(dst_buffer+2*len) = htons(super_protocol);
	return 14;
}

void perror_exit(const char* message)
{
	perror(message);
	exit(-1);
}

void close_exit(const char* message,int fd){
	close(fd);
	perror_exit(message);
}

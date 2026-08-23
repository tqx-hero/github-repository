#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <netpacket/packet.h>
#define FRAME_MAX_SIZE 1500
#define SRC_PORT 12000
#define DST_PORT 12000
#define FLAG_SYN 2
#define FLAG_FIN 1
#define FLAG_ACK 16
/**

组包TCP的SYN请求:进行连接请求
*/

void perror_exit(const char* message);
void perror_close_exit(const char* message,int fd);
uint16_t check_sum(uint8_t* target,int target_size);
int main(int argc,char ** argv,char ** env){
	//创建socket
	int sfd;
	if((sfd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL))) == -1)
		perror_exit("create socket error");
	//组包
	uint8_t message_buf[FRAME_MAX_SIZE]={
		/*************数据链路层部分******************/
		0x8c,0x32,0x23,0x0f,0xea,0xd5,	//目的mac: 8c:32:23:0f:ea:d5
		0x00,0x00,0x00,0x00,0x00,0x00,	//源mac
		0x08,0x00,			//类型ip：0x0800
		/*******************网络层部分****************************/
		0x45,0x00,0x00,0x00,		//版本号+首部长度1B、服务区分1B、总长度2B
		0x00,0x01,0x00,0x00,		//分组的标识2B，flag、片偏移2B
		0x40,0x06,0x00,0x00,		//TTL1B、协议类型1B、首部校验和2B
		0x00,0x00,0x00,0x00,		//源IP
		192,168,1,7,			//目的IP
		/********************传输层部分(TCP)***************************/
		0x00,0x00,0x00,0x00,		//源端口号、目标端口号
		0x00,0x00,0x00,0x01,		//序列号seq 4B
		0x00,0x00,0x00,0x00,		//确认序列号ack 4B
		0x50,0x00,0x00,0x00,		//数据偏移(首部长度，无附加选项为20)+保留1B、控制位Flag 1B、窗口大小2B
		0x00,0x00,0x00,0x00		//校验和(首部+数据载荷)2B、紧急指针2B
		//应用层部分
	};
	
	struct ifreq req;
	memcpy(&req.ifr_name,"ens33",IFNAMSIZ);
	//获取源mac地址
	if(ioctl(sfd,SIOCGIFHWADDR,&req) == -1)
		perror_close_exit("get hw addr error",sfd);
	memcpy(message_buf+6,req.ifr_hwaddr.sa_data,6);
	//设置源IP地址
	if(ioctl(sfd,SIOCGIFADDR,&req) == -1)
		perror_close_exit("get addr error",sfd);
	memcpy(message_buf+26,&((struct sockaddr_in*)&req.ifr_addr)->sin_addr.s_addr,4);
	//TCP连接请求，传输层数据载荷为0
	//所以IP层的包总长度为20+20 = 40
	*(uint16_t*)(message_buf+16) = htons(40);
	//计算IP首部校验和
	*(uint16_t*)(message_buf+24) = htons(check_sum(message_buf+14,20));
	
	//设置源、目的端口
	*(uint16_t*)(message_buf+34) = htons(SRC_PORT);
	*(uint16_t*)(message_buf+36) = htons(DST_PORT);
	//设置控制位Flag SYN=1、窗口大小为60000
	message_buf[47] = FLAG_SYN;
	*(uint16_t*)(message_buf+48) = htons(60000);
	//计算TCP层校验和
	//封装伪首部
	uint8_t fake_header[1024]={
		//源IP、目的IP、1字节填充0、协议类型tcp=6、tcp包长20
		192,168,1,178,
		192,168,1,7,
		0x00,0x06,0x00,0x14
	};
	memcpy(fake_header+12,message_buf+34,20);
	*(uint16_t*)(message_buf+50) =  htons(check_sum(fake_header,12+20));	
	//发送
	struct sockaddr_ll addr;
	bzero(&addr,sizeof(addr));
	//设置要发送的网卡的index
	if(ioctl(sfd,SIOCGIFINDEX,&req) == -1)
		perror_close_exit("get hw index error",sfd);
	addr.sll_ifindex = req.ifr_ifindex;
	bzero(message_buf+54,6);
	sendto(sfd,message_buf,60,0,(struct sockaddr*)&addr,sizeof(addr));
	return 0;
}

uint16_t check_sum(uint8_t* target,int target_size){
	uint32_t sum=0;
	while(target_size >1){
		sum+= ((uint16_t)target[0] <<8 | target[1]);
		target +=2;
		target_size -=2;
	}
	if(target_size)
		sum += (uint16_t)target[0] <<8;
	//处理最高位的进位
	while(sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);
	return ~(uint16_t)sum;
}


void perror_exit(const char* message){
	perror(message);
	exit(-1);
}

void perror_close_exit(const char* message,int fd){
	close(fd);
	perror_exit(message);
}

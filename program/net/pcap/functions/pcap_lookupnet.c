#include <pcap/pcap.h>
#include <string.h>
#include <stdlib.h> 
/**
	pcap_lookupnet函数
	用于搜索网卡的网段与子网掩码
	       #include <pcap/pcap.h>

       char errbuf[PCAP_ERRBUF_SIZE];

       int pcap_lookupnet(const char *device, bpf_u_int32 *netp,
               bpf_u_int32 *maskp, char *errbuf);
	参数：
		device:设备名
		netp:存放网段的指针
		maskp:存放子网掩码的指针
		errbuf:出现错误时的错误信息
*/
int main(){
	//先用pcap_lookupdev等函数获取网卡名称
	char errbuf[PCAP_ERRBUF_SIZE];
	char * dev_name = pcap_lookupdev(errbuf);
	if(!dev_name)
		exit(-1);
	bpf_u_int32 netp,maskp;
	int ret = pcap_lookupnet(dev_name,&netp,&maskp,errbuf);
	if(ret == PCAP_ERROR){
		printf("error:%s\n",errbuf);
		return -1;
	}
	//获取网卡的网段与子网掩码
	uint8_t * net_addr = (uint8_t*) &netp,*net_mask = (uint8_t*)&maskp;
	printf("net addr:%d.%d.%d.%d\n",net_addr[0],net_addr[1],net_addr[2],net_addr[3]);
	printf("mask :%d.%d.%d.%d\n",net_mask[0],net_mask[1],net_mask[2],net_mask[3]);
	return 0;
}

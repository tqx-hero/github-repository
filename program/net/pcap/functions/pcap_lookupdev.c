#include <pcap/pcap.h>
#include <string.h>
#include <stdlib.h> 
/**
	pcap_looupdev用法:返回第一个可用的网卡。
	仅仅返回第一个，如果有多个网卡可用，无法满足条件。
	所以该函数已经被pcap_findalldevs淘汰。
	后者可以返回所有可用的网络设备，自行筛选即可
*/
int main(){
	//pcap_lookupdev的使用
	char errbuf[PCAP_ERRBUF_SIZE];
	char * dev_ptr = pcap_lookupdev(errbuf);
	if(dev_ptr)
		printf("dev:%s\n",dev_ptr);
	return 0;
}

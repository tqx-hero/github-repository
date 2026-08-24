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
	/*
	//pcap_findalldevs函数的使用
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t* head;
	int ret = pcap_findalldevs(&head,errbuf);
	if(ret == PCAP_ERROR){
		printf("find all devs failure: %s\n",errbuf);
		exit(-1);
	}
	while(head){
		printf("name:%s description:%s flag:%d\n",head->name,head->description,head->flags);
		if(head->addresses){
			char ip_addr[INET_ADDRSTRLEN]; 
			inet_ntop(AF_INET,&((struct sockaddr_in*)head->addresses->addr)->sin_addr.s_addr,ip_addr,INET_ADDRSTRLEN);
			printf("ip : %s\n",ip_addr);
		}
		head = head->next;
	}
	pcap_freealldevs(head);
	*/
	//pcap_lookupdev的使用
	char errbuf[PCAP_ERRBUF_SIZE];
	char * dev_ptr = pcap_lookupdev(errbuf);
	if(dev_ptr)
		printf("dev:%s\n",dev_ptr);
	return 0;
}

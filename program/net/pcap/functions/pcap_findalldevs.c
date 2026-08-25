#include <pcap/pcap.h>
#include <string.h>
#include <stdlib.h> 
/**
	pcap_findalldevs
	//查找所有可用的网络设备，以链表的形式返回它们各自的信息
#include <pcap/pcap.h>
char errbuf[PCAP_ERRBUF_SIZE];
int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf);
//释放malloc申请的链表节点。与上面的find函数配套使用，避免内存泄漏
void pcap_freealldevs(pcap_if_t *alldevs);
*/
int main(){
	
	//pcap_findalldevs函数的使用
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t root,*head = &root;
	int ret = pcap_findalldevs(&head,errbuf);
	if(ret == PCAP_ERROR){
		printf("find all devs failure: %s\n",errbuf);
		exit(-1);
	}
	//过滤掉回环地址127与断开连接的
	bpf_u_int32 flag = PCAP_IF_LOOPBACK | PCAP_IF_CONNECTION_STATUS_DISCONNECTED;
	while(head && !(head->flags & flag)){
		printf("name:%s description:%s flag:%d\n",head->name,head->description,head->flags);
		while(head->addresses){
			char ip_addr[INET_ADDRSTRLEN],netmask_addr[INET_ADDRSTRLEN];
			uint32_t ip = ((struct sockaddr_in*)head->addresses->addr)->sin_addr.s_addr;
			struct sockaddr* netmask = head->addresses->netmask;
			if(!ip || !netmask) 
				goto goto_next;
			inet_ntop(AF_INET,&ip,ip_addr,INET_ADDRSTRLEN);
			printf("ip : %s\n",ip_addr);
			inet_ntop(AF_INET,&((struct sockaddr_in*)netmask)->sin_addr.s_addr,ip_addr,INET_ADDRSTRLEN);
			printf("子网掩码 : %s\n",ip_addr);
		goto_next:
			head->addresses = head->addresses->next;
		}
		head = head->next;
	}
	pcap_freealldevs(head);

	return 0;
}

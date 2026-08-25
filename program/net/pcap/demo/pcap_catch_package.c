#include <net/ethernet.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <pcap/pcap.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#define DEV_NAME_SIZE 10
#define DEV_MAX_SIZE 5
#define FAIL_BUF_SIZE 32
#define SNAP_LEN 1518
#define NO_PROMISC 0
#define IS_PROMISC 1
#define TIME_TO_WAIT 0
/**
	使用pcap API进行抓包
*/

typedef struct {
	uint32_t ip_addr,netmask_addr;
	uint8_t dev_name[DEV_NAME_SIZE];
} my_netdev_ipv4_t;

int get_netdev_info(pcap_if_t* head,my_netdev_ipv4_t* netinfo,int dev_size,char* errbuf);
void process_package(u_char* arg,const struct pcap_pkthdr* package_additional,const u_char* package_info);

int main(int argc,char** argv,char** env){
	//使用pcap_findalldevs函数获取可用的网卡名称、ip、子网掩码
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *root = NULL;
	struct bpf_program* bfp_ptr =NULL;
	pcap_t* pcap_handle = NULL;
	int state = pcap_findalldevs(&root,errbuf);
	if(state == PCAP_ERROR){
		perror(errbuf);
		goto close_resource;
	}
	my_netdev_ipv4_t dev_arr[DEV_MAX_SIZE];
	int cnt;
	if((cnt = get_netdev_info(root,dev_arr,DEV_MAX_SIZE,errbuf)) == -1){
		perror(errbuf);
		goto close_resource;
	}
	if(!cnt){
		perror("无可用设备");
		goto close_resource;
	}
	//为了简单起见，这里只取第一个网卡
	my_netdev_ipv4_t cur_dev = dev_arr[0];
	//pcap_freealldevs释放pcap_findalldevs返回链表的内存
	pcap_freealldevs(root);
	root = NULL;
	//使用pcap_open_live函数打开该网卡设备
	pcap_handle = pcap_open_live(cur_dev.dev_name,SNAP_LEN,IS_PROMISC,TIME_TO_WAIT,errbuf);
	if(!pcap_handle){
		perror(errbuf);
		goto close_resource;
	}
	printf("devname = %s\n",cur_dev.dev_name);
	printf("dev netmask = 0x%08x\n",cur_dev.netmask_addr);
	//pcap_compile编译过滤器规则
	struct bpf_program bfp;
	bfp_ptr = &bfp;
	const char* rule_str = ""; 
	//const char* rule_str = "tcp and src host 192.168.1.7"; 
	if(pcap_compile(pcap_handle,bfp_ptr,rule_str,0,ntohl(cur_dev.netmask_addr)) == -1){
		perror(pcap_geterr(pcap_handle));
		goto close_resource;
	}
	//pcap_setfilter设置过滤器规则
	if(pcap_setfilter(pcap_handle,bfp_ptr) == PCAP_ERROR){
		perror(pcap_geterr(pcap_handle));
		goto close_resource;
	}
	if(pcap_datalink(pcap_handle) != DLT_EN10MB)
		goto close_resource;
	//pcap_loop循环监听网卡收包，并进行相关函数回调
	printf("begin loop ....\n");	
	if(pcap_loop(pcap_handle,-1,process_package,NULL) == -1){
		perror(pcap_geterr(pcap_handle));
		goto close_resource;
	}
	//关闭相关资源
close_resource:
	if(root)
		pcap_freealldevs(root);
	//释放过滤器的内存
	if(bfp_ptr)
		pcap_freecode(bfp_ptr);
	//关闭文件句柄
	if(pcap_handle)
		pcap_close(pcap_handle);
	return 0;
}

char* super_protocol(uint16_t type){
	char * ret=NULL;
	switch(type){
		case 0x0800:
			ret = "IPV4";
			break;
		case 0x0806:
			ret = "ARP";
			break;
		case 0x8035:
			ret = "RARP";
			break;
		case 0x86dd:
			ret = "IPV6";
			break;
		default:
			break;	
	}
	return ret;
}


void printf_udp(const u_char* message){
	struct udphdr* udp_ptr = (struct udphdr*)message;
	printf("port : %d >> %d\n",ntohs(udp_ptr->uh_sport),ntohs(udp_ptr->uh_dport));
	printf("udp包总长度：%d\n",ntohs(udp_ptr->uh_ulen));
} 


void printf_tcp(const u_char* message){	
	struct tcphdr* tcp_header_ptr =(struct tcphdr*) message;
	printf("源端口号 = %d\n",ntohs(tcp_header_ptr->th_sport));
        printf("目的端口号 = %d\n",ntohs(tcp_header_ptr->th_dport));
        printf("序列号 = %lu\n",(ulong)ntohl(tcp_header_ptr->th_seq));
        printf("确认序列号 = %lu\n",(ulong)ntohl(tcp_header_ptr->th_ack));
        printf("TCP首部长度 = %d\n",tcp_header_ptr->th_off);
        printf("控制位 = %d\n",tcp_header_ptr->th_flags);
        printf("窗口大小 = %d\n",ntohs(tcp_header_ptr->th_win));
} 

//pcap捕获包之后的回调函数
void process_package(u_char* arg,const struct pcap_pkthdr* package_additional,const u_char* package_info){
	//获取包长：
	uint32_t package_len = package_additional->caplen;
	uint8_t src_ip[INET_ADDRSTRLEN],dst_ip[INET_ADDRSTRLEN];
	printf("包长cap_len=%d\n",package_len);	
	//打印帧的基本信息：
	struct ether_header* ethp;
	struct iphdr* iphp;
	ethp = (struct ether_header*) package_info;
	//if(ethp->ether_type != 0x0008)
	//	return;
	iphp = (struct iphdr*)(package_info+14);
	//先仅处理tcp协议：
	printf("mac: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x  >>  %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
		ethp->ether_shost[0],ethp->ether_shost[1],ethp->ether_shost[2],ethp->ether_shost[3],ethp->ether_shost[4],ethp->ether_shost[5],
		ethp->ether_dhost[0],ethp->ether_dhost[1],ethp->ether_dhost[2],ethp->ether_dhost[3],ethp->ether_dhost[4],ethp->ether_dhost[5]);
	printf("网络层协议：%s\n",super_protocol(ntohs(ethp->ether_type)));
	printf("version = %d\n",iphp->version);
        printf("首部长度 = %d\n",iphp->ihl);
      	printf("ip分组总长度 = %d\n",ntohs(iphp->tot_len));
        printf("TTL = %d\n",iphp->ttl);
        printf("上层协议 = %d\n",iphp->protocol);
        printf("IP = %s  >>  %s\n",inet_ntop(AF_INET,&iphp->saddr,src_ip,INET_ADDRSTRLEN),inet_ntop(AF_INET,&iphp->daddr,dst_ip,INET_ADDRSTRLEN));
	if(iphp->protocol == 0x11)
		printf_udp(package_info+34);
	else if(iphp->protocol == 0x06)
		printf_tcp(package_info+34);
}
//获取网络设备的相关信息
int get_netdev_info(pcap_if_t* head,my_netdev_ipv4_t* netinfo,int dev_size,char* errbuf){
	char* message;
	//参数正确性校验
	if(!dev_size){
		message = "dev_size can not be empty!";
		goto failure_exit;
	}
	if(!head){
		message = "no available net dev!";
		goto failure_exit;
	}
	if(!netinfo){
		message = "net dev arr address invalid!";
		goto failure_exit;
	}
	bzero(netinfo,dev_size*sizeof(my_netdev_ipv4_t));
	int cnt =0;
	//过滤掉回环地址127与断开连接的
	bpf_u_int32 flag = PCAP_IF_LOOPBACK | PCAP_IF_CONNECTION_STATUS_DISCONNECTED;
        while(head && !(head->flags & flag) && cnt < dev_size){
		struct pcap_addr* haddr = head->addresses;
                while(haddr && haddr->addr->sa_family == AF_INET){
                        uint32_t ip = ((struct sockaddr_in*)haddr->addr)->sin_addr.s_addr;
                        struct sockaddr* netmask = haddr->netmask;
                        if(!ip || !netmask)
                                goto goto_next;
        		char ip_addr[INET_ADDRSTRLEN],netmask_addr[INET_ADDRSTRLEN];
                        netinfo[cnt].ip_addr = ip;
			netinfo[cnt].netmask_addr =((struct sockaddr_in*)netmask)->sin_addr.s_addr;
			break;
                goto_next:
                        haddr = haddr->next;
                }
		if(!netinfo[cnt].ip_addr)
			strcpy(netinfo[cnt++].dev_name,head->name);
                head = head->next;
        }
	return cnt;	
   failure_exit:
		strcpy(errbuf,message);
		return -1;
}

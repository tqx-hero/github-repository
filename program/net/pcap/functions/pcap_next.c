#include <pcap/pcap.h>
#include <stdlib.h>
/*
201 struct pcap_pkthdr {
202         struct timeval ts;      
203         bpf_u_int32 caplen;    
204         bpf_u_int32 len;      
205 };
*/
int main(){
	char errbuf[PCAP_ERRBUF_SIZE];
	char * dev_name = pcap_lookupdev(errbuf);
	pcap_t * pt = pcap_open_live(dev_name,1500,0,0,errbuf);	
	if(!pt)
	{
		perror("open live dev error");
		return -1;
	}
	struct pcap_pkthdr pkt;
	const uint8_t * message = pcap_next(pt,&pkt);
	if(message){
		//打印它的信息
		printf("caplen = %d\n",pkt.caplen);
		printf("len = %d\n",pkt.len);
		printf("message = %s\n",message);
	}
	return 0;
}

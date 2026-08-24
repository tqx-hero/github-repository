#include <pcap/pcap.h>
#include <string.h>
#include <stdlib.h> 
/**
	pcap_open_live函数
	打开一个用于捕获数据的网络接口(存活的)
	 pcap_t *pcap_open_live(const char *device, int snaplen,
               int promisc, int to_ms, char *errbuf);
	参数：
		device : 设备名称
		snaplen:捕获数据包的长度
		promisc:是否是混杂模式。1、是；0、不是
		to_ms:等待数据包的超时时间。如果设置为0，阻塞等待直到数据包被捕获到
		errbuf:存放出错时的错误信息
	返回值：
		返回一个pcap_t句柄指针，该句柄相当于文件描述符，对开发人员不透明
*/
int main(){
	//先用pcap_lookupdev等函数获取网卡名称
	char errbuf[PCAP_ERRBUF_SIZE];
	char * dev_name = pcap_lookupdev(errbuf);
	if(dev_name)
		printf("dev_name:%s\n",dev_name);
	pcap_t* pt =  pcap_open_live(dev_name,1500,0,0,errbuf);
	return 0;
}

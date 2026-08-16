#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <err.h>
#include <stdio.h>
////////TFTP数据包操作码
#define TFTP_DATA 0x03  	//数据包
#define TFTP_RD 0x01	//读取/下载文件
#define TFTP_WR 0x02	//写入/上传文件
#define TFTP_ACK 0x04	//确认包
#define TFTP_ERROR 0x05	//错误包
#define TFTP_OACK 0x06	//对选项的确认
#define TFTP_ACKO 0x00	//对选项确认包的确认
int main(){
	int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd ==-1)
		err(EXIT_FAILURE,"socket");
	struct sockaddr_in addr;
	char ip[] = "192.168.1.7";
	addr.sin_family = AF_INET;
	addr.sin_port = htons(69);
	inet_pton(AF_INET,ip,&addr.sin_addr.s_addr);
	
	//if(bind(sock_fd,(struct sockaddr *)&addr,sizeof(addr)) == -1)
	//	err(EXIT_FAILURE,"bind");
	//开始拼装数据包
	//1、打开或创建一个文件,准备以输出流形式写入
	//2、拼装数据包，告诉服务器需要下载的文件名
	//3、读取服务器发送的报文并解析，如果是数据包，读入缓存，读入完成写入文件
	//4、回送确认报文给服务器。	
	//5、继续循环，直到接收到的数据长度小于规定的长度，发送完确认报文后结束
	char file_path[] ="./test.txt",*transformat = "octet";
	FILE * fl_ptr =  fopen(file_path,"w");
	if(!fl_ptr)
		err(EXIT_FAILURE,"open file");
	//拼装请求数据的报文：
	char buffer[1024]={0};
	int len = sprintf(buffer,"%c%c%s%c%s%c",0x00,TFTP_RD,"test.txt",0x00,transformat,0x00);
	int send_size = sendto(sock_fd,buffer,len,0,(struct sockaddr *)&addr,sizeof(addr));
	if(send_size <0)
		err(EXIT_FAILURE,"sendto");
	socklen_t sklen = sizeof(addr);
	while(1){
		int recv_len = recvfrom(sock_fd,buffer,sizeof(buffer),0,(struct sockaddr *)&addr,&sklen);
		if(recv_len <=0)
			break;
		//对数据包进行解读
		uint16_t  op = ntohs(*(uint16_t*)buffer);
		//操作码等于3,则为数据包，将数据部分放入文件中
		if(op == TFTP_DATA){
			uint16_t block_num = *(uint16_t*)(buffer+2);
			fwrite(buffer+4,sizeof(char),recv_len-4,fl_ptr);
			//开始拼装ack数据包
			*(uint16_t*)buffer = htons(TFTP_ACK);
			*(uint16_t*)(buffer+2) = block_num;
			sendto(sock_fd,buffer,4,0,(struct sockaddr * ) &addr,sizeof(addr));
		}else if(op == TFTP_ERROR){
			printf("%s\n",buffer+4);
			break;
		}

		if(recv_len-4 <512)
			break;
	}
	fclose(fl_ptr);
	close(sock_fd);
	return 0;
}

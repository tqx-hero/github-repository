#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
//create UDP SOCKET
int main(){
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	inet_pton(AF_INET,"192.168.1.178",&server_addr.sin_addr.s_addr);
	int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(sock_fd <0)
		perror("fail!");
	while(1){
		char buf[128]="";
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1]=0;
		sendto(sock_fd,buf,strlen(buf),0,(struct sockaddr *) &server_addr,sizeof(server_addr));
		char revieve_buf[128];
		recvfrom(sock_fd,revieve_buf,sizeof(revieve_buf),
				0,NULL,NULL);
		printf("%s\n",revieve_buf);
	
	}
	return 0;
}

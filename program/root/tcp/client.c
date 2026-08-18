#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
/**
 *创建tcp链接的客户端
 */
int main(int argc,char* argv[],char* env[]){
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd ==-1)
		err(EXIT_FAILURE,"socket");
	char *server_ip = "192.168.1.178";
	struct sockaddr_in addr,local_addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = inet_addr(server_ip);
	//测试：绑定端口连接相同的服务端，在服务端强制关闭后能不能直接再次连接
	//经过测试：如果服务端开启端口复用情况下，上述状况出现时可以直接连接，
	//而不需要在等待四次挥手结束后的time_wait状态结束
	bzero(&local_addr,sizeof(local_addr));
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(12222);
	bind(sfd,(struct sockaddr*)&local_addr,sizeof(local_addr));
	//-----------------------------------------------------
	int con_status = connect(sfd,(struct sockaddr *)&addr,sizeof(addr));	
	if(con_status == -1)
		err(EXIT_FAILURE,"connect");
	//连接成功，可以互相通信
	char cache_buf[1024]={0};
	while(1){
		fgets(cache_buf,sizeof(cache_buf),stdin);
		cache_buf[strlen(cache_buf)-1]=0;
		write(sfd,cache_buf,strlen(cache_buf));
		//读取数据
		int read_len = read(sfd,cache_buf,sizeof(cache_buf));
		if(read_len ==0){
			printf("链接已关闭\n");
			break;
		}
		cache_buf[read_len]='\0';
		printf("%s\n",cache_buf);
	}
	close(sfd);
	return 0;
}

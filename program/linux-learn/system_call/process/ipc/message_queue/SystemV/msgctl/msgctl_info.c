#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//msgctl()获取消息队列的属性MSG_INFO
int main(){
	struct msginfo info;
	if(msgctl(1,MSG_INFO,(struct msqid_ds*)&info) == -1){
		perror("ipc stat msg error");
		exit(-1);
	}
	printf("获取成功\n");
	return 0;
}

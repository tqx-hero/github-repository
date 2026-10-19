#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//msgctl()获取消息队列的属性
int main(){
	struct msqid_ds msd;
	if(msgctl(1,IPC_STAT,&msd) == -1){
		perror("ipc stat msg error");
		exit(-1);
	}
	printf("获取成功\n");
	return 0;
}

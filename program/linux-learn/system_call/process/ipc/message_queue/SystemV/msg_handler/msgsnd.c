#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include "msg_t.h"
//msgsnd()发送消息
//argv[1]为要发送的消息类型
int main(int argc,char** argv){
	if(argc < 2){
		fprintf(stderr,"请输入发送消息的类型\n");
		exit(-1);
	}
	//生成消息队列的key
	key_t kt = ftok("./",1);
	if(kt == -1){
		perror("ftok error");
		exit(-1);
	}
	char* kptr = (char*) &kt;
	fprintf(stdout,"消息队列的key = %.2x%.2x%.2x%.2x\n",kptr[3],kptr[2],kptr[1],kptr[0]);
	//创建/获取消息队列id
	int msg_id = msgget(kt,IPC_CREAT | 0666);
	if(msg_id == -1){
		perror("msgget error");
		exit(-1);
	}
	printf("消息队列ID = %d\n",msg_id);
	msg_t msg;
	msg.pid = getpid();
	msg.mtype = atol(argv[1]);
	fprintf(stdout,"请输入要发送的消息: ");
	fflush(stdout);
	fgets(msg.msg_buf,sizeof(msg.msg_buf),stdin);
	if(msgsnd(msg_id,&msg,sizeof(msg) - sizeof(msg.mtype),IPC_NOWAIT) == -1){
		perror("msgsnd error");
		exit(-1);
	}
	fprintf(stdout,"消息发送成功\n");
	return 0;
}

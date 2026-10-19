#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
//msgrcv()函数接收消息

typedef struct {
	long int mtype;
	char buf[128];
} msg_t;

int main(){
	key_t kt = ftok("./",186);
	if(kt == -1){
		perror("ftok error");
		exit(-1);
	}
	int msg_id = msgget(kt,IPC_CREAT | 0666);
	if(msg_id == -1){
		perror("msgget error");
		exit(-1);
	}
	msg_t message;
	if(msgrcv(msg_id,&message,sizeof(message) - sizeof(message.mtype),1,IPC_NOWAIT) == -1){
		perror("msgsnd msg error");
		exit(-1);
	}
	fprintf(stdout,"接收到的数据类型 = %ld\n",message.mtype);
	fprintf(stdout,"接收到的数据 = %s\n",message.buf);
	return 0;
}

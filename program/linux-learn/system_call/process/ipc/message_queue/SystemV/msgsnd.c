#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
//msgsnd()函数发送消息

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
	message.mtype = 1;
	sprintf(message.buf,"%s","hello world!");
	fprintf(stdout,"要发送的消息 = %s\n",message.buf);
	if(msgsnd(msg_id,&message,sizeof(message) - sizeof(message.mtype),IPC_NOWAIT) == -1){
		perror("msgsnd msg error");
		exit(-1);
	}
	return 0;
}

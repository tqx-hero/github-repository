#include <unistd.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include "msg_t.h"
#include <errno.h>
//msgrcv()接收消息
//argv[1]为要接收的消息类型:
// argv[1] == 0 : 无条件接收消息队列的第一条消息
//argv[1] > 0 : 接收msg_t.mtype ==  argv[1]的消息
//argv[1] < 0 : 接收满足 msg_t.mtype <= |argv[1]|所有消息中mtype最小的那一条
int main(int argc,char** argv){
	if(argc < 2){
		fprintf(stderr,"请输入用于接收的消息类型\n");
		exit(-1);
	}
	key_t kt;
	int msg_id;
	ssize_t nbytes;
	//同样需要使用ftok()、msgget()函数获取消息队列的ID
	kt = ftok("./",1);
	if(kt == -1){
		perror("ftok error");
		exit(-1);
	}
	msg_id = msgget(kt,IPC_CREAT | 0666);
	if(msg_id == -1){
		perror("msgget error");
		exit(-1);
	}
	msg_t msg;
	nbytes = msgrcv(msg_id,&msg,sizeof(msg) - sizeof(msg.mtype),atol(argv[1]),IPC_NOWAIT);
	if(nbytes == -1){
		//没读到消息，提示，否则输出错误
		if(errno == ENOMSG){
			fprintf(stdout,"队列中无该类型消息\n");
			return 0;
		}
		perror("msgrcv error");
		exit(-1);
	}
	fprintf(stdout,"消息发送进程ID : %d\n",msg.pid);
	fprintf(stdout,"消息类型 : %ld\n",msg.mtype);
	fprintf(stdout,"消息内容 : %s\n",msg.msg_buf);
	return 0;
}

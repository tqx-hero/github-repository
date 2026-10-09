#ifndef __MSG_T_H
#define __MSG_T_H
//定义消息结构体	
typedef struct{
	long int mtype;	//消息类型
	pid_t pid;	//发送方进程ID
	char msg_buf[128]; //消息内容
}msg_t;

#endif

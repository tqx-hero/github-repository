#include <sys/msg.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//使用消息队列实现多人聊天
//fork()出子进程，父进程用于写消息，子进程用于读消息
//封装消息结构体，除了mtype之外，消息正文有进程ID，用户名称、消息内容
//创建/开启一个消息队列，使用消息队列读写函数进行系统调用
//为简单起见，令argv[1] 为自身的用户名，argv[2]为消息类型

typedef struct {
	long int mtype;
	pid_t pid;
	char username[64];
	char msg_buf[256];
}msg_t;

int main(int argc,char** argv){
	if(argc < 3){
		fprintf(stderr,"参数必须包含:用户名、消息类型\n");
		return -1;
	}
	int msg_id;
	key_t kt;
	pid_t pid;
	ssize_t nbytes;
	//创建、打开消息队列
	kt = ftok("./",1);
	if(kt == -1){
		perror("ftok error");
		exit(-1);
	}
	msg_id  = msgget(kt,IPC_CREAT | 0666); //根据key获取消息队列ID
	//定义消息结构体
	msg_t msg;
	//fork()子进程
	if((pid = fork()) == -1){
		perror("fork error");
		exit(-1);
	}
	//子进程负责读取消息到消息体
	if(pid == 0){
		while(1){
			nbytes = msgrcv(msg_id,&msg,sizeof(msg) - sizeof(long int),atol(argv[2]),0);
			if(nbytes == -1){
				perror("msgrcv error");
				exit(-1);
			}
			//拼接读到的消息
			fprintf(stdout,"mtype:[%ld],PID:[%d],username[%s]:%s\n",msg.mtype,msg.pid,msg.username,msg.msg_buf);
		}
	}else{
		//打包msg，填上固定字段username与pid
		strcpy(msg.username,argv[1]);
		msg.pid = getpid();
		while(1){
			//父进程写入消息，注意要添加给谁发送的消息
			printf("请输入写入的消息类型mtype与消息内容msg，以空格分开(1:bob;2:join;3:jan):\n");
			scanf("%ld %s",&msg.mtype,msg.msg_buf);
			//发送消息
			if(msgsnd(msg_id,&msg,sizeof(msg) - sizeof(long),0) == -1){
				perror("msgsnd error");
				break;
			}
		}
	}
	return 0;
}

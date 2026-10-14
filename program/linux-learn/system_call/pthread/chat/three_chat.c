#include <sys/syscall.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define MSG_BUF_SIZE 1024
//使用多线程+消息队列进行聊天
#ifdef B
#define MTYPE_STR 'B'
char writer[] = "Bob";
#endif

#ifdef L
#define MTYPE_STR 'L'
char writer[] = "Lucy";
#endif

#ifdef J
#define MTYPE_STR 'J'
char writer[] = "John";
#endif

#define MTYPE(__MTYPE) __MTYPE
#define NAME_SIZE 64
typedef struct {
	long int mtype;
	pid_t tid;
	char writer[NAME_SIZE];
	char msg_info[MSG_BUF_SIZE];
} msg_info_t;

typedef struct {
	int msg_id;
}msg_t;

//读消息线程
void* read_callback(void* arg){
	msg_info_t* msginfo =NULL;
	int msg_id = ((msg_t*) arg)->msg_id;
	msginfo = (msg_info_t*) malloc(sizeof(msg_info_t));
	if(!msginfo){
		fprintf(stderr,"无法申请内存空间!\n");
		exit(-1);
	}
	ssize_t nbytes;
	//printf("mtype = %ld\n",(long int)(MTYPE_STR));
	while(1){
		nbytes = msgrcv(msg_id,msginfo,sizeof(msg_info_t) - sizeof(long),(long int)(MTYPE(MTYPE_STR)),0);
		if(nbytes < 0){
			perror("msgrcv error");
			break;
		}
		//展示读到的消息
		fprintf(stdout,"tid:[%d],writer:[%s],msg:[%s]\n",msginfo->tid,msginfo->writer,msginfo->msg_info);
	}
	free(msginfo);
	pthread_exit(0);
}

//写消息线程
void* write_callback(void* arg){
	msg_info_t* msginfo =NULL;
	int msg_id = ((msg_t*) arg)->msg_id;
	msginfo = (msg_info_t*) malloc(sizeof(msg_info_t));
	if(!msginfo){
		fprintf(stderr,"无法申请内存空间!\n");
		exit(-1);
	}
	//填入必要信息
	msginfo->tid = syscall(SYS_gettid);
	strcpy(msginfo->writer,writer);
	char ch;
	while(1){
		//提示输入内容
		fprintf(stdout,"请输入发送对象的姓名首字母与消息，以:分隔(如 L:hello)\n");
		scanf("%c:%s",&ch,msginfo->msg_info);
		msginfo->mtype = (long int)ch;
		printf("要发送的消息：tid:%d,writer:%s,mtype:%ld,msg:%s\n",msginfo->tid,msginfo->writer,msginfo->mtype,msginfo->msg_info);
		//发送到消息队列
		if(msgsnd(msg_id,msginfo,sizeof(msg_info_t) - sizeof(long int),0)){
			perror("msgsnd error");
			exit(-1);
		}
	} 		
	free(msginfo);
	pthread_exit(0);
}

int main(){
	key_t kt;
	int msg_id;
	pthread_t r_tid,w_tid;
	msg_t* msg =NULL;
	//创建key_t、消息队列
	kt = ftok("./",1);
	if((msg_id = msgget(kt,IPC_CREAT | 0666)) == -1){
		perror("msgget error");
		exit(-1);
	}
	msg = (msg_t*) malloc(sizeof(msg_t));
	msg->msg_id = msg_id;
	//创建2个线程，分别进行读、写
	pthread_create(&r_tid,NULL,read_callback,msg);
	pthread_create(&w_tid,NULL,write_callback,msg);
	pthread_join(r_tid,NULL);
	pthread_join(w_tid,NULL);
	//回收消息队列
	if(msgctl(msg_id,IPC_RMID,NULL))
		perror("msg remove error");
	if(msg)
		free(msg);
	return 0;
}

#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define PTHREAD_ARR_SIZE 5
typedef struct {
	pid_t tid;
	char msg_buf[]; //使用柔性数组
}msg_info;

void* pth_exec(void* arg){
	printf("子线程已经执行，正在退出\n");
	//exit(0); //子线程中不要使用exit(2),该函数会导致进程退出，而不是线程退出，可以使用pthread_exit或return
	char* message = "大家好才是真的好!";
	msg_info* msg = (msg_info*)malloc(sizeof(msg_info)+ strlen(message) + 1);
	msg->tid = syscall(SYS_gettid);
	strcpy(msg->msg_buf,message);
	printf("子线程 %d : %s\n",msg->tid,msg->msg_buf);
	return msg;
}

int main(){
	int i,j;
	pthread_t pt[PTHREAD_ARR_SIZE];
	for(i=0;i<PTHREAD_ARR_SIZE;++i){
		if(pthread_create(&pt[i],NULL,pth_exec,NULL) != 0){
			fprintf(stderr,"创建第: %d 个线程失败\n",i+1);
			break;
		}
	}
	printf("创建 %d 个线程成功!\n",i);
	for(j = 0;j < i;++j){
		msg_info* buf;
		if(pthread_join(pt[j],(void**)&buf) != 0){
			fprintf(stderr,"子线程回收失败\n");
			exit(-1);
		}
		printf("子线程回收成功,返回线程ID = %d,信息 = %s\n",buf->tid,buf->msg_buf);
		//回收内存
		free(buf);
	}
	fprintf(stdout,"所有子线程回收成功，主线程退出...\n");
	return 0;
}

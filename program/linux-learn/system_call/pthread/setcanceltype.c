#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//设置线程为不可取消状态，观察线程的运行情况

void* can_callback(void * arg){
	pid_t tid = syscall(SYS_gettid);
	//设置线程为不可取消状态
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	//设置线程取消类型为立即取消
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	printf("已设置子线程:[%d]为不可取消状态\n",tid);
	int i=0;
	while(1){
		printf("子进程正在执行，tid = %d\n",tid);
		i++;
		sleep(1);
		if(i == 7){
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
			printf("已设置线程[%d]为可取消状态\n",tid);
		}
	}
	return (void *)1;
}

int main(){
	pthread_t tid;
	pthread_create(&tid,NULL,can_callback,NULL);
	printf("设置线程取消\n");
	pthread_cancel(tid);
	void * ret;
	printf("join返回值 = %d\n",pthread_join(tid,&ret));
	printf("ret = %ld\n",(long)ret);
	//if(!pthread_join(tid,&ret) && ret == PTHREAD_CANCELED)
	//	printf("子线程为取消状态退出\n");
	return 0;
}

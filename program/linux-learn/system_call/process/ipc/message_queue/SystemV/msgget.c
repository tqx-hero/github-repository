#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
//创建消息队列
int main(){
	key_t kt = ftok("./",186);
	if(kt == -1){
		perror("ftok error");
		return -1;
	}
	printf("kt = %d\n",kt);
	int msg_id = msgget(kt,IPC_CREAT | 0666);
	if(msg_id == -1){
		perror("msgget error");
		return -1;
	}
	printf("消息队列的id = %d\n",msg_id);
	return 0;
}

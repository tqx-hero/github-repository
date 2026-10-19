#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
//msgctl()系统调用对消息队列本身的操作
//这里先以简单的删除消息队列为例
int main(){
	if(msgctl(0,IPC_RMID,NULL) == -1){
		perror("msgctl rm msg error");
		exit(-1);
	}
	fprintf(stdout,"删除成功\n");
	execlp("ipcs","ipcs","-q",NULL);
	perror("exec ipcs error");
	return 0;
}

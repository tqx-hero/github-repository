#include <sys/ipc.h>
#include <stdio.h>

int main(){
	key_t kt = ftok("./",186);
	if(kt == -1){
		perror("ftok error");
		return -1;
	}
	printf("kt = %d\n",kt);
	return 0;
}

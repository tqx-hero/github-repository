#include <unistd.h>
#include <stdio.h>
//access()用于判断文件是否存在
int main(){
	int flag = access("./tst.txt",F_OK);
	if(flag == -1){
		perror("access error");
		return -1;
	}
	printf("文件存在\n");
	return 0;
}

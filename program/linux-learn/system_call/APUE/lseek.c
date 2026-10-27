#include <unistd.h>
#include <stdio.h>
//使用leek函数，通过输入的文件类型来查看是否可以移动读写指针
int main(){
	if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1){
		perror("can not lseek");
		return -1;
	}
	printf("lseek success\n");
	return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//先获取当前工作目录，在改变工作目录，再获取一遍当前工作目录。
int main(){
	char path[128];
	getcwd(path,128);
	printf("当前工作目录 : %s\n",path);
	//改变工作目录
	chdir("../");
	printf("改变后工作目录 : %s\n",getcwd(path,128));
	return 0;
}

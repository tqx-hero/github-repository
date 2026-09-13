#include <stdio.h>
#include <unistd.h>
//验证添加fflush函数，强制刷新缓冲区到文件
int main(){
	printf("这是一行测试行，没有添加\\n");
	fflush(stdout);
	sleep(3);
	printf("这行添加了换行的\n");
	return 0;
}

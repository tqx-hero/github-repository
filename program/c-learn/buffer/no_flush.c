#include <stdio.h>
#include <unistd.h>
//没添加换行符、强制刷新函数，不会往标准输出文件中写入
int main(){
	printf("这是一行测试行，没有添加\\n");
	sleep(2);
	printf("这是一行添加了换行的\n");
	return 0;
}

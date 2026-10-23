#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
//debug的使用
int main(int argc,char** argv){
	assert(argc > 1);
	assert(atoi(argv[1]) > 0);
	#ifdef DEBUG
		printf("debug...\n");
		printf("这是第:%d行,编译时间是:" __TIME__ "\n",__LINE__);
		printf("编译日期= " __DATE__ ",当前文件 : " __FILE__ "\n" );
		num++;
		printf("当前函数名 = %s\n",__FUNCTION__);
	#endif
	printf(".....\n");
	return 0;
}

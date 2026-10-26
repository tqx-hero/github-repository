#include <stdio.h>
#include <limits.h>
#include <unistd.h>
int main(){
	printf("long  = %ld\n",sizeof(long));
	printf("long min = %ld\n",LONG_MIN);
	printf("long long = %ld\n",sizeof(long long));
	printf("long long min = %lld\n",LLONG_MIN);
	//sysconf(3)获取系统的限制项
	printf("一个进程能同时打开的文件数量 = %ld\n",sysconf(_SC_OPEN_MAX));
	//pathconf(3)
	printf("文件名的最长为 %ld\n",pathconf("./t1.c",_PC_PATH_MAX));
	//fpathconf(3)
	printf("终端输入的最长字节数为 %ld\n",fpathconf(0,_PC_MAX_CANON));
	return 0;
}

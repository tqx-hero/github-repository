#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
//setrlimit(3)函数的使用
int main(){
	//这里直接设置栈大小
	struct rlimit limit,r_limit;
	limit.rlim_cur = 1024 * 1024;
	//limit.rlim_max = RLIM_INFINITY;
	limit.rlim_max = 8 * 1024 * 1024;
	if(setrlimit(RLIMIT_STACK,&limit) < 0)
		perror("setrlimit() error");
	//读取栈大小限制
	if(getrlimit(RLIMIT_STACK,&r_limit) < 0)
		perror("getrlimit() error");
	//fprintf(stdout,"cur = %lu,max == unlimit ? %d\n",r_limit.rlim_cur,r_limit.rlim_max == RLIM_INFINITY);
	fprintf(stdout,"cur = %lu,max == %lu\n",r_limit.rlim_cur,r_limit.rlim_max);
	return 0;
}

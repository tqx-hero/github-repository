#include <event.h>
#include <stdio.h>
/*
	获取libevent支持的方法
	以及当前使用的方法
*/
int main(){
	const char ** methods = event_get_supported_methods(); //获取libevent后端支持的方法
	struct event_base *base = event_base_new();
	int i=0;
	for(;methods[i];++i){
		printf("%s\n",methods[i]);
	}
	//获取当前使用的方法
	printf("%s\n",event_base_get_method(base));
	return 0;
}

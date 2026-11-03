#include <stdio.h>
//测试标准错误stderr是否带缓冲区
int main(){
    fprintf(stderr,"123");
    while(1);
	return 0;
}

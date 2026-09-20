#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//通过read、write针对标准输入(0)、输出(1)、错误(2)进行读写
int main(){
	char buf[128];
	int r_len = read(0,buf,sizeof(buf));
	if(write(1,buf,r_len) != r_len){
		char msg[] = "写入的字节数不正确";
		write(2,msg,strlen(msg));
	}
	return 0;
}

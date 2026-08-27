#include <string.h>
#include <stdio.h>
/*
 *
 * sprintf用法：
 * 将数据按照一定格式进行组包，放入内存中，并且在最后会添加\0。
 * 返回值为组包的真实长度，不包括最后的\0.
 * 如果组包途中有字符串，会在字符串末尾\0处开始组包
 */
int main(){
	char message[256];
	printf("ssss:%d\n",message[13]);
	int len = sprintf(message,"%d:%d:%s%d",12,30,"iamher",8);
	printf("[%d:%d]:%s\n",len,message[len],message);
	return 0;
}

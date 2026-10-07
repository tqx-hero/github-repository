#include <stdio.h>
//fgets()，从stream文件流获取字符串放到指定数组
int main(){
	char buf[128];
	fgets(buf,sizeof(buf),stdin);
	fprintf(stdout,"输入的内容： %s\n",buf);
	return 0;
}

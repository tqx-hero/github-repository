#include <stdio.h>
//fgetc()从文件流中获取一个字符
int main(){
	int ch = fgetc(stdin);
	printf("输入的字符 : %c\n",ch);
	return 0;
}

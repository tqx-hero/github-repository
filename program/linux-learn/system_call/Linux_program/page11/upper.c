#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define OUT_FILE "./a.txt"
//重定向
int main(){
	int ch;
	//测试，重定向标准输出到文件
	if(freopen(OUT_FILE,"w",stdout) == NULL){
		perror("reopen a.txt error");
		exit(EXIT_FAILURE);
	}
	while((ch = getc(stdin)) != EOF)
		putc(toupper(ch),stdout);
	return 0;
}

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
int my_atoi(const char *s);
int main(int argc,char ** argv,char** env){
	if(argc ==1){
		printf("param count error\n");
		return EXIT_FAILURE;
	}
    printf("转换后数字=%d\n",my_atoi(argv[1]));
	return 0;
}

int my_atoi(const char *s){
    long long ret =0;
    //查看第一个字符是不是+或者-
    int negative = 0;
    if(*s == '-'){
        negative = 1;
        s++;
    }
    while(isdigit(*s)){
        ret = ret*10 + (*s) - '0';
        s++;
    }
    return negative ? -ret : ret;
}
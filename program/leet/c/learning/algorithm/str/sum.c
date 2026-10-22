#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

int is_digit(char* str){
    if(*str == '-')
        str++;
    while (*str){
        if(!isdigit(*str))
            break;
        str++;
    }
    return *str == 0;
}

int main(int argc,char ** argv,char** env){
    if(argc ==1)
    {
        printf("参数个数非法\n");
        return -1;
    }
    int len = argc-1;
    //校验参数是否为数字
    int i;
    for(i=1;i<=len && is_digit(argv[i]);++i);
    if(i <= len){
        fprintf(stderr,"参数必须全部为整数\n");
        exit(-1);
    }
    int ret=0;
    while(len >=1){
        ret += atoi(argv[len]);
        len--;
    }
    printf("总和=%d\n",ret);
    return 0;
}
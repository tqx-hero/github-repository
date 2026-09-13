#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int count_words(const char *s);
int main(int argc,char ** argv,char** env){
    if(argc ==1){
        printf("参数个数不足！\n");
        return -1;
    }
    printf("单词个数 = %d\n",count_words(argv[1]));
    return 0;
}

int count_words(const char *s){
    int ret= 0,str_size = 0;
    for(;*s != 0;s++){
        if(*s == ' '){
            ret = str_size ? ret+1 : ret;
            str_size=0;
        }else
            str_size++;
    }
    return str_size ? ret+1 :ret;
}
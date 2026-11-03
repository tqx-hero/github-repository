#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//使用setbuf(3)设置缓冲区
int main(){
    char buf[BUFSIZ];
    setbuf(stdout,buf);
    fprintf(stdout,"hello world\n");
    write(1,buf,strlen(buf));
    //设置取消缓冲区
    setbuf(stdout,NULL);
    printf("hahahaha");
    while(1);
    return 0;
}


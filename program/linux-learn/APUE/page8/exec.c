#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    puts("begin");
    
    fflush(NULL);   /***必须注意冲刷缓冲区,exec替换不会主动冲刷***/

    execl("/bin/date","date","+%s",NULL);
    perror("exec() error");
    exit(1);
    puts("end");
}

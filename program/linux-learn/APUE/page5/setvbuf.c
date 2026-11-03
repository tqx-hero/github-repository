#include <stdio.h>
#include <unistd.h>
//设置缓冲区模式：全缓冲、行缓冲、不缓冲
int main(){
    //设置标准输出为全缓冲
    setvbuf(stdout,NULL,_IOFBF,0);
    printf("hello world..\n");
    sleep(5);
    fflush(stdout);
    sleep(2);
	return 0;
}

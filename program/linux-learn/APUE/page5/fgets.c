#include <stdio.h>
//验证fgets(3)可以冲刷缓冲区
int main(){
    printf(" %% ");
    char buf[1024];
    //因为fgets是取一行，行结束符\n，标准输入输出的缓冲区是行行缓冲区，遇到\n会自动刷新
    fgets(buf,sizeof(buf),stdin);
    while(1);
	return 0;
}

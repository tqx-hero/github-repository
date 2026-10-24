#include <stdlib.h>
#include <stdio.h>

//system()的用法，等价于execlp("ls","ls","-lh",NULL)
int main(){
	system("ls -lh");
	printf("输出完成\n");
	return 0;
}

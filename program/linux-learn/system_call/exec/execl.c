#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//execl的使用
int main(){
	execl("/bin/ls","ls","-lh",NULL);
	return 0;
}

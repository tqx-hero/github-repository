#include <stdio.h>
#include <unistd.h>
//fputs()用法
int main(){
	char buf[] = "hello wrold\n";
	fputs(buf,stdout);
	sleep(1);
	return 0;
}

#include <stdio.h>
extern void asm_itoa(int num,char *buf);
int main(){
	char buf[20];
	asm_itoa(1234,buf);
	printf("%s\n",buf);
	return 0;
}

#include <stdio.h>
//tmpnam的用法
int main(){
	printf("%s\n",tmpnam(NULL));
	char tmp_name[L_tmpnam];//L_tmpnam为20,缓冲区要不小于这个数
	printf("%s\n",tmpnam(tmp_name));
	printf("%s\n",tmp_name);
	return 0;
}

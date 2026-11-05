#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
//迭代获取shadow文件

int main(){
	struct spwd *sp;

	setspent();
	while((sp = getspent()) != NULL)
		fprintf(stdout,"login name = %s, pwd = %s\n",sp->sp_namp,sp->sp_pwdp);
	endspent();
	return 0;
}

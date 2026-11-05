#include <stdio.h>
#include <shadow.h>
#include <stdlib.h>
#include <unistd.h>
//获取阴影口令文件getspnam(3)
int main(){
	const char* username;
	struct spwd *wp;
	username = getlogin();
	wp = getspnam(username);
	if(wp == NULL){
		perror("getspnam() error");
		exit(1);
	}
	fprintf(stdout,"username = %s, pwd = %s\n",wp->sp_namp,wp->sp_pwdp);
	return 0;
}

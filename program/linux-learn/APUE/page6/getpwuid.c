#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
//根据用户ID获取口令:getpwuid(3)
int main(){
	uid_t uid;
	struct passwd *pwdp;
	//获取用户ID
	uid = getuid();
	errno = 0;
	pwdp = getpwuid(uid);
	if(pwdp == NULL){
		perror("getpwuid() error");
		exit(1);
	}

	fprintf(stdout,"username = %s ,passwd = %s\n",pwdp->pw_name,pwdp->pw_passwd);
	return 0;
}

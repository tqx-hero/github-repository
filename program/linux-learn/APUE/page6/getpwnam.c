#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

//通过用户名获取用户信息getpwnam(3)
int main(){
	struct passwd *pwdp;
	const char *username;
	username = getlogin();
	pwdp = getpwnam(username);
	fprintf(stdout,"username = %s , userID = %u, groupID = %u\n",pwdp->pw_name,pwdp->pw_uid,pwdp->pw_gid);
	return 0;
}

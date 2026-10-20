#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
//获取用户信息
int main(){
	struct passwd* userinfo;
	userinfo =  getpwuid(getuid());
	printf("username = %s,passwd = %s,user ID = %u, group ID = %u,userinfo = %s,home dir = %s,shell = %s\n",
		userinfo->pw_name,userinfo->pw_passwd,userinfo->pw_uid,userinfo->pw_gid,userinfo->pw_gecos,
		userinfo->pw_dir,userinfo->pw_shell);
	userinfo = getpwnam(getlogin());
	printf("username = %s,passwd = %s,user ID = %u, group ID = %u,userinfo = %s,home dir = %s,shell = %s\n",
		userinfo->pw_name,userinfo->pw_passwd,userinfo->pw_uid,userinfo->pw_gid,userinfo->pw_gecos,
		userinfo->pw_dir,userinfo->pw_shell);
	return 0;
}

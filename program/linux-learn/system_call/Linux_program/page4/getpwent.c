#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
//getpwent()用法
int main(){
	const char * username = getlogin();
	 struct passwd* userinfo;
	 while((userinfo = getpwent())){
		if(strcmp(userinfo->pw_name,username)) //不是当前用户,跳过
			continue;
	 	printf("username = %s,passwd = %s,user ID = %u, group ID = %u,userinfo = %s,home dir = %s,shell = %s\n",
                	userinfo->pw_name,userinfo->pw_passwd,userinfo->pw_uid,userinfo->pw_gid,userinfo->pw_gecos,
	                userinfo->pw_dir,userinfo->pw_shell);
		break;
	 }	
	endpwent();
	return 0;
}

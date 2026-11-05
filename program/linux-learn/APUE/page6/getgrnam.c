#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
//通过组名获取组信息getgrnam(3)
int main(){
	const char *username;
	struct group *grp;
	char **grp_mem;
	username = getlogin();
	grp = getgrnam(username);
	if(grp == NULL){
		perror("getgrnam() error");
		exit(1);
	}
	fprintf(stdout,"group name = %s,group ID = %u\n",grp->gr_name,grp->gr_gid);
	grp_mem = grp->gr_mem;
	while(*grp_mem)
		fprintf(stdout,"%s\n",*grp_mem++);
	return 0;
}

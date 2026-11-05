#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <sys/types.h>
#include <unistd.h>
//通过gid获取组信息getgrgid(3)
int main(){
	struct group *grp;
	gid_t gid;
	char **grp_mem;
	gid = getgid();//获取组ID
	if((grp = getgrgid(gid)) == NULL){
		perror("getgrgid() error");
		exit(1);
	}
	fprintf(stdout,"group name = %s,group ID = %u\n",grp->gr_name,grp->gr_gid);
	//遍历获取组下用户名
	grp_mem = grp->gr_mem;
	while(*grp_mem)
		fprintf(stdout,"%s\n",*grp_mem++);
	return 0;
}

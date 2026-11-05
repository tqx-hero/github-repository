#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//获取附属组信息getgroups(3)
int main(){
	long ngroup_max;
	int current_groups;
	int i;
	gid_t *gids;
	//获取系统设置的最大组上限,申请内存
	ngroup_max = sysconf(_SC_NGROUPS_MAX);
	fprintf(stdout,"mgroups_max = %ld\n",ngroup_max);
	if((gids = malloc(ngroup_max +1)) == NULL){
		perror("malloc() error");
		exit(1);
	}
	current_groups = getgroups(ngroup_max,gids);
	for(i = 0;i < current_groups;++i)
		fprintf(stdout,"%u\n",gids[i]);
	free(gids);
	return 0;
}

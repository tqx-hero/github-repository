#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
	查找指定目录下的所有文件，包括文件夹
*/

//按照一定规则过滤，当返回值为0，param文件会被过滤掉
int filter_dir (const struct dirent * param){
	return strcmp(param->d_name,"dirs");
}

int main(){
	struct dirent ** dirs;
	char *name = "/home/tqx/net/webserver/version1/static";
	int cnt = scandir(name,&dirs,filter_dir,alphasort);
	//int cnt = scandir(name,&dirs,NULL,versionsort);
	while(cnt--){
		printf("file = %s\n",dirs[cnt]->d_name);
		free(dirs[cnt]);
	}
	free(dirs);
	return 0;
}

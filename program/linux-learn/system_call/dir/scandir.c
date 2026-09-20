#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int filter_dir(const struct dirent *);
int main(int argc,char** argv,char** env){
	if(argc != 2){
		fprintf(stderr,"请输入目录名称\n");
		return -1;
	}
	struct dirent** dir_arr = NULL;
	int arr_len = scandir(argv[1],&dir_arr,filter_dir,alphasort);	
	//int arr_len = scandir(argv[1],&dir_arr,filter_dir,versionsort);	
	if(arr_len == -1){
		perror("scandir error:");
		return -1;
	}
	int i;
	for(i=0;i<arr_len;++i){
		struct dirent* dir = dir_arr[i];
		printf("文件: [%s],类型：%s\n",dir->d_name, dir->d_type ==  DT_REG ? "普通文件" : dir->d_type == DT_DIR ? "目录" : "其他设备文件");
		free(dir);
		dir_arr[i] =NULL;
	}
	free(dir_arr);
	dir_arr = NULL;
	return 0;
}

//int (*filter)(const struct dirent *),
//条件过滤。在这里过滤掉名称为. 与 ..的目录
int filter_dir(const struct dirent * ent){
	if(!strcasecmp(ent->d_name,".") || !strcasecmp(ent->d_name,".."))
		return 0;
	return 1;
}

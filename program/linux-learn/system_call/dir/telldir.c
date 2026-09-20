#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
//对目录的操作

int main(int argc,char** argv,char** env){
	DIR* d_ptr =NULL;
	if(argc !=2){
		fprintf(stderr,"请输入要查询的目录\n");
		return -1;
	}
	struct stat st;
	int flag = stat(argv[1],&st);
	//查询文件是否存在
	if(flag == -1){
		perror("");
		return -1;
	}
	//校验是否为目录、是否有权限访问
	if(!S_ISDIR(st.st_mode) || (st.st_mode & S_IXUSR) == 0){
		fprintf(stderr,"文件不是目录或没有访问权限\n");
		return -1;
	}
	//开始打开目录
	d_ptr =  opendir(argv[1]);
	if(!d_ptr){
		perror("");
		return -1;
	}
	//开始读取目录下的文件
	struct dirent* dir_ptr;
	long dir_off,cnt = 0;
	while((dir_ptr = readdir(d_ptr))){
		cnt++;
		printf("文件名：%s\n",dir_ptr->d_name);
		
		switch(dir_ptr->d_type){
			case DT_DIR : 
				printf("类型为目录\n");
				break;
			case DT_REG : 
				printf("类型为普通文件\n");
				break;
			default : 
				printf("类型为设备(块、字符、管道、socket等)。\n");
				break;
		}
		//记录扫描到net文件时的光标
		if(!strcmp(dir_ptr->d_name,"net")){
			dir_off = telldir(d_ptr);
			printf("dir_off = %ld\n",dir_off);
			printf("off = %ld\n",dir_ptr->d_off);
			printf("两个offset是否相同？ ：%d\n",dir_off == dir_ptr->d_off);
		}
	}
	printf("文件个数 = %ld\n",cnt);
	if(d_ptr)
		closedir(d_ptr);
	return 0;
}

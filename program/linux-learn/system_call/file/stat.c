#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//stat函数的使用
int main(int argc,char** argv,char** env){
	if(argc != 2){
		fprintf(stderr,"请输入要查询的文件名\n");
		exit(-1);
	}
	struct stat st;
	int flag = stat(argv[1],&st);
	if(flag == -1){
		perror("");
		exit(-1);
	}
	if(S_ISDIR(st.st_mode))
		printf("该文件为目录\n");
	else if((st.st_mode & S_IFMT) == S_IFREG  && (st.st_mode & S_IRWXU) == (S_IRUSR | S_IWUSR))
		printf("该文件为可读写的普通文件,大小为:%ld bytes\n",st.st_size);
	return 0;
}

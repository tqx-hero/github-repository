#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#define SWITCH_TYPE(__KEY,__CHARSTR)	case __KEY :		\
						ch = __CHARSTR;	\
					break
//使用opendir、readdir函数实现对目录的访问
int main(int argc,char **argv){
	DIR *dp;
	struct dirent *dnt;
	int ch;
	if(argc < 2){
		fprintf(stderr,"Usage main() : param invalid! \n");
		exit(1);
	}

	if((dp = opendir(argv[1])) == NULL){
		perror("opendir() error");
		exit(1);
	}
	
	//遍历目录，读取目录项
	while((dnt = readdir(dp)) != NULL){
		fprintf(stdout,"filename = %s\n", dnt->d_name);
		fprintf(stdout,"inode number = %ld\n", dnt->d_ino);
		switch(dnt->d_type){
			SWITCH_TYPE(DT_BLK,'b');
			SWITCH_TYPE(DT_CHR,'c');
			SWITCH_TYPE(DT_FIFO,'p');
			SWITCH_TYPE(DT_REG,'r');
			SWITCH_TYPE(DT_DIR,'d');
			SWITCH_TYPE(DT_LNK,'l');
			SWITCH_TYPE(DT_SOCK,'s');
			default :
				ch = 'u';
				break;
		}
		fprintf(stdout,"file type = %c\n", ch);
		fprintf(stdout,"..............\n");
	}
	closedir(dp);
	return 0;
}

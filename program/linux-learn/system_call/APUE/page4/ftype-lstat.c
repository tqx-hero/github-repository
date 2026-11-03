#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
//给一个文件名，返回它的文件类型
#define FILE_TYPE(__COMPARED,__RESVAL) case __COMPARED : \
					res = __RESVAL;	\
					break
static int ftype(const char *fname){
	struct stat st;
	int res;
	if(lstat(fname,&st) < 0){
		perror("stat() error");
		exit(EXIT_FAILURE);
	}

	switch(st.st_mode & S_IFMT){
		FILE_TYPE(S_IFLNK,'l');
		FILE_TYPE(S_IFREG,'r');
		FILE_TYPE(S_IFDIR,'d');
		FILE_TYPE(S_IFCHR,'c');
		FILE_TYPE(S_IFBLK,'b');
		FILE_TYPE(S_IFSOCK,'s');
		FILE_TYPE(S_IFIFO,'p');
		default :
			res = 'u';
			break;
	}
	return res;
}

int main(int argc,char **argv){

	if(argc < 2)
	{
		fprintf(stderr,"Usage main() : param invalid !\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout,"文件类型 : %c\n",ftype(argv[1]));
	return 0;
}

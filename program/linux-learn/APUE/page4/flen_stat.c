#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//通过stat(2)获取文件大小
int main(int argc,char **argv){
	if(argc < 2){
		fprintf(stderr,"Usage main() : 参数不全 !\n");
		exit(EXIT_FAILURE);
	}

	struct stat st;
	if(stat(argv[1],&st) < 0){
		perror("stat() error");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout,"size = %ld\n",st.st_size);
	return 0;
}

#include "mygetline.h"
//测试mygetline()函数
#include <fcntl.h>
int main(int argc,char ** argv){
	if(argc < 2){
		fprintf(stderr,"Usage main() : param <argv[1]> must not be empty !\n");
		exit(EXIT_FAILURE);
	}
	int fd;
	char *lineptr = NULL;
	size_t linesz = 0;
	ssize_t bytes;
	if((fd = open(argv[1],O_RDONLY)) < 0){
		perror("open file error");
		exit(EXIT_FAILURE);
	}
	
	//按照行读取
	while(1){
		if((bytes = fmygetline(fd,&lineptr,&linesz)) < 0){
			perror("getline error");
			exit(EXIT_FAILURE);
		}
		else if(!bytes)
			break;
		fprintf(stdout,"%s",lineptr);
		//fprintf(stdout,"linesz = %lu\n",linesz);
		//fprintf(stdout,"strlen = %lu\n",strlen(lineptr));
	}
	mygetline_free(lineptr);
	close(fd);
	return 0;
}

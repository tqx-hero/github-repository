#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#define EXIT(status)	if(fd >= 0)		\
				 close(fd);	\
			exit(status)

int main(int argc,char **argv){
	int fd;
	ssize_t file_size;
	if(argc < 3){
		fprintf(stderr,"Usage main(): <argv[1]>: filename, <argv[2]>: filesize !\n");
		EXIT(1);
	}
	
	file_size = atoll(argv[2]);
	if(file_size <= 0){
		fprintf(stderr,"Usage param : < argv[2] > invalid !\n");
		EXIT(1);
	}

	fd = open(argv[1],O_WRONLY | O_CREAT,0644);
	if(fd < 0){
		perror("open() error");
		EXIT(1);
	}
 	
	if(ftruncate(fd,file_size) < 0){
		perror("ftruncate() error");
		EXIT(1);
	}

	fprintf(stdout,"ftruncate success!\n");

	EXIT(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define FILE_NAME "/tmp/file2"
#define EXIT(num)	if(fd)		\
			  close(fd);	\
			  exit(num)
int main(){
	int fd;
	char buf[10];
	fd = open(FILE_NAME,O_RDWR | O_CREAT | O_TRUNC,0644);
	if(fd < 0){
		perror("open() error");
		EXIT(1);
	}

	if(pwrite(fd,"XYZ",3,10) < 0){
		perror("pwrite() error");
		EXIT(1);
	}

	if(pread(fd,buf,5,SEEK_SET) < 0){
		perror("pread() error");
		EXIT(1);
	}

	fprintf(stdout,"%c %c %c %c %c \n",buf[0],buf[1],buf[2],buf[3],buf[4]);
	return 0;
}

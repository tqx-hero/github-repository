#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define FILE_NAME "/tmp/file1"
#define EXIT(STATUS) if(fd1 >= 0)	\
			close(fd1);	\
		     if(fd2 >= 0)	\
		     	close(fd2);	\
			exit(STATUS)
int main(){
	int fd1,fd2;
	char buf[128];
	fd1 = -1;
	fd2 = -1;
	fd1 = open(FILE_NAME,O_WRONLY | O_CREAT | O_TRUNC,0666);
	if(fd1 < 0){
		perror("open fd1 error");
		EXIT(1);
	}

	fd2 = open(FILE_NAME,O_RDONLY);
	if(fd2 < 0){
		perror("open fd2 error");
		EXIT(1);
	}

	if(write(fd1,"ABCDE",5) < 0){
		perror("write() error");
		EXIT(1);
	}

	if(read(fd2,buf,3) < 3){
		perror("read() error");
		EXIT(1);
	}

	buf[3] = 0;
	fprintf(stdout,"%s\n",buf);

	EXIT(0);
}

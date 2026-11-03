#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define EXIT_HANDLER(__EXIT_STATUS) if(r_fd >= 0) 	\
					close(r_fd);	\
				    if(w_fd >= 0)	\
					close(w_fd);	\
				    exit(__EXIT_STATUS)
#define BUF_SIZE BUFSIZ
//实现cp功能
int main(int argc,char **argv){
	int r_fd,w_fd;
	char buf[BUF_SIZE];
	ssize_t rlen,wlen,pos;
	if(argc < 3){
		fprintf(stderr,"Usage main() : param is invalid !\n");
		EXIT_HANDLER(EXIT_FAILURE);
	}
	r_fd = -1;
	w_fd = -1;
	r_fd = open(argv[1],O_RDONLY);
	if(r_fd < 0){
		perror("open rfd error");
		EXIT_HANDLER(EXIT_FAILURE);
	}

	w_fd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(w_fd < 0){
		perror("open wfd error");
		EXIT_HANDLER(EXIT_FAILURE);
	}
	
	while(1){
		rlen = read(r_fd,buf,sizeof(buf));
		if(rlen < 0){
			perror("read error");
			EXIT_HANDLER(EXIT_FAILURE);
		}else if(rlen == 0)
			break;
		pos = 0;
		while(pos < rlen){ //写
			wlen = write(w_fd,buf + pos,rlen - pos);
			pos += wlen;
		}
	}
	fprintf(stdout,"cp success !\n");

	EXIT_HANDLER(EXIT_SUCCESS);
}

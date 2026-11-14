#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#define BUF_SIZE BUFSIZ 
//实现cat的功能
int main(int argc,char **argv){
	int sfd = -1,dfd = 1;
	char buf[BUF_SIZE];
	ssize_t bytes,res;
	if(argc < 2){
		fprintf(stderr,"Usage param <argv>\n");
		exit(EXIT_FAILURE);
	}

    do{
        sfd = open(argv[1],O_RDONLY);
        if(sfd < 0){
            if(errno != EINTR){
                perror("open argv[1] error");
                goto fail_ret;
            }
        }
    }while(sfd < 0);

	while(1){
		bytes = read(sfd,buf,sizeof(buf));
		if(bytes < 0){
            if(errno == EINTR)
                continue;
			perror("read error");
			goto fail_ret;
		}
		if(!bytes)
			break;
		res = 0;
		while(1){
			res = write(dfd,buf + res,bytes);
			if(res <= 0){
                if(res < 0 && errno == EINTR)
                    continue;
				perror("write error");
				goto fail_ret;
			}
			if(res >= bytes)
				break;
			bytes -= res;
		}
	}

	close(sfd);
	return 0;

fail_ret:
	if(sfd >= 0)
		close(sfd);
	exit(EXIT_FAILURE);
}

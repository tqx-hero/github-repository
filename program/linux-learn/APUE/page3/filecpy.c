#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
//测试变换缓冲区大小对文件复制的效率影响
#define BUF_SIZE BUFSIZ 
//传递2个参数，分别代表要复制的文件与复制到的地方
int main(int argc,char **argv){
	int sfd = -1,dfd = -1;
	char buf[BUF_SIZE];
	ssize_t bytes,res;
	time_t start_time,end_time;
	if(argc < 3){
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

    do{
        dfd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0600);
        if(dfd < 0){
            if(errno != EINTR){
                perror("open argv[2] error");
                goto fail_ret;
            }
        }
    }while(dfd < 0);
	//统计时间
	start_time = time(NULL);

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

	end_time = time(NULL);
	fprintf(stdout,"耗时：%f\n", difftime(end_time,start_time));
	close(sfd);
	close(dfd);
	return 0;

fail_ret:
	if(sfd >= 0)
		close(sfd);
	if(dfd >= 0)
		close(dfd);
	exit(EXIT_FAILURE);
}

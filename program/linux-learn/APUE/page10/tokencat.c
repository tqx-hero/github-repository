#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#define TOKEN_MAX 50
#define CPS 10
#define BUF_SIZE CPS 

//令牌桶功能
//令牌数
static volatile int token = 0;

//SIGALRM信号捕获
static void alrm_handler(int signum){
    if(++token > TOKEN_MAX)
        token = TOKEN_MAX;
    alarm(1);
}

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

    //注册信号
    if(signal(SIGALRM,alrm_handler) == SIG_ERR){
        perror("signal()");
        goto fail_ret;
    }
    alarm(1);

    while(1){

        //如果没有token，阻塞在这里
        while(!token)
            pause();
        --token;

        while((bytes = read(sfd,buf,sizeof(buf))) < 0)
        {
            if(errno == EINTR){
                continue;
            }
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

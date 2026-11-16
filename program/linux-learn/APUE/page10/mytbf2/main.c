#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include "mytbf.h"
#define TOKEN_MAX 50
#define CPS 10
#define BUF_SIZE 1024 

int main(int argc,char **argv){
    int sfd = -1,dfd = 1;
    char buf[BUF_SIZE];
    ssize_t bytes,res;
    mytbf_t *mbf = NULL;
    int tokenlen;
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

    mbf = mytbf_init(CPS,TOKEN_MAX);
    if(mbf == NULL)
    {
        perror("mytbf_init()");
        exit(1);
    }

    while(1){
        tokenlen = mytbf_fetch(mbf,BUF_SIZE);
        if(tokenlen < 0){
            perror("mytbf_fetch()");
            exit(1);
        }

        while((bytes = read(sfd,buf,tokenlen)) < 0)
        {
            if(errno == EINTR){
                continue;
            }
            perror("read error");
            goto fail_ret;
        }

        if(!bytes)
            break;
        //如果读取的字节数少于长度，将剩余的字节返还令牌桶
        if(bytes < tokenlen && 
                mytbf_return(mbf,tokenlen - bytes) < 0){
            perror("mytbf_return()");
            exit(1);
        }

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

    //销毁令牌桶
    if(mytbf_destory(mbf) < 0)
        perror("mytbf_destory()");
    close(sfd);
    return 0;

fail_ret:
    if(sfd >= 0)
        close(sfd);
    if(mbf)
        mytbf_destory(mbf);
    exit(EXIT_FAILURE);
}

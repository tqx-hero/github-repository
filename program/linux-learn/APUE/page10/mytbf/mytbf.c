#include "mytbf.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

typedef struct {
    int cps;//速率，
    int token;//token数量，每次增加cps的字节数
    int burst;//token的最大值
    int pos;
} mf_t;

//令牌桶
mf_t *mf_buf[MYTBF_BUFSIZ];

static int get_free_pos();
static int min(const int x,const int y);
static void alrm_handler(int signum);
static int max(const int x,const int y);
static void init_tbf(void);
static int init;
static void (*alrm_old_handler)(int);

mytbf_t *mytbf_init(int cps,int burst){
    mf_t *mf;
    int pos;
    //获取桶的空余位置
    if((pos = get_free_pos()) == -1)
        return NULL;
    //有空余位置，申请空间，准备放入桶
    mf = malloc(sizeof(mf_t));
    if(mf == NULL)
        return NULL;

    //初始化令牌结构体
    mf -> cps = cps;
    mf -> burst = burst;
    mf -> token = 0;
    mf -> pos = pos;
    //结构体入桶
    mf_buf[pos] = mf;

    //注册信号捕获
    if(!init){
        init = 1;
        init_tbf();
    }
    return mf;
}

int mytbf_fetch(mytbf_t* mbf,int maxsize){
    int ret;
    mf_t *mf = (mf_t*) mbf;
    if(maxsize <= 0)
    {
        errno = EINVAL;
        return - 1;
    }
    while(mf -> token == 0)
        pause();

    ret = min(mf -> token,maxsize);
    mf->token -= ret;
    return ret; 
}

int mytbf_return(mytbf_t* mbf,int returnval){
    mf_t* mf = (mf_t*) mbf;
    if(returnval <= 0){
        errno = EINVAL;
        return -1;
    }
    mf -> token =  min(returnval + mf -> token,
            mf -> burst);
    return 0;
}

int mytbf_destory(mytbf_t* mbf){
    mf_buf[((mf_t*)mbf) -> pos] = NULL;
    free(mbf);
    return 0;
}


static void alrm_handler(int signum){
    int i;
    for(i = 0;i < MYTBF_BUFSIZ;++i){
        if(mf_buf[i])
            mf_buf[i]->token = min(mf_buf[i]->burst,
                    mf_buf[i]->token + mf_buf[i]->cps);
    }
    alarm(1);
}

static void destory_tbf(void){
    int i;
    if(signal(SIGALRM,alrm_old_handler) == SIG_ERR){
        perror("signal()");
    }

    alarm(0);
    for(i = 0;i < MYTBF_BUFSIZ;++i)
    {   
        free(mf_buf[i]);
        mf_buf[i] = NULL;
    }
}

static void init_tbf(void){
    alrm_old_handler = signal(SIGALRM,alrm_handler);
    if(alrm_old_handler == SIG_ERR){
        perror("signal()");
        exit(1);
    }

    alarm(1);
    //增加钩子函数，当进程退出时执行卸载功能
    atexit(destory_tbf);
    return;
}

static int max(const int x,const int y){
    return x >= y ? x : y;
}

static int min(const int x,const int y){
    return x <= y ? x : y;
}

static int get_free_pos(){
    int i;
    for(i = 0;i < MYTBF_BUFSIZ;++i){
        if(mf_buf[i] == NULL)
            return i;
    }
    errno = ENOBUFS;
    return -1;
}

#include "anytimer.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef struct {
    unsigned int second;
    void (*func) (void*);
    void* arg;
    unsigned int pos;
}mytimer_t;

mytimer_t *tim_buf[MYTIME_SIZ];
static void (*alrm_handler_old) (int);
static int getpos(void);
static int init;
static void alrm_handler(int signum);
static int moudle_init(void);
mytime_t *mysettimer(unsigned int seconds,void(*func)(void*),void* arg)
{
    mytimer_t *mt;
    int pos;
    //校验参数
    if(seconds == 0 || func == NULL){
        errno = EINVAL;
        return NULL;
    }

    //查找是否数组还有槽
    if((pos = getpos()) < 0){
        errno = ENOBUFS;
        return NULL;
    }

    //申请内存，填充结构体
    mt = malloc(sizeof(mytimer_t));
    if(!mt)
        return NULL;

    mt->second = seconds;
    mt->func = func;
    mt->arg = arg;
    mt->pos = pos;
    tim_buf[pos] = mt;//放入数组
    //加载闹钟功能
    if(!init)
    {
        moudle_init();
    }
    //返回结构体指针
    return mt;
}

static int getpos(void){
    int i;
    for(i = 0;i < MYTIME_SIZ && tim_buf[i];++i);
    return i == MYTIME_SIZ ? -1 : i;
}

static void module_uninstall(){
    int i;
    //停掉闹钟
    alarm(0);
    //还原信号
    signal(SIGALRM,alrm_handler_old);
    //回收数组中指针的内存
    for(i = 0;i < MYTIME_SIZ;++i)
        free(tim_buf[i]);
    return;
}

static int moudle_init(void){
    init = 1;
    //设定定时器，每秒钟遍历数组，进行一次减时间操作
    alrm_handler_old = signal(SIGALRM,alrm_handler);
    if(alrm_handler_old == SIG_ERR){
        errno = EBUSY;
        return -1;
    }
    alarm(1);
    //注册进程退出时的模块卸载功能
    atexit(module_uninstall);
    return 0;
}

static void alrm_handler(int signum)
{
    int i;
    for(i = 0;i < MYTIME_SIZ;++i){
        if(tim_buf[i] && --tim_buf[i]->second == 0)
        {
            //调用程序,这里可以使用多线程
            tim_buf[i]->func(tim_buf[i]->arg);
            free(tim_buf[i]);
            tim_buf[i] = NULL;
        }
    }
    alarm(1);
}



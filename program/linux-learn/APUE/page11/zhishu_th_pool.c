#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#define LEFT_NUM 3000000
#define RIGHT_NUM 3000200
#define NUM_SIZ 4 

//使用4个线程筛选范围内的质数.
//main线程负责往结构体内放，4个线程负责取

struct th_arg_t{
    int num;
};

static struct th_arg_t thp;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void* th_handler(void *arg)
{
    int num,i;
    pthread_t tid = pthread_self();
    while(1)
    {
        pthread_mutex_lock(&mtx);
        while(thp.num == 0) //当没有新任务送达，解锁等待
        {
            pthread_mutex_unlock(&mtx);
            sched_yield();
            pthread_mutex_lock(&mtx);
        }
        //首先看一下值是否是-1，是-1表示要退出了
        if(thp.num == -1)
        {
            pthread_mutex_unlock(&mtx);
            break;
        }
        //不是-1，那就是任务，领取并把值设置为0
        num = thp.num;
        thp.num = 0;
        pthread_mutex_unlock(&mtx);
        //执行任务
        for(i = 2;i <= (num / 2) && (num % i);++i);
        if(i > (num / 2))
            fprintf(stdout,"线程[%lu] : %d is current num !\n",tid,num);
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t pth_arr[NUM_SIZ];
    int i,err;
    //创建线程
    for(i = 0;i < NUM_SIZ;++i)
    {
        if(err  = pthread_create(pth_arr + i,NULL,th_handler,NULL))
        {
            fprintf(stderr,"%s\n",strerror(err));
            exit(1);
        }
    }
    //添加任务
    for(i = LEFT_NUM;i <= RIGHT_NUM ;++i)
    {
        pthread_mutex_lock(&mtx);
        //先判断任务有没有被取走，没被取走就释放锁待会再放入新任务
        while(thp.num != 0)
        {
            pthread_mutex_unlock(&mtx);
            sched_yield();
            pthread_mutex_lock(&mtx);
        }
        thp.num = i;//等于0时就将其设置为新任务
        pthread_mutex_unlock(&mtx);
    }

    pthread_mutex_lock(&mtx);
    //判断任务是否已经被其他线程领取
    while(thp.num != 0)
    {
        pthread_mutex_unlock(&mtx);
        sched_yield();
        pthread_mutex_lock(&mtx);
    }
    //所有任务都被领取完成，再将值设置为-1，表示所有线程退出
    thp.num = -1;
    pthread_mutex_unlock(&mtx);

    //回收资源
    for(i = 0;i < NUM_SIZ;++i)
    {
        if(err = pthread_join(pth_arr[i],NULL))
        {
            fprintf(stderr,"%s\n",strerror(err));
            exit(1);
        }
    }

    pthread_mutex_destroy(&mtx);
    exit(0);
}

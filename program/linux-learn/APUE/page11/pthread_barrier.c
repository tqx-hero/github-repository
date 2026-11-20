#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define TH_SIZ 8

#define NUMBER 8000000L
#define TNUM (NUMBER / TH_SIZ)
static pthread_barrier_t br;
long nums[NUMBER];
long snums[NUMBER];

struct sorted_t{
    long begin_idx;
};

static int compared(const void * v1,const void *v2)
{
    return *(long*) v1 >= *(long *) v2;
}

static void *th_handler(void *arg)
{
    long bidx = ((struct sorted_t*) arg) -> begin_idx;
    
    //每一个线程排序
    qsort(nums + bidx,TNUM,sizeof(long),compared);
    
    pthread_barrier_wait(&br);
    fprintf(stdout,"线程[%llu] 已完成排序!\n",pthread_self());
    pthread_exit(arg);
}

static void merge(void)
{
    long i,sidx,j,minval,minidx,num;
    long idx[TH_SIZ];
    for(i = 0;i < TH_SIZ;++i)
        idx[i] = i * TNUM;
    
    for(sidx = 0 ; sidx < NUMBER ;++sidx)
    {
        minval = LONG_MAX;
        //找到每个分段最小值
        for(j = 0 ;j < TH_SIZ; ++j)
        {
            if(idx[j] < ((j + 1) * TNUM) && (num = nums[idx[j]]) < minval)
            {
                minidx = j;
                minval = num;
            }
        }
        //最小值放入数组
        snums[sidx] = minval;
        idx[minidx]++;
    }
}

int main(){
    pthread_t pth_arr[TH_SIZ];
    long i;
    int err;
    struct sorted_t *st;

    //设置随机数
    srandom(time(NULL));
    for(i = 0 ;i < NUMBER;++i)
        nums[i] = random();
    
    pthread_barrier_init(&br,NULL,TH_SIZ + 1);
    for(i = 0; i < TH_SIZ ; ++i )
    {
        if((st = malloc(sizeof(struct sorted_t))) == NULL)
        {
            perror("malloc()");
            exit(1);
        }
        st->begin_idx = i * TNUM;
        err = pthread_create(pth_arr + i,NULL,th_handler,st);
        if(err)
        {
            fprintf(stderr,"%s\n",strerror(err));
            exit(1);
        }
    }

    pthread_barrier_wait(&br);
    fprintf(stdout,"排序完成，正在汇总:\n");
    merge();
    for(i = 0;i < NUMBER;++i)
        fprintf(stdout,"%ld\n",snums[i]);
    //销毁资源,释放内存
    for(i = 0;i < TH_SIZ ;++i)
    {
        pthread_join(pth_arr[i],(void**) &st);
        free(st);
    }
    pthread_barrier_destroy(&br);

    exit(0);
}

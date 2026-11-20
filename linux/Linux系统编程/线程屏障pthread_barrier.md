### 线程屏障`pthread_barrier`

```c
#include <pthread.h>

int pthread_barrier_destroy(pthread_barrier_t *barrier);
int pthread_barrier_init(pthread_barrier_t *restrict barrier,
      const pthread_barrierattr_t *restrict attr, unsigned count);
```



`pthread_barrier_destroy()` 销毁 `barrier` 指向的屏障，并释放该屏障占用的资源。在屏障再次通过 `pthread_barrier_init()` 重新初始化之前，后续再使用这个屏障的行为是未定义的。实现可以利用该函数把 barrier 对象置为无效值。 如果**有线程正阻塞在该屏障上**时调用 `pthread_barrier_destroy()`，或是对一个未初始化的屏障调用本函数，结果都是未定义行为。

`pthread_barrier_init()` 分配使用该屏障所需的资源，并按照 `attr` 指向的属性初始化屏障。如果 `attr` 为 `NULL`，则使用屏障默认属性，效果等同于传入默认属性对象的地址。 如果有线程阻塞在屏障上（也就是还没有从 `pthread_barrier_wait()` 返回）时调用 `pthread_barrier_init()`，结果未定义。屏障未经初始化就直接使用，结果未定义。对一个已经初始化完成的屏障再次调用 `pthread_barrier_init()`，结果未定义。

参数 `count` 指定：必须有 `count` 个线程调用 `pthread_barrier_wait()` 之后，这些线程才可以成功从该调用返回。`count` 的取值必须大于 0。

如果 `pthread_barrier_init()` 调用失败，屏障不会被初始化，`barrier` 对象内部内容是未定义的。

只有 `barrier` 指向的原对象可以用来同步；把该对象拷贝一份，用拷贝出来的对象去调用 `pthread_barrier_destroy()` / `pthread_barrier_wait()`，行为未定义。

#### 返回值

调用成功返回 0；失败时返回错误码标识错误原因。



```c
#include <pthread.h>
int pthread_barrier_wait(pthread_barrier_t *barrier);
```



`pthread_barrier_wait()` 在 `barrier` 指向的屏障处同步参与线程。调用线程会阻塞，直到达到设定数量的线程都对该屏障调用了`pthread_barrier_wait()`。

当凑够指定数量线程调用 `pthread_barrier_wait()` 时：**其中一个不确定的线程会收到返回值 `PTHREAD_BARRIER_SERIAL_THREAD`，其余所有线程返回 0**。

**与此同时，屏障会重置为最近一次 `pthread_barrier_init()` 之后的初始状态（屏障可以再次复用，下一轮继续等待 count 个线程）。**

常量 `PTHREAD_BARRIER_SERIAL_THREAD` 在 `<pthread.h>` 中定义，它的值和 `pthread_barrier_wait()` 其他所有返回值都不相同。

如果对一个**未初始化的屏障**调用本函数，行为未定义。

如果一个阻塞在屏障上的线程收到信号：信号处理函数返回之后，若屏障还没有凑齐线程（等待未完成），线程继续阻塞等待；若等待已经完成，则线程正常从 wait 返回继续执行。在信号处理函数执行期间，即便所有线程都已经抵达屏障，其他线程是否可以越过屏障继续执行，标准不作规定。

阻塞在屏障上的线程，不会阻止其他就绪、可调度的线程持续推进执行；调度权由调度策略决定（屏障阻塞不造成整体死锁、不抢占调度资源语义）。

#### 返回值

成功时：**随机一个线程返回 `PTHREAD_BARRIER_SERIAL_THREAD`，其余返回 0**；失败则返回错误码。



###### demo:使用屏障实现多线程排序功能

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
//要创建的线程数
#define TH_SIZ 8
//要排序的数量
#define NUMBER 8000000L
//每个线程要排序的数量
#define TNUM (NUMBER / TH_SIZ)

//线程屏障对象
static pthread_barrier_t br;
//分别表示排序前与排序后的数组
long nums[NUMBER];
long snums[NUMBER];

struct sorted_t{
    long begin_idx;//当前线程处理排序任务起始下标
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

    pthread_barrier_wait(&br);//任务执行完成，阻塞等待所有线程全部执行完统一退出
    fprintf(stdout,"线程[%llu] 已完成排序!\n",pthread_self());
    pthread_exit(arg);
}

//对每个排好序的分段，找到当前最小值放入新数组
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

    //初始化屏障等待线程的数量，创建8个+main线程一共9个
    pthread_barrier_init(&br,NULL,TH_SIZ + 1);
    for(i = 0; i < TH_SIZ ; ++i )
    {
        if((st = malloc(sizeof(struct sorted_t))) == NULL)
        {
            perror("malloc()");
            exit(1);
        }
        st->begin_idx = i * TNUM;//将线程处理分段的起始下标放到结构体，作为参数传入任务
        
        err = pthread_create(pth_arr + i,NULL,th_handler,st);
        if(err)
        {
            fprintf(stderr,"%s\n",strerror(err));
            exit(1);
        }
    }

    pthread_barrier_wait(&br);//等待全部线程都执行完成
    fprintf(stdout,"排序完成，正在汇总:\n");
    merge();
    
    for(i = 0;i < NUMBER;++i)
        fprintf(stdout,"%ld\n",snums[i]);
    
    //销毁资源,释放内存
    for(i = 0;i < TH_SIZ ;++i)
    {
        pthread_join(pth_arr[i],(void**) &st);
        free(st);//注意释放结构体在堆空间的内存
    }
    pthread_barrier_destroy(&br);//销毁线程屏障

    exit(0);
}
```


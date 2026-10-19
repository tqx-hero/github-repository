### 线程间的同步：

#### 条件变量pthread_cond_t：

​		**给互斥锁的线程阻塞队列进行更细粒度的拆分，当不满足某个条件，把线程放到一个队列中阻塞；当其他进程使用共享资源直到满足这个条件时，有其他线程精准唤醒这个队列中的一个或多个线程(唤醒是把线程从条件队列放到就绪队列)。由于是按照条件进行入队，所以相同队列中的线程都是在等待同一个条件满足，这样能做到精准唤醒，不会导致盲目唤醒与惊群效应。**

**由上述得出，条件变量是对互斥锁进行的一个优化，所以前提还是要创建互斥对象。**

###### 条件变量的创建、销毁：

```c
#include <pthread.h>
/**
	pthread_cond_init () 函数将使用 attr 所指向的属性来初始化 cond 所引用的条件变量。若 attr 为 NULL，则使用默认的条件变量属性；其效果等同于传入一个默认条件变量属性对象的地址。初始化成功后，该条件变量的状态变为已初始化。
	cond: 条件对象的地址。
	attr：条件对象的属性。为NULL表示默认属性(全部为0)，等价于 PTHREAD_COND_INITIALIZER
	return:
		成功：0
		失败：错误码如下
			EAGAIN: 系统缺少初始化另一个条件变量所需的资源（内存除外）。
			ENOMEM: 内存不足。
			EINVAL：attr属性未加载。
*/
int pthread_cond_init(pthread_cond_t *restrict cond,const pthread_condattr_t *restrict attr);
/**
	pthread_cond_destroy () 函数将销毁由 cond 指定的条件变量；该对象实际上变为未初始化状态。
实现方案可使 pthread_cond_destroy () 将 cond 指向的对象置为无效值。已销毁的条件变量对象可通过 pthread_cond_init () 重新初始化.
	不能对未初始化的条件变量进行销毁。
	return：
		成功：0
		失败：错误码如下
			EINVAL：cond没有没初始化。
*/
int pthread_cond_destroy(pthread_cond_t *cond);
//默认初始化条件变量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
```

###### pthread_cond_t:

```c
#define __extension__ 	//这是一个扩展选项,当前值为空
#define __SIZEOF_PTHREAD_COND_T 48
#define __LOCK_ALIGNMENT 
typedef union
{
  struct __pthread_cond_s __data;	//条件变量结构体
  char __size[__SIZEOF_PTHREAD_COND_T];	//结构体大小为48字节，这里为字节填充
  __extension__ long long int __align;	//内存对齐为8字节
} pthread_cond_t;

struct __pthread_cond_s
{
  __extension__ union
  {
    __extension__ unsigned long long int __wseq;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __wseq32;
  };
  __extension__ union
  {
    __extension__ unsigned long long int __g1_start;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __g1_start32;
  };
  unsigned int __g_refs[2] __LOCK_ALIGNMENT;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};
```



##### 条件变量的释放锁、入队pthread_cond_wait(3):

###### 		作用都是将当前线程放到cond的条件队列中阻塞，等待其他线程唤醒，同时释放锁。所以这两个函数调用时*必须要先持有锁*，否则会报错。

###### 		两个函数都会有虚假唤醒，这和CPU的调度有关系，所以使用该函数时必须用while(condation...)防止虚假唤醒线程往下执行。千万不要用if(condition...)

​		pthread_cond_timedwait () 和 pthread_cond_wait () 函数会在条件变量上阻塞。应用程序必须保证调用线程在调用这些函数时已经持有互斥锁；否则，对于 PTHREAD_MUTEX_ERRORCHECK 类型互斥锁和健壮互斥锁会返回错误，对于其他类型互斥锁则会产生未定义行为。

​		**这些函数会原子性地释放互斥锁，并让调用线程在条件变量 cond 上阻塞**；此处的原子性指 “相对于其他线程对该互斥锁以及后续条件变量的访问保持原子”。也就是说，如果某个即将阻塞的线程释放互斥锁之后，另一个线程能够获取该互斥锁，那么该线程后续调用 pthread_cond_broadcast () 或 pthread_cond_signal () 的行为，等同于在这个即将阻塞的线程完成阻塞之后才发起调用。

​		**函数成功返回时，互斥锁已经被锁定，并且归调用线程持有**。如果该互斥锁是健壮互斥锁，且锁的持有者在持有锁期间终止，同时状态可恢复，那么即便函数返回错误码，调用线程依然会获取该互斥锁。

​		使用条件变量时，每一次条件等待操作都总是关联一个包含共享变量的布尔断言：当断言为真时，线程才可以继续向下执行。pthread_cond_timedwait () 或 pthread_cond_wait () 函数可能产生虚假唤醒。由于从这两个函数返回并不代表该布尔断言的取值情况，因此在返回后必须重新检查该断言。

​		当线程调用 pthread_cond_timedwait () 或 pthread_cond_wait ()，为等待操作指定特定互斥锁并在条件变量上等待时，该互斥锁与条件变量之间会建立动态绑定。只要至少有一个线程阻塞在该条件变量上，这个绑定就持续有效。在此期间，如果任何线程尝试使用其他互斥锁在这个条件变量上等待，行为是未定义的。一旦所有等待线程都被解除阻塞（例如通过 pthread_cond_broadcast ()），下一次针对该条件变量的等待操作，会和本次等待指定的互斥锁建立新的动态绑定。即便在线程从条件等待解除阻塞，到返回调用方或者开始执行取消清理这段时间内，条件变量与互斥锁之间的动态绑定可能被移除或替换，被唤醒的线程仍然会重新获取本次条件等待调用中指定的互斥锁。

​		**条件等待（无论是否带超时）是一个取消点**。当线程的可取消类型设置为 PTHREAD_CANCEL_DEFERRED 时，若线程在条件等待过程中处理取消请求，会产生一个副作用：在执行第一个取消清理处理函数前，会重新获取互斥锁。其效果相当于线程被解除阻塞，一直执行到即将从 pthread_cond_timedwait () 或 pthread_cond_wait () 返回的位置；但在该位置检测到取消请求，不会返回给这两个函数的调用者，而是开始执行线程取消流程，其中包含调用取消清理处理函数。

​		如果线程在阻塞于 pthread_cond_timedwait () 或 pthread_cond_wait () 期间收到取消操作而被解除阻塞，并且该条件变量上还存在其他阻塞线程，则该线程不会消耗同一时间发送给这个条件变量的任何条件信号。

​		**pthread_cond_timedwait () 函数功能等同于 pthread_cond_wait ()，区别在于：如果在条件变量 cond 收到信号或广播通知之前，abstime 指定的绝对时间已到期（即系统时间等于或超过 abstime），或者调用该函数时 abstime 指定的绝对时间已经过期，则函数会返回错误**。发生这类超时情况时，pthread_cond_timedwait () 仍然会释放并重新获取 mutex 参数指向的互斥锁，并且可能消耗同一时刻发送给该条件变量的条件信号。

​		条件变量具有时钟属性，该属性指定用于计量 abstime 参数所指定时间的时钟。pthread_cond_timedwait () 函数同时也是一个取消点。

​		如果正在等待条件变量的线程收到信号，在信号处理函数返回后，线程会继续等待该条件变量，如同没有被信号中断一样；或者线程可能因虚假唤醒而返回 0。

```c
#include <pthread.h>
/**
	持续阻塞，直到满足条件被唤醒。
	cond：等待的条件。
	mutex：释放的互斥锁。
	return：
		成功：0
		失败：
			ENOTRECOVERABLE：互斥锁保护的状态不可恢复。
			EOWNERDEAD：该互斥锁为健壮互斥锁，持有该互斥锁的上一所属线程所在进程在持有锁期间终止。调用线程将获取此互斥锁，由新持有者负责恢复状态一致性。
			EPERM：互斥锁类型为 PTHREAD_MUTEX_ERRORCHECK（检错互斥锁），或是健壮互斥锁，且当前线程并不持有该互斥锁。
*/
int pthread_cond_wait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex);
/**
	有时间的阻塞，时间到了会返回错误。
	cond：等待的条件。
	mutex：释放的互斥锁。
	abstime: 最大阻塞时间。
	return：
		成功：0
		失败：
			ENOTRECOVERABLE：互斥锁保护的状态不可恢复。
			EOWNERDEAD：该互斥锁为健壮互斥锁，持有该互斥锁的上一所属线程所在进程在持有锁期间终止。调用线程将获取此互斥锁，由新持有者负责恢复状态一致性。
			EPERM：互斥锁类型为 PTHREAD_MUTEX_ERRORCHECK（检错互斥锁），或是健壮互斥锁，且当前线程并不持有该互斥锁。
			ETIMEDOUT：pthread_cond_timedwait () 指定的 abstime 时间已到期。
			EINVAL： 参数 abstime 指定的纳秒值小于零，或者大于等于 10 亿
*/
int pthread_cond_timedwait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex,
                           const struct timespec *restrict abstime);

typedef long __kernel_time_t;
struct timespec {
        __kernel_time_t tv_sec;                 /* seconds */
        long            tv_nsec;                /* nanoseconds */
};
```

##### 唤醒线程：

​		这些函数用于解除条件变量上阻塞的线程。

​		pthread_cond_broadcast () 函数会解除当前在指定条件变量 cond 上阻塞的所有线程。

​		pthread_cond_signal () 函数会解除指定条件变量 cond 上阻塞的一个线程（如果有线程在 cond 上阻塞）。

​		如果有多个线程在某个条件变量上阻塞，线程的唤醒顺序由调度策略决定。当因调用 pthread_cond_broadcast () 或 pthread_cond_signal () 而被唤醒的线程从 pthread_cond_wait () 或 pthread_cond_timedwait () 调用返回时，该线程将持有其调用 pthread_cond_wait () 或 pthread_cond_timedwait () 时所关联的互斥锁。被唤醒的线程将按照调度策略（如适用）竞争该互斥锁，其行为等同于每个线程都调用了 pthread_mutex_lock ()。

​		线程调用 pthread_cond_broadcast () 或 pthread_cond_signal () 时，无论其当前是否持有那些调用 pthread_cond_wait () 或 pthread_cond_timedwait () 的线程在等待期间与该条件变量绑定的互斥锁，都可以调用这两个函数；但是，如果需要可预测的调度行为，则调用 pthread_cond_broadcast () 或 pthread_cond_signal () 的线程应当持有该互斥锁。

​		如果当前没有线程在 cond 上阻塞，pthread_cond_broadcast () 和 pthread_cond_signal () 函数不会产生任何效果。

##### 两者区别：

signal是唤醒满足条件cond的至少线程，这个线程是在队列中任意选择一个，无法做到精准唤醒指定的一个(只能做到精准唤醒一类中的一个)。

broadcast是唤醒所有cond队列中的线程进行锁的竞争，到最后仍然是少量的线程会持有锁进入就绪态。

###### 两者选择：

​		**如果是写少读多的场景，即临界资源可以让多个线程共享读锁时，优先选用broadcast(),这样在多核处理机上增加CPU的吞吐量；或者全局状态改变，需要所有线程更新状态(需要线程退出，修改了大循环条件)，必须使用broadcast()唤醒所有线程更新。**

​		**除此之外，全部使用signal()，避免惊群效应出现，不必要的上下文开销。**

```c
#include <pthread.h>
/**
	return:
		成功： 0
		失败：
			EINVAL：参数未初始化。
*/
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond);
```

#### 生产者消费者模型(重点)：以互斥锁+条件变量实现。

​		**两种线程共用一个消息队列，生产者线程往队列中生产消息，消费者线程从队列消费消息。消息队列为临界资源**

​		**需要设置一个互斥对象，生产者消费者线程在访问临界资源时需要先竞争互斥对象的锁。**

​		**生产线程当消息队列满了，需要停止生产，释放已持有的锁，进入阻塞状态，等待队列不满时再生产；消费线程当消息队列空，同样需要停止消费，释放持有的锁，进入阻塞状态，等待队列不空再消费。**

​		**根据以上概述，可以使用条件变量pthread_cond，生产线程使用full变量，当队列满，进入full条件的阻塞队列，等待消费线程消费了消息后(消费了消息队列不满了)唤醒；消费线程使用empty变量，当队列空，进入empty条件的阻塞队列，等待生产线程生产了消息后(生产消息后不空了)唤醒。**

​		**至于唤醒的函数，broadcast与signal均可，这里使用的signal只唤醒一个，减少线程上下文切换开销，也避免了惊群效应。**

###### 消息队列头文件： \<ArrayDeque.h\>

```c
#ifndef OS_ARRAYDEQUE_H
#define OS_ARRAYDEQUE_H
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

//这里必须为2的整数幂
#define ARRAYDEQUE_MAX_SIZE 16


//定义一个循环队列
typedef struct ArrayDeque {
    void* obj[ARRAYDEQUE_MAX_SIZE];
    int count;
    int front;
    int rear;
} ArrayDeque;
/**
        查询当前队列的元素个数
        queue: 消息队列对象的地址
        return:
                成功：返回元素个数
                失败：-1
*/
int arrayDeque_size(ArrayDeque *queue);
/**
        初始化队列
        queue: 消息队列对象的地址
*/
void arrayDeque_initQueue(ArrayDeque *queue);
/**
        判断当前队列是否为空
        queue: 消息队列对象的地址
        return:
                为空：1
                不为空：0
*/
_Bool arrayDeque_isEmpty(ArrayDeque *queue);
/**
        获取队头元素
        queue: 消息队列对象的地址
        obj: 将队头元素拷贝到该地址
        size：元素的大小，以字节为单位
        return:
                成功：0
                失败：-1
*/
int arrayDeque_peek(ArrayDeque *queue,void* obj,size_t size);
/**
        取出队头元素，队头元素出队
        queue: 消息队列对象的地址
        obj: 将队头元素拷贝到该地址
        size：元素的大小，以字节为单位
        return:
                成功：0
                失败：-1
*/
int arrayDeque_poll(ArrayDeque *queue,void*,size_t);
/**
        判断当前队列是否已满
        queue: 消息队列对象的地址
        return:
                已满：1
                不满：0
*/
_Bool arrayDeque_isFull(ArrayDeque *queue);
/**
        将元素添加到队列
        queue: 消息队列对象的地址
        obj: 元素的地址
        size：元素的大小，以字节为单位
        return:
                成功：0
                失败：-1
*/
int arrayDeque_offer(ArrayDeque *queue, void*,size_t);
/**
        销毁队列，回收队列资源
        queue: 消息队列对象的地址
*/
int arrayDeque_destory(ArrayDeque*);

#endif //OS_ARRAYDEQUE_H
```



###### 队列的实现源文件：\<ArrayDeque.c\>

```c
#include "ArrayDeque.h"

_Bool arrayDeque_isEmpty(ArrayDeque *queue) {
    return queue->count == 0;
}

void arrayDeque_initQueue(ArrayDeque *queue) {
    memset(queue,0,sizeof(ArrayDeque));
}

int arrayDeque_poll(ArrayDeque *queue,void* obj,size_t size) {
    if (!arrayDeque_isEmpty(queue)) {
        void* target = queue->obj[queue->front];
        memcpy(obj,target,size);
        //释放这个下标的内存空间
        free(target);
        queue->obj[queue->front] = NULL;
        queue->count--;
        queue->front = (queue->front + 1) & (ARRAYDEQUE_MAX_SIZE - 1);
        return 0;
    }
    obj = NULL;
    return -1;
}

int arrayDeque_peek(ArrayDeque *queue,void* obj,size_t size) {
    if (!arrayDeque_isEmpty(queue)){
        memcpy(obj,queue->obj[queue->front],size);
        return 0;
    }
    obj = NULL;
    return -1;
}

_Bool arrayDeque_isFull(ArrayDeque *queue) {
    return queue->count == ARRAYDEQUE_MAX_SIZE;
}

int arrayDeque_size(ArrayDeque *queue) {
    return queue->count;
}

int arrayDeque_offer(ArrayDeque *queue, void* obj,size_t size) {
    if (!arrayDeque_isFull(queue)) {
        void* ptr= (void*) malloc(size);
        if(!ptr){
                fprintf(stderr,"malloc error\n");
                exit(-1);
        }
        queue->obj[queue->rear] = ptr;
        memcpy(queue->obj[queue->rear],obj,size);
        queue->rear = (queue->rear + 1) & (ARRAYDEQUE_MAX_SIZE - 1);
        queue->count++;
        return 0;
    }
    return 0;
}

int arrayDeque_destory(ArrayDeque* queue){
        int front = queue->front,rear = queue->rear;
        while( front & (ARRAYDEQUE_MAX_SIZE - 1) != rear){
                free(queue->obj[front]);
                queue->obj[front] = NULL;
                front = (front + 1) & (ARRAYDEQUE_MAX_SIZE -1);
        }
        return 0;
}
```

###### 生产者消费者主程序：\<src.c\>

```c
#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "ArrayDeque.h"         //消息队列
#define THREAD_COUNT 10         //生产者消费者各5个
#define MSG_MAX_SIZE MAX_SIZE

//定义消息结构体
typedef struct Object {
    int num;
} Object;

//生产者消费者模型mutex+cond
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//创建2个条件
//empty:满足缓冲区空时，消费者阻塞在该条件队列
//full:缓冲区满时，生产者阻塞在该条件队列
pthread_cond_t empty = PTHREAD_COND_INITIALIZER,full = PTHREAD_COND_INITIALIZER;
pthread_t threads[THREAD_COUNT];
ArrayDeque msgque;
int num;
int running = 1;//执行总开关,为0时退出程序
void init_src(){
        //加载消息队列
        arrayDeque_initQueue(&msgque);
}
//生产者
void* provider(void* arg){
        pid_t tid = syscall(SYS_gettid);
        while(running){
                pthread_mutex_lock(&lock);
                //判断队列是否为满,满了的话入full条件队列
                while(running && arrayDeque_isFull(&msgque)) //循环检查防止虚假唤醒
                        pthread_cond_wait(&full,&lock);
                if(!running)
                        break;
                //队列不满就放入消息
                Object obj = {num++};
                arrayDeque_offer(&msgque,&obj,sizeof(Object));
                printf("生产线程[%d] 生产了消息: %d\n",tid,obj.num);
                pthread_mutex_unlock(&lock);
                //pthread_cond_broadcast(&empty);
                pthread_cond_signal(&empty);
            	usleep(1000 * 100);	//退出临界区之后的其他业务
        }
        //解锁
        pthread_mutex_unlock(&lock);
        printf("生产线程[%d]已退出\n",tid);
        pthread_exit(NULL);
}
//消费者
void* consumer(void* arg){
        pid_t tid = syscall(SYS_gettid);
        while(running){
                pthread_mutex_lock(&lock);
                //队列空，消费者线程阻塞到empty条件队列
                while(running && arrayDeque_isEmpty(&msgque))//循环检查防止出现虚假唤醒
                        pthread_cond_wait(&empty,&lock);
                if(!running)
                        break;
                Object obj;
                //消费消息
                arrayDeque_poll(&msgque,&obj,sizeof(Object));
                printf("消费者线程[%d]消费了消息: %d\n",tid,obj.num);
                pthread_mutex_unlock(&lock);
                //pthread_cond_broadcast(&full);
                pthread_cond_signal(&full);
            	usleep(1000 * 100);//退出临界区之后的其他业务
        }
        pthread_mutex_unlock(&lock);
        printf("消费线程[%d]已退出\n",tid);
        pthread_exit(NULL);
}
//对SIGINT信号进行处理，将运行字段变为0
void sigint_handler(int signum){
        running = 0;
        printf("已进入终止执行流程，开始回收资源\n");
        return;
}
//回收资源
void destory_src(){
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&empty);
        pthread_cond_destroy(&full);
        //回收消息队列
        arrayDeque_destory(&msgque);
}

int main(){
        //注册信号SIGINT处理，回收资源(虽然该信号会终止进程自动回收所有资源，没什么实际用途,这里是以该信号为例作为练习)
        struct sigaction sigact;
        sigact.sa_flags = 0;
        sigemptyset(&sigact.sa_mask);
        sigact.sa_handler = sigint_handler;
        if(sigaction(SIGINT,&sigact,NULL)){
                perror("sigaction SIGINT error");
                exit(-1);
        }
        init_src();
        //创建线程
        int i;
        for(i = 0;i < THREAD_COUNT;++i){
                if(i % 2 ==0)
                        pthread_create(&threads[i],NULL,provider,NULL);
                else
                        pthread_create(&threads[i],NULL,consumer,NULL);
                //pthread_detach(threads[i]);
        }
        while(running)
                sleep(10);
        //开始回收资源
        int j;
        //唤醒所有阻塞的线程
        pthread_cond_broadcast(&empty);
        pthread_cond_broadcast(&full);
        for(j = 0;j < i;++j)
                pthread_join(threads[j],NULL);
        //线程全部退出后，回收条件变量、互斥锁、消息队列
        destory_src();
        printf("所有资源已回收，程序退出.\n");
        return 0;
}
```




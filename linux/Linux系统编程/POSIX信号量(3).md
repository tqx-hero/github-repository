### POSIX信号量：

#### 信号量(POSIX标准)：

##### 本质就是一个计数器，用于表示临界资源当前可以同时被几个线程访问。对信号量的操作是PV,P是减少、V是增加，这2个操作是具有原子性的。

###### 下面是通过对sem操作来实现对临界资源访问的步骤：

> ​		1、假设初始信号量sem >0，线程之前对信号量进行P操作，当sem < 0 时，表示临界资源已经到达线程访问数量上限，本线程不能访问，只能等待其他线程访问完成进行V操作。可以根据业务情况，采取自旋或者挂起线程等待。

> ​		2、当线程访问完临界资源，需要对sem进行V操作，表示本线程已访问完毕。如果增加后sem<=0，代表之前sem的值为负数，表示有其他线程正在等待访问该临界资源，此时就需要本线程唤醒其他阻塞线程。

**互斥锁的本质就是sem = 1时，代表有且仅有一个线程能访问临界资源。**

**(sem = N)>1时，就是共享锁，也就是读写锁里面的读锁，代表可以N个线程共享临界资源。**

**需要同步访问临界资源的代码段叫做临界区。**

***POSIX标准中的信号量分无名信号量与有名信号量2种,这两种信号量与管道一样，无名用完即回收；有名是以一个字符串为标识,适用于进程间的通信。***

#### 信号量结构体：

```c
typedef union
{
  char __size[__SIZEOF_SEM_T];	//64位占32字节，32位占16字节
  long int __align;
} sem_t;

#if __WORDSIZE == 64
# define __SIZEOF_SEM_T 32
#else
# define __SIZEOF_SEM_T 16
#endif
```



#### 无名信号量：

##### 信号量的初始化(创建)与销毁:

###### sem_init(3):

> sem_init () 用于初始化 sem 指向地址处的未命名信号量。value 参数指定该信号量的初始值。

> pshared 参数表示该信号量是在同一进程的线程间共享，还是在多个进程之间共享。

> 若 pshared 的值为 0，则该信号量在同一进程内的线程间共享，且需要存放在所有线程都可访问的地址（例如全局变量，或是在堆上动态分配的变量）。

> 若 pshared 不为 0，则该信号量在多个进程间共享，且必须存放在共享内存区域（参见 shm_open (3)、mmap (2) 以及 shmget (2)）。（由 fork (2) 创建的子进程会继承父进程的内存映射，因此也可以访问该信号量。）任何能够访问这片共享内存区域的进程，都可以通过 sem_post (3)、sem_wait (3) 等函数操作这个信号量。

> 对一个已经初始化过的信号量再次执行初始化，会产生未定义行为。

```c
#include <semaphore.h>
/**
	初始化无名信号量
	sem: 信号量地址。
	pshared: 是否进程共享。默认为0，代表不共享
		0:进程独占。
		不等于0：进程可以共享。启用该选项时，sem必须要在共享内存或mmap同一区域。
	value：信号量的值，这里是用的无符号整数。
	return：
		成功：0
		失败：-1，错误码errno。
			EINVAL: 信号量的值value超过了可以设定的最大值 SEM_VALUE_MAX（有符号整数的最大值2^31 -1）.
			ENOSYS: pshared不为0，但是系统不支持进程共享信号量（参考sem_overview(7)）。
*/
int sem_init(sem_t *sem, int pshared, unsigned int value);
/**
	销毁 sem 指针指向的未命名信号量。
	只有经由 sem_init (3) 初始化过的信号量，才可以使用 sem_destroy () 销毁。
	不能销毁当前有其他进程或线程正在 sem_wait (3) 上阻塞等待的信号量。
	不能销毁已经销毁的信号量，除非该信号量已经通过 sem_init (3) 重新完成初始化。
	已销毁的信号量可以通过sem_init()重新初始化。
return：
	成功时返回 0；发生错误时返回 -1，并设置 errno 以标识错误类型。
	EINVAL：信号量不合法。
*/
int sem_destroy(sem_t *sem);
Link with -pthread.
```



#### 有名信号量的开启、关闭：

```c
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
/**
	name: 信号量的标识，相同的name会开启同一个信号量。关于名称构成的详细信息，请参见 sem_overview (7)。
	oflag：参数指定用于控制该调用行为的标志。（引入 <fcntl.h> 头文件可以获取这些标志值的定义。）如果 oflag 中指定了 O_CREAT，那么当该信号量不存在时就会创建它。信号量的所有者（用户 ID）会被设置为调用进程的有效用户 ID；所属组（组 ID）会被设置为调用进程的有效组 ID。如果 oflag 同时指定 O_CREAT 和 O_EXCL，当同名信号量已经存在时，函数将返回错误。
	如果 oflag 指定了 O_CREAT，则必须提供另外两个参数。即有该项时，需要使用第二函数:
	
	mode: 指定新信号量的访问权限，规则同 open (2)(引入 <sys/stat.h> 头文件可以获取权限位的符号定义).
	value : 指定新信号量的初始值。
	
	如果指定了 O_CREAT，但同名信号量已经存在，则 mode 和 value 参数会被忽略。
	
	return：
		成功时，sem_open () 返回新信号量的地址；调用其他信号量相关函数时会使用该地址。
		出错时，sem_open () 返回 SEM_FAILED((sem_t*)0)，并设置 errno 以指明错误类型。
		错误码：
			EACCES：信号量存在，但调用者没有打开它的权限。
			EEXIST：oflag 参数中同时指定了 O_CREAT 和 O_EXCL，但是已存在同名信号量。
			EINVAL：value 大于 SEM_VALUE_MAX。
			EINVAL：名称仅由 “/” 构成，后面没有其他字符。
			EMFILE：已达到单个进程可打开文件描述符数量上限。
			ENAMETOOLONG：名称过长。
			ENFILE：已达到系统全局打开文件总数上限。
			ENOENT：oflag 参数未指定 O_CREAT，且不存在该名称的信号量；或者指定了 O_CREAT，但名称格式非法。
			ENOMEM：内存不足。
*/
sem_t *sem_open(const char *name, int oflag);
sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);

/**
	sem_close () 关闭由 sem 指向的命名信号量，系统会释放为调用进程分配给该信号量的相关资源。
	所有已打开的命名信号量会在进程终止或调用 execve (2) 时自动关闭。
	return: 
		成功：0
		失败：-1，错误码填充到errno：
		EINVAL：参数sem不合法。
*/
int sem_close(sem_t *sem);

/**
	sem_unlink () 函数用于删除由 name 指定的命名信号量。信号量名称会被立即移除。当所有其他打开该信号量的进程都将其关闭后，该信号量才会被销毁。它的效果等同于System V中的 semctl(2)command参数设置IPC_RMID。
	return：
		成功：0
		失败：-1，填充errno
			EACCES： 调用进程没有权限删除该信号量。
			ENAMETOOLONG：名称name过长。
			ENOENT： 不存在具有该名称的信号量。
*/
int sem_unlink(const char *name);

Link with -pthread.
```



###### 信号量的PV操作：

P操作：

> 所有这些函数调用成功时返回 0；发生错误时，信号量的值保持不变，函数返回 - 1，并设置 errno 以标识错误类型。
>
> ***这些函数都可以被信号中断，如果信号sa_flags设置了SA_RESTART,在信号handler返回后sem_init(3)与sem_timewait(3)会恢复原状态（自 Linux 2.6.22 版本起；之前版本，调用总是返回 EINTR 错误，详情参考signal(7)）。***

```c
#include <semaphore.h>
/**
	信号量-1，当信号量减之前为0，阻塞直到够减再返回。
	错误码：
		EINTR：被信号打断，具体行为参考上面的斜版字体说明。
		EINVAL：参数不合法。
*/
int sem_wait(sem_t *sem);
/**
	sem_wait()的不阻塞版本，当无法立刻执行减一操作时，该调用会返回-1，错误码 errno 设置为 EAGAIN，而不会阻塞。
	EAGAIN：当前的信号量值为0，不能进行P操作
*/
int sem_trywait(sem_t *sem);
/**
	限定阻塞时长的sem_wait()版本,当阻塞时长超过绝对时间：abs_timeout，会返回。
	EINVAL：abs_timeout的时间不合法。abs_timeout.tv_nsecs 的值小于 0，或者大于等于 10 亿。
	ETIMEDOUT：abs_timeout设定的时间到了还没有成功执行P操作。
*/
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

Link with -pthread.
```



> sem_wait () 会对 sem 指向的信号量执行减一操作（加锁）。若信号量的值大于 0，则直接完成减一操作，函数立即返回。若信号量当前值为 0，该调用会阻塞，直到可以执行减一操作（也就是信号量的值上升至大于 0），或是信号处理函数中断本次调用。

> sem_trywait () 的功能与 sem_wait () 一致，区别在于：当无法立刻执行减一操作时，该调用会返回错误（错误码 errno 设置为 EAGAIN），而不会阻塞。

> sem_timedwait () 的功能与 sem_wait () 一致，区别在于：当无法立刻执行减一操作时，abs_timeout 参数限定了本次调用的阻塞时长。abs_timeout 参数指向一个结构体，该结构体指定了自纪元时间（1970-01-01 00:00:00 +0000 (UTC)）起的绝对超时时间，单位为秒和纳秒。该结构体定义如下：

```c
struct timespec {
    time_t tv_sec;      /* 秒 */
    long   tv_nsec;     /* 纳秒 [0 .. 999999999] */
};
```

> 如果调用发生时超时时间已到期，且无法立刻对信号量加锁，则 sem_timedwait () 执行失败，返回超时错误（错误码 errno 设置为 ETIMEDOUT）。



V操作：

```c
#include <semaphore.h>
/**
	return：
		成功：0
		失败：-1，填充errno
			EINVAL： 参数不合法。
			EOVERFLOW：信号量将超出其最大允许值。
*/
int sem_post(sem_t *sem);

Link with -pthread.
```

> sem_post () 会增加（解锁）sem 指向的信号量。如果信号量的值因此大于 0，那么另一个在 sem_wait (3) 调用中阻塞的进程或线程将被唤醒，并继续获取该信号量。

> **sem_post () 是异步信号安全函数：可以在信号处理函数内安全调用。**



###### 获取信号量的当前值：

```c
#include <semaphore.h>
/**
	sem: 信号量地址。
	sval：存储当前信号量值的地址。
	return：
		成功：0
		失败：-1，填充errno
			EINVAL：参数不合法。
*/
int sem_getvalue(sem_t *sem, int *sval);

Link with -pthread.
```

> sem_getvalue () 函数将 sem 指向的信号量的当前值存入 sval 指向的整型变量中。

> 如果有一个或多个进程或线程阻塞，等待通过 sem_wait (3) 锁定该信号量，POSIX.1 标准对 sval 的返回值规定了两种可选情况：返回 0；或是返回一个负数，其绝对值代表当前在 sem_wait (3) 中阻塞的进程与线程数量。Linux 采用前一种行为。

> 当 sem_getvalue () 返回时，信号量的值可能已经发生变化。



###### demo:使用信号量实现互斥锁

启动程序，参数为打印次数cnt，生成10个线程，执行cnt次打印任务，最后关闭进程。

```c
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define THREAD_COUNT 10

//使用信号量实现互斥锁的功能
sem_t sm;
long int cur_cnt;
void* th_printer(void* arg){
        pid_t tid = syscall(SYS_gettid);
        long total_cnt = (long) arg;
        while(1){
                sem_wait(&sm);//P操作
                if(cur_cnt >= total_cnt)
                        break;
                //次数不到，执行打印
                printf("线程[%d]正在打印第[%ld]份文件...\n",tid,++cur_cnt);
                sem_post(&sm);
                usleep(1000 * 200);
        }
        sem_post(&sm);//退出之前千万不要忘了V操作
        printf("线程[%d]退出.\n",tid);
        pthread_exit(NULL);
}
//argv[1]为输入打印次数
int main(int argc,char** argv){
        if(argc <2){
                fprintf(stderr,"请输入打印次数\n");
                exit(-1);
        }
        long int cnt = atol(argv[1]);
        if(cnt <= 0){
                fprintf(stderr,"请输入正确的打印次数(>0)!\n");
                exit(-1);
        }
        sem_init(&sm,0,1);//设置信号量初值为1
        //创建线程执行打印任务
        pthread_t threads[THREAD_COUNT];
        int i;
        for(i = 0; i < THREAD_COUNT;++i)
                pthread_create(&threads[i],NULL,th_printer,(void*)cnt);
        for(i = 0; i < THREAD_COUNT; ++i)
                pthread_join(threads[i],NULL);
        sem_destroy(&sm);
        printf("打印任务全部完成，总打印数量:[%ld],实际打印数量:[%ld].\n",cnt,cur_cnt);
        return 0;
}
```



###### demo：实现2个线程交替执行\<order.c\>

```c
#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
//信号量实现2个线程交替执行
sem_t sem1,sem2;
long cur_cnt;
typedef struct {
        long total_count;
}pth_msg_t;
//线程t1，执行的操作：sem1 > P,sem2 > V
void* t1_exec(void* arg){
        pth_msg_t* msgp = (pth_msg_t*)arg;
        long total_count = msgp->total_count;
        pid_t tid = syscall(SYS_gettid);
        while(1){
                sem_wait(&sem1);
                if(cur_cnt >= total_count){
                        sem_post(&sem2);
                        break;
                }
                ++cur_cnt;
                fprintf(stdout,"线程[%d]执行第[%ld]次\n",tid,cur_cnt);
                sem_post(&sem2);	//对信号2+1，此时的信号量：sem1=0,sem2=1，阻塞的线程2可以执行
                usleep(1000 * 100);
        }
        pthread_exit(NULL);
}
//线程t2，执行的操作：sem2 > P,sem1 > V
void* t2_exec(void* arg){
        pth_msg_t* msgp = (pth_msg_t*)arg;
        long total_count = msgp->total_count;
        pid_t tid = syscall(SYS_gettid);
        while(1){
                sem_wait(&sem2);
                if(cur_cnt >= total_count){
                        sem_post(&sem1);
                        break;
                }
                ++cur_cnt;
                fprintf(stdout,"线程[%d]执行第[%ld]次\n",tid,cur_cnt);
                sem_post(&sem1);
                usleep(1000 * 100);
        }
        pthread_exit(NULL);
}

void* Malloc(size_t size){
        void* ret;
        if(!(ret = malloc(size))){
                perror("malloc error");
                exit(-1);
        }
        return ret;
}
//argv[1]参数为执行次数
int main(int argc,char** argv){
        if(argc <2){
                fprintf(stderr,"请输入要执行的总次数\n");
                exit(-1);
        }
        long total_cnt = atol(argv[1]);
        if(total_cnt < 1){
                fprintf(stderr,"输入的执行总次数要大于1\n");
                exit(-1);
        }
        pth_msg_t* pmsg = NULL;
        pthread_t t1,t2;//创建2个线程
        pmsg = (pth_msg_t*)Malloc(sizeof(pth_msg_t));
        pmsg->total_count = total_cnt;
        //谁先开始谁信号量为1,另一个信号量为0，刚开始为阻塞态。
        sem_init(&sem1,0,1);
        sem_init(&sem2,0,0);
        pthread_create(&t1,NULL,t1_exec,pmsg);
        pthread_create(&t2,NULL,t2_exec,pmsg);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        fprintf(stdout,"任务结束!总次数:[%ld],实际次数:[%ld].\n",total_cnt,cur_cnt);
        sem_destroy(&sem1);
        sem_destroy(&sem2);
        free(pmsg);
        return 0;
}
```

启动脚本:

```bash
./order 100	#执行100次任务
```

###### demo:信号量实现生产者消费者模型

> ​		消息队列头文件\<ArrayDeque.h\>与源文件\<ArrayDeque.c\>在该文档的：互斥锁+条件变量 实现部分，其中把队列的最大值修改为了8，这样在生产者消费者都为10个线程时可以更好的观察CPU对线程的调度带来的结果的不可预测性。

> ​		主程序中，生产者消费者线程都是10个，消息队列size=8。

> ​		使用了3个信号量：

> ​				1、pro_sem:生产者的sem，等于消息队列的size，代表每一时刻并行的生产线程最多有多少个。

> ​				2、con_sem:消费者sem，初值等于0，起初消息队列为空，需要等到生产者生产消息后执行对它的V操作，唤醒阻塞的消费者。

> ​				3、mutex: 消息队列的互斥量，初值为1。生产者消费者同一时刻都竞争使用消息队列，存在竞态，属于临界资源，对它的访问需要使用互斥量进行限制,也就是互斥锁。

> ​		示例中把重点放在了信号量的工作过程，忽略了：某些函数异常的处理、信号的handler、对线程循环次数的控制等，后续可自行查阅相关资料补齐。

主程序\<producer_consumer.c\>如下：

```c
#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayDeque.h"
#define MQ_SIZE ARRAYDEQUE_MAX_SIZE
#define CON_THREAD_COUNT 10
#define PRO_THREAD_COUNT 10
//pro_sem:生产者信号量,初值为队列总容量，表示一次性(原子操作)能放入的总数量
//con_sem:消费者信号量，初值为0，需要等生产者V操作后会的信号量
//mutex: 对临界资源消息队列进行互斥量定义，给它加锁
sem_t pro_sem,con_sem,mutex;
pthread_t pro_th[PRO_THREAD_COUNT],con_th[CON_THREAD_COUNT];
long cur_num;
ArrayDeque queue;
typedef struct {
        long num;
        pid_t tid;
}msg_t;

void* pro_handler(void* arg){
        pid_t tid = syscall(SYS_gettid);
        msg_t* msg = (msg_t*)malloc(sizeof(msg_t));
        if(!msg){
                perror("malloc error");
                exit(-1);
        }
        while(1){
                sem_wait(&pro_sem);//P操作
                msg->num = ++cur_num;
                msg->tid = tid;
                sem_wait(&mutex);
                arrayDeque_offer(&queue,msg,sizeof(msg_t));
                sem_post(&mutex);
                fprintf(stdout,"线程[%d]放入了第[%ld]条消息.\n",tid,cur_num);
                sem_post(&con_sem);//唤醒消费者
                //usleep(1000 * 200);
        }
        free(msg);
        pthread_exit(NULL);
}

void* con_handler(void* arg){
        pid_t tid = syscall(SYS_gettid);
        msg_t* msg = (msg_t*)malloc(sizeof(msg_t));
        if(!msg){
                perror("malloc error");
                exit(-1);
        }
        while(1){
                sem_wait(&con_sem);
                //消费消息
                sem_wait(&mutex);
                arrayDeque_poll(&queue,msg,sizeof(msg_t));
                sem_post(&mutex);
                fprintf(stdout,"消费线程[%d]: [%d] > [%ld].\n",tid,msg->tid,msg->num);
                sem_post(&pro_sem);
                //usleep(1000 * 200);
        }
        free(msg);//释放内存
        return NULL;
}

int main(){
        //加载生产者的信号量，初值等于消息队列的size
        //消费者信号量，初值等于0，刚开始没有消息，
        //需要阻塞等待生产者生产消息给con_sem+1
        arrayDeque_initQueue(&queue);
        sem_init(&pro_sem,0,MQ_SIZE);
        sem_init(&con_sem,0,0);
        sem_init(&mutex,0,1);
        //创建生产者、消费者线程
        int i,max = PRO_THREAD_COUNT > CON_THREAD_COUNT ? PRO_THREAD_COUNT : CON_THREAD_COUNT;
        for(i=0;i<max;++i){
                if(i < PRO_THREAD_COUNT)
                        pthread_create(&pro_th[i],NULL,pro_handler,NULL);
                if(i < CON_THREAD_COUNT)
                        pthread_create(&con_th[i],NULL,con_handler,NULL);
        }

        for(i=0;i<max;++i){
                if(i < PRO_THREAD_COUNT)
                        pthread_join(pro_th[i],NULL);
                if(i < CON_THREAD_COUNT)
                        pthread_join(con_th[i],NULL);
        }
        sem_destroy(&pro_sem);
        sem_destroy(&con_sem);
        sem_destroy(&mutex);
        arrayDeque_destory(&queue);
        return 0;
}
```


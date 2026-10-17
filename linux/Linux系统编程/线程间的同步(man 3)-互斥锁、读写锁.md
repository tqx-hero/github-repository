### 线程间的同步(man 3)：

#### 互斥锁：

##### 互斥锁数据结构：

```c
typedef union
{
  struct __pthread_mutex_s __data;
  //预留空间，64位系统__SIZEOF_PTHREAD_MUTEX_T = 40，32位系统 = 32，整好等于结构体大小
  char __size[__SIZEOF_PTHREAD_MUTEX_T];	
  long int __align; //内存对齐
} pthread_mutex_t;

//互斥锁结构体：
struct __pthread_mutex_s
{
  int __lock;	//futex状态字：0未锁，1已锁，2有线程在等待（竞争态）
  unsigned int __count; //可重入锁的嵌套计数，普通锁只用0/1
  int __owner; 	//持有锁的线程TID
    
#ifdef __x86_64__	//64位字段
  unsigned int __nusers; //用户计数
#endif
  /* KIND must stay at this position in the structure to maintain
     binary compatibility with static initializers.  */
  int __kind;	//锁类型：普通/递归/检错/优先级保护
#ifdef __x86_64__
  short __spins;	//自旋次数（自适应自旋锁）
  short __elision;	//TSX事务锁相关
  __pthread_list_t __list;	//等待线程链表, 双向链表
# define __PTHREAD_MUTEX_HAVE_PREV      1
    
#else	//往下是32位的字段
  unsigned int __nusers;
  __extension__ union
  {
    struct
    {
      short __espins;
      short __eelision;
# define __spins __elision_data.__espins
# define __elision __elision_data.__eelision
    } __elision_data;
    __pthread_slist_t __list;
  };
# define __PTHREAD_MUTEX_HAVE_PREV      0
#endif
};

//__pthread_list_t结构体：一个双向链表
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
```

##### PTHREAD_MUTEX_INITIALIZER的定义：

PTHREAD_MUTEX_INITIALIZER是一个由宏函数:

```c
__PTHREAD_MUTEX_INITIALIZER(PTHREAD_MUTEX_TIMED_NP)
```

定义的一个宏，用于生成一个默认初始化所有属性为0的pthread_mutex_t的结构体,参数PTHREAD_MUTEX_TIMED_NP为一个枚举值，定义如下：

```c
/* Mutex types.  */
enum
{
  PTHREAD_MUTEX_TIMED_NP, //枚举值 = 0 
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP
#if defined __USE_UNIX98 || defined __USE_XOPEN2K8
  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
#endif
#ifdef __USE_GNU
  /* For compatibility.  */
  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP
#endif
};
```

__PTHREAD_MUTEX_INITIALIZER的定义如下：

```c
//不同架构下__PTHREAD_MUTEX_INITIALIZER的定义：
//1、 64位操作系统：
# define __PTHREAD_MUTEX_INITIALIZER(__kind) \
  0, 0, 0, 0, __kind, 0, 0, { 0, 0 }

//2、 32位操作系统：
# define __PTHREAD_MUTEX_INITIALIZER(__kind) \
  0, 0, 0, __kind, 0, { { 0, 0 } }

//对互斥锁默认初始化PTHREAD_MUTEX_INITIALIZER的宏定义：
#define PTHREAD_MUTEX_INITIALIZER \
 { {  __PTHREAD_MUTEX_INITIALIZER (PTHREAD_MUTEX_TIMED_NP) } }
```

##### 互斥锁的创建与销毁：

###### 创建互斥锁：

- **pthread_mutex_init () 函数使用 attr 指定的属性，初始化由 mutex 指向的互斥锁。若 attr 为 NULL，则使用默认互斥锁属性；效果等同于传入默认互斥锁属性对象的地址。初始化成功后，该互斥锁的状态变为已初始化且未加锁。**

- **尝试对一个已经初始化的互斥锁再次执行初始化，行为未定义。**

- ***当适合使用默认互斥锁属性时，可以使用宏 PTHREAD_MUTEX_INITIALIZER 初始化互斥锁。其效果等同于调用 pthread_mutex_init () 并将参数 attr 指定为 NULL 的动态初始化方式，区别是不会执行错误检查。***

- **如果传给 pthread_mutex_init () 的 attr 参数所指定的值不是指向一个已初始化的互斥锁属性对象，行为未定义。**



###### 销毁互斥锁：

- **pthread_mutex_destroy () 函数用于销毁由 mutex 指向的互斥锁对象；该互斥锁对象实际上变为未初始化状态。实现可以让 pthread_mutex_destroy () 将 mutex 指向的对象设置为无效值。**

- ***已销毁的互斥锁对象可以使用 pthread_mutex_init () 重新初始化；在销毁之后以其他方式引用该对象，行为未定义。***

- **销毁一个已初始化且处于解锁状态的互斥锁是安全的。尝试销毁一个已加锁的互斥锁，或是正被其他线程引用（例如正在 pthread_cond_timedwait () 或 pthread_cond_wait () 中使用）的互斥锁，将导致未定义行为。**

- **仅可使用 mutex 本身执行同步操作。在调用 pthread_mutex_lock ()、pthread_mutex_trylock ()、pthread_mutex_unlock () 和 pthread_mutex_destroy () 时引用 mutex 的副本，行为未定义。**

- **如果传给 pthread_mutex_destroy () 的 mutex 参数所指定的值不是指向一个已初始化的互斥锁，行为未定义。**

```c
#include <pthread.h>
/**
	使用指定的attr属性初始化一把互斥锁。如果attr=NULL，则指定一把默认互斥锁等价于静态初始化。
	mutex：互斥锁地址
	attr：互斥锁属性
	return：
		成功：0
		失败：
			EAGAIN： 系统缺少初始化另一个互斥锁所需的资源（内存除外）。
			ENOMEM： 内存不足，无法初始化该互斥锁。
			EPERM： 调用方没有执行此操作的权限。
			EINVAL： attr 所引用的属性对象设置了健壮互斥锁属性，但未设置进程共享属性。
		这些函数不会返回 [EINTR] 错误码。
*/
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

//静态初始化，创建一个初始化属性值全部为0的互斥锁。PTHREAD_MUTEX_INITIALIZER的展开参考上一部分介绍
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

###### demo:创建、销毁互斥锁

第一种：使用pthread_mutex_init(3)加载：

```c
#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//互斥锁mutex的使用
static pthread_mutex_t lock;
//2、第二种初始化默认互斥锁写法：static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int main(){
        int ret;
        if(ret = pthread_mutex_init(&lock,NULL)){ //1、第一种写法
                fprintf(stderr,"初始化互斥锁出现异常,%d\n",ret);
                exit(-1);
        }
	...
        pthread_mutex_destroy(&lock);	//销毁后可以再次init重新使用
        return 0;
}
```

第二种：静态初始化

```c
#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//互斥锁mutex的使用
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int main(){
    	...
        pthread_mutex_destroy(&lock);
        return 0;
}
```

##### pthread_mutexattr_t属性:

设置互斥锁的属性(功能类似于pthread_attr_t对pthread_t).

```c
typedef union
{
  struct
  {
    int __mutexkind;    // 锁类型（普通/递归/检错）
    int __pshared;      // 是否进程间共享
    int __protocol;     // 优先级协议：无 / 优先级继承 / 优先级天花板
    int __prioceiling;  // 优先级天花板数值
  } __data;
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  long int __align;
} pthread_mutexattr_t;

```

###### 相应的配套函数(详细情况参考man 3 pthread_mutexattr_*)：

```c
#include <pthread.h>
/**
- 作用：初始化 mutex 属性对象，设为默认属性
- 默认值：
  - type: PTHREAD_MUTEX_NORMAL 普通锁
  - pshared: `PTHREAD_PROCESS_PRIVATE` 进程内私有
  - protocol: `PTHREAD_PRIO_NONE` 无优先级保护
- 注意：使用前必须 init，不要直接使用未初始化的 attr。
*/
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
/**
	销毁属性对象，释放内部资源；销毁后 attr 变为未初始化状态，不能再用，除非重新 init。
	销毁 attr不影响已经用这个 attr 创建出来的 mutex。
*/
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);

//锁类型：
/**
	设置 mutex 类型，type 可选：
	PTHREAD_MUTEX_NORMAL：普通锁，无 owner 校验，重复 lock 直接死锁
	PTHREAD_MUTEX_RECURSIVE：递归锁，同一线程可多次 lock，嵌套计数
	PTHREAD_MUTEX_ERRORCHECK：检错锁，做 owner 校验，非法操作返回错误码
*/
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
//读取当前 attr 里的锁类型到type地址。
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);

//进程共享？
/**
	设置是否进程间共享：
	PTHREAD_PROCESS_PRIVATE（默认）：仅本进程内线程使用
	PTHREAD_PROCESS_SHARED：多进程共享（mutex 必须放在共享内存 mmap/shmget）
*/
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *attr, int *pshared);

//还有很多，详细参考man文档...
```



##### 上锁、解锁：

​		**由 mutex 引用的互斥对象，应通过调用 pthread_mutex_lock () 完成加锁，该调用返回 0 或 [EOWNERDEAD]。若该互斥锁已被其他线程锁定，则调用线程将阻塞，直到互斥锁可用。本操作返回时，mutex 所引用的互斥对象处于锁定状态，且调用线程为其持有者。**

​		**不能对owner不是自身的锁进行解锁。**

​		**只有锁类型为递归锁(PTHREAD_MUTEX_RECUSIVE)时，才能对已加锁(owner为自己线程)的互斥对象再次加锁。当锁的可重入计数__count减到0，表示该线程已对互斥对象解锁完成，此时才可以被其他线程加锁。**

​	  **pthread_mutex_trylock () 函数的功能与 pthread_mutex_lock () 等效，区别在于：如果 mutex 所引用的互斥量对象当前已被锁定（被任意线程，包括当前线程锁定），该调用会立即返回。若互斥量类型为 PTHREAD_MUTEX_RECURSIVE，且该互斥量当前归调用线程所有，则互斥量锁计数加一，同时 pthread_mutex_trylock () 函数会立即返回成功。**

```c
#include <pthread.h>
/**
	mutex：互斥对象地址。
	return：
		成功： 0
		失败:返回错误码。
*/
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

这三个函数的返回错误码：

```tex
1、pthread_mutex_lock()与pthread_mutex_trylock()共有返回错误：
	EAGAIN：无法获取锁因为已经超出递归锁的最大次数。
	EINVAL:该互斥锁创建时，协议属性取值为 PTHREAD_PRIO_PROTECT，且调用线程的优先级高于该互斥锁当前的优先级上限。
	ENOTRECOVERABLE:互斥锁所保护的状态不可恢复。
	EOWNERDEAD：该互斥锁为健壮互斥锁，持有该互斥锁的前所属线程所在进程在持有锁期间终止。调用线程将获得该互斥锁，由新的持有者负责恢复状态一致性。

2、pthread_mutex_lock()返回错误：	
	EDEADLK：互斥锁类型为 PTHREAD_MUTEX_ERRORCHECK，且当前线程已经持有该互斥锁，或者检测到了死锁
3、pthread_mutex_trylock()返回值：
	EBUSY: 加锁失败因为已经被加锁了。
4、pthread_mutex_unlock()返回错误：
	EPERM：互斥锁类型为 PTHREAD_MUTEX_ERRORCHECK 或 PTHREAD_MUTEX_RECURSIVE，或者该互斥锁是健壮互斥锁，且当前线程并不持有该互斥锁。
```

###### demo：创建2个线程，分别打印各自的语句，一共打印1000次。

```c
#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define PRINT_MAX_COUNT 1000
//消息结构体
typedef struct {
        pid_t tid;	//线程TID
        char* wordp; //要打印的消息
}print_msg_t;

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//创建2个子线程，竞争同一把锁，获取锁后可以使用打印机printer(),要求所有线程一共能打印PRINT_MAX_COUNT次
int count;
void printer(void* arg){
        print_msg_t* mptp = (print_msg_t*) arg;
        char* word = mptp->wordp;
        while(*word){
                putchar(*word);
                word++;
        }
        printf("\n");
        printf("线程: %d 打印完成，正在退出\n",mptp->tid);
}

void* th_callback(void* arg){
        char* word = (char*) arg;
        int ret;
        print_msg_t pmt;
        pmt.tid = syscall(SYS_gettid);
        pmt.wordp = (char*)arg;
        while(1){
                if(ret = pthread_mutex_lock(&lock)){
                        //加锁出现错误
                        printf("加锁出现错误，错误码 = %d\n",ret);
                        continue;
                }
                //先判断次数是否已经超过10次
                if(count >= PRINT_MAX_COUNT){
                        printf("%d次打印已完成，子线程退出...\n",PRINT_MAX_COUNT);
                        pthread_mutex_unlock(&lock);
                        break;
                }
                printer(&pmt);
                count++;
                pthread_mutex_unlock(&lock);
        }
        return NULL;
}

int main(){
        pthread_t tid[2];
        char * word[] = {"hello world","你好朋友！"};
        int i;
        for(i = 0;i < 2;++i)
                pthread_create(&tid[i],NULL,th_callback,word[i]);
        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);
        pthread_mutex_destroy(&lock);
        return 0;
}
```



##### 综合demo：使用进程共享的互斥锁，多个进程中的线程竞争这把锁，分别执行打印任务。

###### 步骤：

> 1、主进程建立、挂载共享内存，在共享内存中设置共享资源，包括互斥对象pthread_mutex_t(属性设为进程共享PTHREAD_PROCESS_SHARED)、临界资源等。
>
> 2、将SIGCHLD添加到阻塞集，方便对子进程的信号回收。
>
> 3、fork(2)创建子进程，从这里开始分叉进行。
>
> 4、主进程创建完子进程之后，设置SIGCHLD信号的处理函数、将SIGCHLD移除阻塞集、等待回收子进程PCB、卸载共享内存、设置共享内存删除标记、退出。
>
> 5、子进程执行别的任务：创建线程，线程竞争步骤1的互斥对象pthread_mutex_t(一定是在共享内存)，执行打印任务，执行完成退出。

##### 头文件\<shared.h\>:

```c
#ifndef __MY_SHARED_H_
#define __MY_SHARED_H_

#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#define PRO_COUNT 2	//子进程创建个数
#define SHMAT_FAIL ((void*) -1) //shmat失败标志的宏
#define PRINT_TOTAL_SIZE 1000	//打印任务总次数
#define THREAD_PRINT "thread_print" //子进程开启任务时的进程名称前缀
//共享资源结构体，该结构体存储在共享内存首地址
typedef struct {
        pthread_mutex_t lock; //互斥对象(进程之间共享锁的核心)
        int total_cnt;	//执行任务总次数
        int cur_cnt;	//当前已打印的次数
} shared_info_t;

#endif
```



##### 主线程代码(main_process.c)：

```c
#include "shared.h"
#include <sys/wait.h>
//记录已退出的进程数量，主进程退出标志
int exit_process;

void sigchld_handler(int signum){
        pid_t pid;
        while((pid = waitpid(-1,NULL,WNOHANG)) > 0){
                printf("已回收子进程: %d\n",pid);
                exit_process++;
        }
}
//设置共享内存中的结构体,尤其是互斥锁mutex属性为进程间共享
int set_mutex(shared_info_t* sh_info){
        //设置共享变量
        sh_info->total_cnt = PRINT_TOTAL_SIZE;
        sh_info->cur_cnt = 0;
        //获取共享内存存放的结构体
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        //设置进程共享的属性
        if(pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED)){
                fprintf(stderr,"pthread_mutexattr_setpshared error\n");
                exit(-1);
        }
        //初始化互斥对象，也就是锁
        pthread_mutex_init(&sh_info->lock,&attr);
        pthread_mutexattr_destroy(&attr); //销毁attr对象，不影响已经加载完成的互斥对象
        return 0;
}

int main(){
        key_t kt = ftok("./",1);
        int shm_id;
        //创建共享内存
        if((shm_id = shmget(kt,sysconf(_SC_PAGE_SIZE),IPC_CREAT | 0666)) == -1){
                perror("shmget error");
                exit(-1);
        }
        //设置共享内存
        shared_info_t* sh_info = (shared_info_t*)shmat(shm_id,NULL,0);
        if(sh_info == SHMAT_FAIL){
                perror("shmat error");
                goto fail_ret;
        }
        //设置mutex对象
        set_mutex(sh_info);
        //设置信号屏蔽字，先将SIGCHLD放到阻塞集，避免主线程执行途中子线程意外退出而忽略了信号
        sigset_t set,oldset;
        sigemptyset(&set);
        sigaddset(&set,SIGCHLD);
        sigprocmask(SIG_BLOCK,&set,&oldset);
        pid_t pid;
        int i = 0;
        while(i < PRO_COUNT){
                if((pid = fork()) == -1){
                        perror("fork error");
                        goto fail_ret;
                }
                //子进程开启新的任务
                if(pid == 0){
                        //子进程直接恢复屏蔽字
                        if(sigprocmask(SIG_SETMASK,&oldset,NULL)){
                                perror("child proc sigprocmask error");
                                goto fail_ret;
                        }
                        //子进程执行新的任务，新任务： ./thread_print shm_id,参数为共享内存id
                        char proc_name[64],shm_id_s[16];
                        sprintf(proc_name,THREAD_PRINT"_%d",getpid()); //设置每个子进程的启动名称，后缀为进程号
                        sprintf(shm_id_s,"%d",shm_id);
                        char * argvs[3] ={proc_name,shm_id_s,NULL};
                        execv("./"THREAD_PRINT,argvs);
                        perror("execv error");
                        goto fail_ret;
                }
                i++;
        }
        //设置信号SIGCHLD处理函数
        struct sigaction sig;
        sig.sa_flags = 0 ;   //不需要开启系统调用重启功能，因为休眠类的函数sleep()不会重启
        sig.sa_handler = sigchld_handler;
        sigemptyset(&sig.sa_mask);
        if(sigaction(SIGCHLD,&sig,NULL)){
                perror("sigaction error");
                goto fail_ret;
        }
        //将SIGCHLD从阻塞集去除,处理未决信号集
        sigprocmask(SIG_SETMASK,&oldset,NULL);
        while(exit_process < PRO_COUNT)
                sleep(10);
        //所有进程已退出，开始回收资源
        printf("所有子进程已退出，正在回收资源...\n");
        pthread_mutex_destroy(&sh_info->lock); //销毁锁
        //主进程解绑共享内存
        if(shmdt(sh_info)){
                perror("shmdt error");
                goto fail_ret;
        }
        shmctl(shm_id,IPC_RMID,NULL); //给共享内存打上删除标记，当引用为0时删除。
        return 0;
fail_ret:
        exit(-1);
}
```



##### 子进程执行的代码(thread_print.c):

```c
#include "shared.h"

//子进程执行的新程序,即开启线程执行打印任务

void* th_handler(void* arg){
        pid_t tid = syscall(SYS_gettid); //系统调用获取线程TID
        shared_info_t * shp = (shared_info_t*) arg; //传递的参数为共享资源地址
        while(1){
                //加锁
                pthread_mutex_lock(&shp->lock);
                //判断当前打印次数是否已经超过最大次数
                if(shp->cur_cnt >= shp->total_cnt){
                        printf("打印已完成，线程[%d] 退出\n",tid);
                        break;
                }
                //打印输出的内容,简化起见输出当前的次数
                printf("线程[%d]执行第[%d]次打印\n",tid,++shp->cur_cnt);//修改共享资源，计数+1
                pthread_mutex_unlock(&shp->lock);
        }
        pthread_mutex_unlock(&shp->lock); //不要忘了退出时解锁
        return NULL;
}

int main(int argc,char** argv){
        if(argc < 2){
                fprintf(stderr,"参数不足!\n");
                goto fail_ret;
        }
        pid_t pid = getpid();
        //从参数拿到共享内存ID
        int shm_id = atoi(argv[1]);
        printf("进程：%d 开始执行打印任务程序,shm_id = %d\n",getpid(),shm_id);
        //挂载共享内存到进程
        void * shm_ptr = shmat(shm_id,NULL,0);
        if(shm_ptr == SHMAT_FAIL){
                perror("shmat error");
                goto fail_ret;
        }
        //创建子线程执行打印任务
        pthread_t pth;
        pthread_create(&pth,NULL,th_handler,shm_ptr); //将共享内存的映射地址以传参形式传给子线程
        pthread_join(pth,NULL);
        printf("全部打印完成，子进程[%d]正在退出\n",pid);
        //卸载共享内存映射关系
        if(shmdt(shm_ptr)){
                perror("子进程 shmdt error");
                goto fail_ret;
        }
        return 0;

fail_ret:
        printf("子进程[%d]正在退出\n",pid);
        exit(-1);
}
```



##### 注意事项：

***1、必须保证所有进程共享同一份临界资源，所以只要是共享资源(mutex、总计数、当前状态等)都必须在共享内存/mmap。***

***2、互斥对象pthread_mutex_t只能在主进程初始化一次，其他进程直接使用，不要再初始化(再初始化后就修改了它的属性值)。***

***3、注意进程间的信号处理、阻塞集的使用。***

***4、子进程的线程中不要执行pthread_mutex_destory(2)，所有对互斥对象的初始化、回收都在主进程中操作。***

***5、注意各进程在使用完共享内存后执行卸载shmdt(2)。删除共享内存在主线程中执行。***



#### 读写锁：

**典型的读者写者问题，即资源可以让多个进程同时读，不能让资源同时写、读时写、写时读。读锁为共享锁，写锁为排它锁(也叫互斥锁)。**

**实现原理：**

> **1、锁都是信号量支持，底层还是依赖硬件的同步原语。**

> **2、同步原语是CPU在执行某些指令时需要关中断，(多核机还需要缓存一致性协议MESI)，这样在CPU执行这些指令时不会被外部中断打扰，保证指令执行一气呵成，这种特性叫做原子性。**
>
> **3、由著名计算机学家迪杰斯特拉提出的信号量解决该问题。针对初始设定的信号量(代表可以同时请求的资源的进程数量)的P(减少)、V(增加)操作都是原子操作,简称PV操作。**
>
> **4、写锁属于互斥锁，等同于mutex，即临界资源同一时刻最多只能有一个进程访问。底层是初始化信号量的值等于1，可以做到资源只能有一个进程访问。**
>
> **5、读锁属于共享锁，即多个进程可以同时拥有访问临界资源的权限(至于几个进程，由信号量的值决定)。底层还是信号量，只是信号量的值num大于1，这样就能让num个进程同时访问临界资源。**



**读写锁初始化、销毁：**

###### 初始化init：

​	**1、pthread_rwlock_init () 函数将分配使用 rwlock 指向的读写锁所需的所有资源，并将该锁初始化为未上锁状态，属性由 attr 指定。若 attr 为 NULL，则使用默认读写锁属性；效果等同于传入默认读写锁属性对象的地址。锁一旦初始化完成，可多次使用，无需重复初始化。如果调用 pthread_rwlock_init () 时指定一个已经初始化过的读写锁，结果未定义。读写锁未经初始化就投入使用，结果未定义。**

​	**2、如果 pthread_rwlock_init () 函数调用失败，rwlock 不会被初始化，且 rwlock 的内容是未定义的。**

​	**3、只能使用 rwlock 指向的对象执行同步操作。在调用 pthread_rwlock_destroy ()、pthread_rwlock_rdlock ()、pthread_rwlock_timedrdlock ()、pthread_rwlock_timedwrlock ()、pthread_rwlock_tryrdlock ()、pthread_rwlock_trywrlock ()、pthread_rwlock_unlock () 或 pthread_rwlock_wrlock () 时，如果传入该对象的副本，结果未定义。**

​	**4、当适合使用默认读写锁属性时，可以使用宏 PTHREAD_RWLOCK_INITIALIZER 来初始化读写锁。其效果等价于调用 pthread_rwlock_init () 并将 attr 参数设为 NULL 进行动态初始化，区别是不会执行错误检查。**

​	**5、如果传给 pthread_rwlock_init () 的 attr 参数所指定的值并非指向一个已初始化的读写锁属性对象，则行为未定义。**

​	**6、在再次调用 pthread_rwlock_init () 重新初始化该锁之前，后续使用此锁的行为是未定义的。**

###### 销毁锁：

​	**1、pthread_rwlock_destroy () 函数将销毁由 rwlock 指向的读写锁对象，并释放该锁占用的所有资源。**

​	**2、实现可以让 pthread_rwlock_destroy () 将 rwlock 指向的对象置为无效值。如果在任意线程持有 rwlock 的情况下调用 pthread_rwlock_destroy ()，结果未定义。尝试销毁一个未初始化的读写锁会产生未定义行为。**

> 注意事项：
>
> ​		如果实现检测到传给`pthread_rwlock_destroy()`的`rwlock`参数所指定的值并非指向一个已初始化的读写锁对象，建议该函数执行失败并返回 [EINVAL] 错误。
>
> ​		如果实现检测到传给`pthread_rwlock_init()`的`attr`参数所指定的值并非指向一个已初始化的读写锁属性对象，建议该函数执行失败并返回 [EINVAL] 错误。
>
> ​		如果实现检测到传给`pthread_rwlock_destroy()`或`pthread_rwlock_init()`的`rwlock`参数所指定的值指向一个处于加锁状态的读写锁对象，或者检测到传给`pthread_rwlock_init()`的`rwlock`参数所指定的值指向一个已经完成初始化的读写锁对象，建议该函数执行失败并返回 [EBUSY] 错误。

```c
#include <pthread.h>
/**
	rwlock: 要初始化的读写锁结构体地址。
	attr:	初始化的锁的属性。为NULL则全部为默认属性
	return：
		成功：0
		失败返回错误码有：
			EAGAIN： 系统缺少初始化另一个读写锁所需的资源（内存除外）。
			ENOMEM： 内存不足，无法初始化读写锁。
			EPERM： 调用者没有执行该操作的权限。
			这些函数不会返回 [EINTR] 错误码。
*/
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,const pthread_rwlockattr_t *restrict attr);
/**
	销毁读写锁。
	return：
		成功：0
		失败返回错误码有：
			EINVAL： 具体查看上面的注意事项。
			EBUSY：具体查看上面的注意事项。
			函数不会返回 [EINTR] 错误码
*/
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
/**
	对加锁对象解锁
	return：
		成功：0
		失败：
			EINVAL: 读写锁的对象没初始化。
			EPERM: 不是自身加的锁，没有权限解锁。
*/
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
//使用默认属性attr =NULL进行初始化的一种简便写法。
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
```

##### pthread_rwlock_t结构体：



```c
typedef union
{
  struct __pthread_rwlock_arch_t __data;	//读写锁对象
  char __size[__SIZEOF_PTHREAD_RWLOCK_T];	// 填充足够大内存空间
  long int __align;	//内存对齐，32位下4字节对齐，64位8字节对齐
} pthread_rwlock_t;

struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;
    
#ifdef __x86_64__	//64位系统
  int __cur_writer;
  int __shared;
  signed char __rwelision;
# ifdef  __ILP32__
  unsigned char __pad1[3];
#  define __PTHREAD_RWLOCK_ELISION_EXTRA 0, { 0, 0, 0 }
# else
  unsigned char __pad1[7];
#  define __PTHREAD_RWLOCK_ELISION_EXTRA 0, { 0, 0, 0, 0, 0, 0, 0 }
# endif
  unsigned long int __pad2;
  /* FLAGS must stay at this position in the structure to maintain
     binary compatibility.  */
  unsigned int __flags;
    
#else  //32位系统
  /* FLAGS must stay at this position in the structure to maintain
     binary compatibility.  */
  unsigned char __flags;
  unsigned char __shared;
  signed char __rwelision;
  unsigned char __pad2;
  int __cur_writer;
#endif
};

//默认初始化的宏函数定义
#ifdef __x86_64__
# define __PTHREAD_RWLOCK_INITIALIZER(__flags) \
  0, 0, 0, 0, 0, 0, 0, 0, __PTHREAD_RWLOCK_ELISION_EXTRA, 0, __flags
#else
# define __PTHREAD_RWLOCK_INITIALIZER(__flags) \
  0, 0, 0, 0, 0, 0, __flags, 0, 0, 0, 0
#endif
```

##### pthread_rwlockattr_t:

该结构体不对外暴露。

```c
typedef union
{
  char __size[__SIZEOF_PTHREAD_RWLOCKATTR_T];	//填充足够空间
  long int __align;	//内存对齐
} pthread_rwlockattr_t;
```



##### 申请读锁、写锁：

​	**1、必须在读写锁结构体初始化之后进行读、写锁的申请.**

​	**2、pthread_rwlock_rdlock () 函数将对 rwlock 引用的读写锁施加读锁。如果没有写者持有该锁，并且没有写者阻塞在该锁上，则调用线程会获取读锁。**



###### 读锁：

> ​		如果支持线程执行调度选项，且参与该锁的线程采用 SCHED_FIFO 或 SCHED_RR 调度策略运行时：若已有写者持有该锁，或存在优先级更高 / 相等的写者阻塞在该锁上，则调用线程不能获取此锁；否则调用线程应当获取该锁。
>
> ​		如果支持线程执行调度选项，且参与该锁的线程采用 SCHED_SPORADIC 调度策略运行时：若已有写者持有该锁，或存在优先级更高 / 相等的写者阻塞在该锁上，则调用线程不能获取此锁；否则调用线程应当获取该锁。
>
> ​		如果不支持线程执行调度选项：当没有写者持有锁，但有写者阻塞在该锁上时，调用线程能否获取锁由实现定义。若已有写者持有锁，则调用线程不能获取读锁。若未能获取读锁，调用线程将阻塞，直到可以获取该锁为止。如果调用线程在发起调用时已经持有写锁，则可能发生死锁。
>
> ​		一个线程可以在读写锁上同时持有多个读锁（即成功调用 pthread_rwlock_rdlock () 函数 n 次）。在这种情况下，应用程序必须保证该线程执行对应次数的解锁操作（即调用 pthread_rwlock_unlock () 函数 n 次）。
>
> ​		实现所保证的、可施加在单个读写锁上的最大并发读锁数量由实现定义。如果超出该上限，pthread_rwlock_rdlock () 函数可能调用失败。
>
> ​		pthread_rwlock_tryrdlock () 函数的作用与 pthread_rwlock_rdlock () 一样，都是施加读锁，区别在于：如果等效的 pthread_rwlock_rdlock () 调用会造成调用线程阻塞，则本函数会失败。pthread_rwlock_tryrdlock () 函数绝不会阻塞，它要么成功获取锁，要么立即失败并返回。
>
> ​		如果使用未初始化的读写锁调用上述任意函数，行为结果未定义。
>
> ​		如果正在等待读写读锁的线程收到信号，信号处理函数返回后，该线程会继续等待读写读锁(支持信号的重启功能)，如同未被信号中断过.

###### 写锁：

> ​		pthread_rwlock_trywrlock () 函数的作用与 pthread_rwlock_wrlock () 类似，用于施加写锁，区别在于：如果当前已有任意线程持有该读写锁（无论是读锁还是写锁），本函数会直接返回失败。
>
> ​		pthread_rwlock_wrlock () 函数用于对 rwlock 所引用的读写锁施加写锁。如果没有其他线程（读线程或写线程）持有该读写锁 rwlock，调用线程将成功获取写锁。否则，该线程会阻塞，直到能够获取锁为止。如果调用线程在发起调用时已经持有该读写锁（无论读锁还是写锁），则可能发生死锁。
>
> ​		为避免写者饥饿，部分实现会优先保障写者。
>
> ​		如果调用这些函数时传入未初始化的读写锁，行为未定义。
>
> ​		若一个正在等待读写写锁的线程收到信号，从信号处理函数返回后，该线程会继续等待该写锁，如同没有被信号中断过。

```c
#include <pthread.h>
//读锁属于递归锁，可重入
//由于这些函数在被信号中断后能够自动继续执行，所以不会返回被中断的错误(EINTR)。
/**
	rwlock: 读写锁对象。
	return：
		成功：0
		失败：
			EAGAIN：写锁已经超出最大上限。
			EDEADLK：检测出了死锁，或者当前线程已经持有了写锁
			EINVAL:如果实现检测到传递给 pthread_rwlock_rdlock () 或 pthread_rwlock_tryrdlock () 的 rwlock 参数所指定的值并未指向一个已初始化的读写锁对象，则建议该函数执行失败并返回 [EINVAL] 错误
*/
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
/**
	不会阻塞，尝试加锁，无论成功与否都会返回。
	rwlock: 读写锁对象。
	return：
		成功：0
		失败：
			EAGAIN：写锁已经超出最大上限。
			EBUSY：有写者持有该锁，或是具备相应优先级的写者正阻塞等待此锁。（此时有可能产生死锁，需要处理）
			EINVAL:如果实现检测到传递给 pthread_rwlock_rdlock () 或 pthread_rwlock_tryrdlock () 的 rwlock 参数所指定的值并未指向一个已初始化的读写锁对象，则建议该函数执行失败并返回 [EINVAL] 错误
*/
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);

/**
	尝试加写锁，不会阻塞，成功与否直接返回。
	return:
		成功：0
		失败返回错误码：
			EBUSY: 对象已经被加上了读锁或者写锁。
			EINVAL：读写锁对象未初始化。
*/
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
/**
	尝试加写锁，阻塞直到成功或者出现错误。
	return:
		成功：0
		失败返回错误码：
			EDEADLK: 检测到了死锁，或者当前线程已经拥有了该对象的读锁或写锁。
			EINVAL：读写锁对象未初始化。
*/
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
```



###### 设置读写锁属性的配套函数(与互斥锁类似)：

> 注意：\*\_setkind_np/ \*\__getkind_up这些函数属于非标准 GNU 扩展，因此函数名称中带有后缀 “\_np”（不可移植）。慎用

##### 以下的\*\_get\*与\*\_set\*函数都满足：

​	**1、读函数都会成功，返回0。**

​	**2、写函数成功返回0，失败返回EINVAL：即参数不合法。包括init与destory都不会返回EINTR(被信号中断)**

```c
#include <pthread.h>
//创建、销毁attr
/**
	return：
		ENOMEM：内存不足，无法初始化读写锁属性对象。
*/
int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);
/**
	return：
		EINVAL：参数未初始化。
*/
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
//设置、获取进程间共享属性
/**
	pshared: 进程间是否共享？
	
		PTHREAD_PROCESS_PRIVATE(枚举值 =0)：	
			进程私有，不允许多进程共享该锁。
			进程共享属性的默认值为 PTHREAD_PROCESS_PRIVATE。
			
		PTHREAD_PROCESS_SHARED(枚举值 =1)：
			允许进程间共享该读写锁。该读写锁的对象必须在多个进程可共同访问的区域。(共享内存或mmap)。		
*/
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t * restrict attr, int *restrict pshared);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr,int pshared);
//设置读写锁对读锁、写锁的类型：
//注意：这些函数属于非标准 GNU 扩展，因此函数名称中带有后缀 “_np”（不可移植）。
/**
	pthread_rwlockattr_setkind_np () 函数将 attr 指向的读写锁属性对象的 “锁类型” 属性设置为 pref 指定的值。参数 pref 可设置为下列值之一：
	PTHREAD_RWLOCK_PREFER_READER_NP(读优先):
		这是默认选项。线程可以持有多个读锁，即读锁支持递归。根据《单一 UNIX 规范》，当读线程尝试加锁、当前没有写锁但存在等待的写线程时，行为未定义。PTHREAD_RWLOCK_PREFER_READER_NP 设置为读优先，意味着即便有写线程正在等待，读线程仍可以获取请求的锁。只要一直存在读线程，写线程就会发生饥饿。
	PTHREAD_RWLOCK_PREFER_WRITER_NP(写优先,但是递归写锁会产生死锁):
		该选项本意是作为与 PTHREAD_RWLOCK_PREFER_READER_NP 对应的写锁版本。glibc 会忽略此选项，因为 POSIX 要求支持递归写锁，该选项会引发简单死锁；应当改用 PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP，该选项确保应用开发者不会获取递归读锁，从而避免死锁。
	PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP(不递归版写优先):
		将锁类型设置为此值，只要不使用递归方式加读锁，就可以避免写线程饥饿。

pthread_rwlockattr_getkind_np () 函数将 attr 指向的读写锁属性对象的锁类型属性值通过指针 pref 返回。
*/
int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *attr,int pref);
int pthread_rwlockattr_getkind_np(const pthread_rwlockattr_t *attr,int *pref);
```



###### 读写锁简单demo：10个读线程，2个写线程，读线程读取消息缓冲区，写线程写入缓冲区数据

```c
#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RD_THREAD_COUNT 10
#define WR_THREAD_COUNT 2
//读写锁的使用,创建2个写线程，10个读线程
char message_buf[512]="hello world!";
char wr_buf[512];
//初始化读写锁
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
//写线程
void* write_handler(void* arg){
        pid_t tid = syscall(SYS_gettid);
        while(1){
                pthread_rwlock_wrlock(&rwlock);//添加写锁
                sprintf(message_buf,"From[%d] > 你好朋友!!",tid);
                printf("线程[%d],写入缓冲区消息:%s\n",tid,message_buf);
                sleep(1);
                pthread_rwlock_unlock(&rwlock);
        }
        return NULL;
}
//读线程
void* read_handler(void* arg){
        pid_t tid = syscall(SYS_gettid);
        while(1){
                pthread_rwlock_rdlock(&rwlock);//尝试加读锁
                printf("线程[%d]读取缓冲区消息：%s\n",tid,message_buf);
                pthread_rwlock_unlock(&rwlock);
                sleep(1);
        }
}

int main(){
        pthread_t rth[RD_THREAD_COUNT],wth[WR_THREAD_COUNT];
        int i;
        for(i=0;i<WR_THREAD_COUNT;++i){	//这里先启动的写锁
                pthread_create(&wth[i],NULL,write_handler,NULL);
                pthread_detach(wth[i]);
        }
        for(i=0;i<RD_THREAD_COUNT;++i){	//再启动读锁,为公平起见，可以混合启动，即1个读锁1个写锁的交叉启动
                pthread_create(&rth[i],NULL,read_handler,NULL);
                pthread_detach(rth[i]);
        }
        while(1)
                sleep(10);
        pthread_rwlock_destroy(&rwlock);
        return 0;
}
```


### POSIX标准共享内存shm_*(3):

POSIX标准的共享内存相对System V的shmget/shmat/shmdt/shmctl等操作相对简单，大概就是三步：

> shm_open(3)创建、打开共享内存。

> 如果是新建的共享内存，初始大小为0，需要使用ftruncate(2)设置内存大小。

> 使用mmap(2)将共享内存映射到进程的逻辑空间。这样就可以通过返回的逻辑地址操作实际的物理空间。

> 使用完，munmap(2)解除内存直接映射。

> shm_unlink(3)删除共享内存。

至于内存映射mmap参考mmap(2).md。

shm_*函数api如下：

```c
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

/**
	name: 共享内存的标识字符串。
		为保证移植性，格式为 ：/name。
	oflag：打开方式，与open(2)相同，详情参考如下.
	mode: oflag的O_CREAT开启，新创建共享内存时设置内存的权限。
	return:
		成功：返回非负数的fd。
		失败：返回-1.
*/
int shm_open(const char *name, int oflag, mode_t mode);
/**
	删除共享内存名称，当所有进程都解除对该对象的映射之后，会释放并销毁对应的内存区域内容.
	该函数只是删除这个名字，所以只需要一个进程执行该函数就行。
	如果共享同一内存段的进程都是有父子关系，即fork()产生出的，可以在mmap映射完虚拟地址后直接调用shm_unlink()将该名称去除，以防后续出现异常退出没及时清理造成命名污染。
	但如果通信进程之间是独立进程，那就不能提前unlink，否则其他进程会映射不到相同的内存段。
*/
int shm_unlink(const char *name);

//gcc编译时要引入第三方库: -lrt
Link with -lrt.
```

#### shm_open:

​	`shm_open()` 创建并打开一个全新的 POSIX 共享内存对象，或者打开一个已存在的共享内存对象。POSIX 共享内存对象本质上是一个句柄，互不相关的进程可以利用该句柄，通过 `mmap(2)` 映射到同一块共享内存区域。`shm_unlink()` 执行反向操作：删除之前由 `shm_open()` 创建的共享内存对象。

​	`shm_open()` 的操作行为类似于 `open(2)`。`name` 参数指定待创建或打开的共享内存对象名。**为保证可移植性，共享内存对象名称格式应为 `/somename`：以斜杠开头、字符串以`\0`结尾，最长不超过 `NAME_MAX`（255）字符**；**首字符是 `/`，后面不能再包含任何斜杠**。

> ⚠️ 重点：不是普通文件路径，不能出现多级目录，只能一个斜杠 + 名字，如 `/myshm`，不能 `/shm/mem`

`oflag` 是位掩码，**必须二选一：O_RDONLY / O_RDWR**，再按需或上其他标志：

- `O_RDONLY`：只读打开。以此方式打开的共享内存对象，调用 `mmap` 时**只能映射为 PROT_READ（只读）**，不能写。
- `O_RDWR`：读写打开。

`O_CREAT`：对象不存在时创建。 对象的属主、属组取自调用进程的有效用户 ID / 有效组 ID；权限位由`mode`低 9 位决定，同时会被进程的`umask`屏蔽（umask 中置 1 的权限位会清零）。权限宏定义参考`open(2)`，头文件 `<sys/stat.h>`。

> ✅ **非常关键：新创建的共享内存对象初始长度为 0！必须调用`ftruncate`设置大小；新分配的内存字节自动初始化为 0。**

`O_EXCL`：和`O_CREAT`一起使用时，如果同名共享内存对象已存在，则返回错误。**对象存在性检查 + 创建是原子操作**，多进程并发创建时防止竞争。

`O_TRUNC`：若对象已存在，将其截断至 0 字节。

以上标志的宏定义需要引入头文件 `<fcntl.h>`。



​	调用成功时，`shm_open()` 返回一个指向共享内存对象的新文件描述符。该 fd 一定是进程内当前最小可用的未打开文件描述符。**返回的 fd 默认自带 FD_CLOEXEC 标志**：**进程执行`exec`系列函数时，这个文件描述符会自动关闭。**

这个 fd 一般后续传给`ftruncate`（新建对象必须调用）和`mmap`。 

> ✅ 重点：**mmap 映射完成之后，可以直接 close (fd)，不会影响已经建立好的内存映射**，映射依旧有效，直到`munmap`解除映射。



#### shm_unlink:

`shm_unlink()` 的行为类似于 `unlink(2)`：它删除共享内存对象的名字。**只有当所有进程都解除对该对象的映射之后**，才会释放并销毁对应的内存区域内容。 `shm_unlink()` 调用成功之后，如果再调用 `shm_open()` 打开同名对象会失败；除非指定了 `O_CREAT`，这种情况下会创建一个全新、独立的共享内存对象。



##### 出现的错误码errno如下：

**EACCES**：调用 `shm_unlink()` 删除该共享内存对象，权限不足。 **EACCES**：调用 `shm_open()` 以指定模式打开对象时权限不足；或者指定了 `O_TRUNC`，但调用者对该对象不具备写权限。

**EEXIST**：`shm_open()` 同时指定了 `O_CREAT | O_EXCL`，但指定名称的共享内存对象已经存在。

**EINVAL**：传给 `shm_open()` 的 `name` 参数不合法。

**EMFILE**：进程已达到单个进程允许打开的文件描述符上限。

**ENAMETOOLONG**：`name` 的长度超过 `PATH_MAX`。

**ENFILE**：系统全局范围内打开文件总数达到系统上限。

**ENOENT**：调用 `shm_open()` 打开不存在的对象，且未指定 `O_CREAT`。

**ENOENT**：调用 `shm_unlink()` 删除一个不存在名称的共享内存对象。

###### demo：简单的父子进程使用共享内存通信(未添加同步措施，如果需要，可使用互斥锁进行同步，互斥锁也要放到共享内存)

```c
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define SHM_NAME "/name"
#define SHM_BUF_SIZE 1024
#define SHM_TRUNCATE_SIZE 1024
//进程间的通信结构体
typedef struct {
        pid_t pid;
        char buf[SHM_BUF_SIZE];
} shminfo_t;

//使用POSIX标准的共享内存
int main(){
        pid_t pid;
        int fd;
        shminfo_t* shmp;
        off_t fd_size = SHM_TRUNCATE_SIZE;//共享内存大小，不存在内存段需要创建时默认是宏，存在内存段时更改为内存段实际大小
        fd = shm_open(SHM_NAME,O_CREAT | O_RDWR | O_EXCL,0666);//以 O_CREAT | O_EXCL打开，存在时直接使用
        if(fd == -1){
                //如果内存段已存在，直接打开
                if(errno == EEXIST){
                        fd = shm_open(SHM_NAME,O_RDWR,0666);
                        //获取内存段的大小
                        struct stat st;
                        fstat(fd,&st);
                        fd_size = st.st_size; //内存段存在，更改内存段的实际大小
                        printf("内存段已存在，大小 ：%ld\n",fd_size);
                }
                else{
                        perror("open shared mem error");
                        exit(-1);
                }
        }else{ //内存段不存在，创建成功，设置内存段的大小=SHM_TRUNCATE_SIZE
                if(ftruncate(fd,SHM_TRUNCATE_SIZE)){
                        perror("truncate shm error");
                        exit(-1);
                }
        }
    	//映射到进程虚拟空间,MAP_SHARED方式子进程会继承它的地址。
        shmp = (shminfo_t*) mmap(NULL,fd_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
        close(fd);//提前关闭fd，避免出现fd泄露
        shm_unlink(SHM_NAME); //fork()的子进程因为有继承关系，所以可直接先把名称去掉
        if(!(pid = fork())){//子进程
                shmp->pid = getpid();
                strcpy(shmp->buf,"你好我好大家好....");
                if(munmap(shmp,fd_size)){
                        perror("子进程解除内存映射mmap失败:");
                        exit(-1);
                }
                exit(0);
        }else{//父进程
                sleep(1);
                printf("共享内存内容：%d > %s\n",shmp->pid,shmp->buf);
                munmap(shmp,fd_size);
        }
        return 0;
}
```

###### demo:对上面的进程通信进行信号量的同步，实现子进程写完，父进程读取，两者交替进行

```c
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#define SHM_NAME "/name"
#define SHM_BUF_SIZE 1024
#define SHM_TRUNCATE_SIZE 1024
//定义信号量结构体，该结构体必须放到共享内存
typedef struct {
        sem_t full,empty;
} sem_info_t;

typedef struct {
        pid_t pid;
        int num;
        char buf[SHM_BUF_SIZE];
} shminfo_t;

//使用POSIX标准的共享内存
//父子进程进行简单的同步
int main(){
        pid_t pid;
        int fd;
        char* start_ptr;
        shminfo_t* shmp;
        off_t fd_size = SHM_TRUNCATE_SIZE;
//      pthread_mutex_t *mutex;
        sem_info_t * semp;
        fd = shm_open(SHM_NAME,O_CREAT | O_RDWR | O_EXCL,0666);
        if(fd == -1){
                //如果内存段已存在，直接打开
                if(errno == EEXIST){
                        fd = shm_open(SHM_NAME,O_RDWR,0666);
                        //获取内存段的大小
                        struct stat st;
                        fstat(fd,&st);
                        fd_size = st.st_size;
                        printf("内存段已存在，大小 ：%ld\n",fd_size);
                }
                else{
                        perror("open shared mem error");
                        exit(-1);
                }
        }else{ //内存段不存在，创建成功，设置内存段的大小
                if(ftruncate(fd,SHM_TRUNCATE_SIZE)){
                        perror("truncate shm error");
                        exit(-1);
                }
        }
        start_ptr = (char*) mmap(NULL,fd_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
        close(fd);
        shm_unlink(SHM_NAME); //fork()的子进程因为有继承关系，所以可直接先把名称去掉
        //在共享内存设置互斥对象，用于后续父子进程同步,设定共享内存起始偏移0位置为互斥对象的地址
        //mutex = (pthread_mutex_t*)start_ptr;
        //pthread_mutex_init(mutex,NULL);
        //*mutex = PTHREAD_MUTEX_INITIALIZER;
        //设置信号量，初始full =0，empty = 1，均为进程共享。
        semp = (sem_info_t*) start_ptr;
        sem_init(&semp-> full,1,0);
        sem_init(&semp-> empty,1,1);
        //给出可用内存的起始地址,即从起始偏移+ 信号量对象大小
        shmp =(shminfo_t*)(start_ptr + sizeof(sem_info_t));
        if(!(pid = fork())){//子进程
                int num=0;
                shmp->pid = getpid();
                while(1){
                        //pthread_mutex_lock(mutex);
                        sem_wait(&semp->empty);
                        shmp->num = num;
                        sprintf(shmp->buf,"这是第[%d]条消息.\n",num);
                        ++num;
                        //pthread_mutex_unlock(mutex);
                        sem_post(&semp->full);
                }
                if(munmap(start_ptr,fd_size)){
                        perror("子进程解除内存映射mmap失败:");
                        exit(-1);
                }
                exit(0);
        }else{//父进程
                while(1){
//                      pthread_mutex_lock(mutex);
                        sem_wait(&semp->full);
                        printf("共享内存内容：%d > [%d] %s\n",shmp->pid,shmp->num,shmp->buf);
//                      pthread_mutex_unlock(mutex);
                        sem_post(&semp->empty);
                }
                //在解除内存映射前销毁信号量
                sem_destroy(&semp->full);
                sem_destroy(&semp->empty);
                munmap(start_ptr,fd_size);
        }
//      pthread_mutex_destroy(mutex);
        return 0;
}
```


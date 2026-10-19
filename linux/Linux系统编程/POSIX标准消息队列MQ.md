### POSIX标准消息队列MQ：

#### 创建、打开mq：

```c
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
typedef int mqd_t;
/**
	mq_open () 用于创建一个新的 POSIX 消息队列，或者打开一个已存在的队列。
	name: 消息队列唯一标识。关于名称的构成细节，请参考 mq_overview (7)。总的来说，name格式： /NAME。NAME为任意单词字符。
	oflag：指定调用行为。（引入 <fcntl.h> 头文件可获得这些标志值的定义。）oflag 中必须指定下列标志中的一个：
		O_RDONLY：打开队列用于接收消息。
		O_WRONLY：仅打开队列用于发送消息。
		O_RDWR：打开队列，既可发送消息也可接收消息。
		除了以上必须得一个，还可以位或以下标志位：
		
		O_CLOEXEC：（自 Linux 2.6.26 起）为消息队列描述符设置执行时关闭标志。关于该标志的作用，请参见 open (2)。
		O_CREAT：如果消息队列不存在，则创建该队列。消息队列的所有者（用户 ID）将设置为调用进程的有效用户 ID。所属组（组 ID）设置为调用进程的有效组 ID。
		O_EXCL：如果 oflag 指定了 O_CREAT，且同名队列已存在，则调用失败并返回 EEXIST 错误。
		O_NONBLOCK：以非阻塞模式打开队列。当 mq_receive (3) 和 mq_send (3) 在普通情况下会发生阻塞时，这些函数会直接失败并返回 EAGAIN 错误。
		
	return:
		成功： 返回消息队列的文件描述符
		失败：返回 (mqd_t)-1,错误码填充errno
		错误码如下：
		EACCES：
        	1、队列存在，但调用进程没有权限以指定模式打开该队列；
        	2、名称包含多个斜杠。
		EEXIST： 在文件状态标志中同时指定了 O_CREAT 和 O_EXCL，但已存在同名队列。
		EINVAL： 名称不符合 mq_overview (7) 中规定的格式。
			文件状态标志中指定了 O_CREAT，且 attr 不为空，但 attr->mq_maxmsg 或 attr->mq_msgsize 无效。这两个字段的值都必须大于 0。对于非特权进程（不具备 CAP_SYS_RESOURCE 能力），attr->mq_maxmsg 必须小于等于 msg_max(默认为10，可修改，文件路径：/proc/sys/fs/mqueue/msg_max) 限制，attr->mq_msgsize 必须小于等于 msgsize_max 限制。此外，即使是特权进程，attr->mq_maxmsg 也不能超过 HARD_MAX 限制。（有关这些限制的详细信息参见 mq_overview (7)。）
		EMFILE： 已达到单个进程可打开的文件描述符与消息队列描述符数量上限（参见 getrlimit (2) 中对 RLIMIT_NOFILE 的说明）。
		ENAMETOOLONG：名称过长。
		ENFILE： 已达到系统全局可打开文件与消息队列的总数上限。
		ENOENT： 
			1、文件状态标志中未指定 O_CREAT，且不存在该名称的队列。
		    2、名称仅为 “/”，后面没有其他字符。
		ENOMEM： 内存不足。
		ENOSPC： 没有足够空间创建新消息队列。该错误大概率是触及了 queues_max 限制；详见 mq_overview (7)。
*/
mqd_t mq_open(const char *name, int oflag);
/**
	指定oflag有O_CREAT选项时，需要补充后两个参数，给新建的消息队列设置权限与属性.
	mode: 同系统调用open(2)的权限项相同。详情参考系统调用open(2)
	attr: 消息队列的属性，为NULL会按照系统默认的配置项进行配置，默认配置项以文件形式储存在内存，具体如下：
		结构体字段如下显示。其中需要设置的有2个字段：mq_maxmsg、mq_msgsize,其它2个字段在新建时自动忽略。
		要设置的这两个字段的值都必须大于 0。至于取值限制，与msg_../msgsize_..的文件设置相关，参考如下：
		
		1、/proc/sys/fs/mqueue/msg_default（Linux 3.5 起提供）：
		该文件用于设置：调用 mq_open (3) 创建消息队列且 attr 参数设为 NULL 时，新队列 mq_maxmsg 的取值。此文件默认值为 10。其最小值、最大值与 /proc/sys/fs/mqueue/msg_max 保持一致。新队列默认的 mq_maxmsg 取值为 msg_default 和 msg_max 两者中的较小值。在 Linux 2.6.28 之前，mq_maxmsg 默认值为 10；Linux 2.6.28 至 Linux 3.4 版本，默认值采用 msg_max 限制所定义的值。
		2、/proc/sys/fs/mqueue/msg_max：
		该文件用于查看和修改单个消息队列最大消息数量的上限。该值作为 mq_open (3) 入参 attr->mq_maxmsg 的上限阈值。msg_max 默认值为 10，最小值为 1（2.6.28 之前内核最小值为 10），上限为 HARD_MSGMAX。特权进程（拥有 CAP_SYS_RESOURCE 权限）不受 msg_max 限制，但仍然受 HARD_MSGMAX 上限约束。
		HARD_MSGMAX 的定义随内核版本变化：
			Linux 2.6.32 及更早版本：131072 /sizeof (void *)
			Linux 2.6.33 至 3.4 版本：(32768 * sizeof (void *) / 4)
			Linux 3.5 起：65536
		3、/proc/sys/fs/mqueue/msgsize_default（Linux 3.5 起提供）：
		该文件用于设置：调用 mq_open (3) 创建消息队列且 attr 参数设为 NULL 时，新队列 mq_msgsize 的取值。该文件默认值为 8192（字节）。其最小值、最大值与 /proc/sys/fs/mqueue/msgsize_max 保持一致。若 msgsize_default 大于 msgsize_max，则新队列默认 mq_msgsize 会被限制在 msgsize_max 上限。Linux 2.6.28 之前，mq_msgsize 默认值为 8192；Linux 2.6.28 至 Linux 3.4 版本，默认值采用 msgsize_max 限制所定义的值。
		4、/proc/sys/fs/mqueue/msgsize_max：
		该文件可用于查看和修改消息最大长度的上限。该值是 mq_open (3) 传入参数 attr->mq_msgsize 的上限。msgsize_max 默认值为 8192 字节。最小值为 128（2.6.28 之前的内核中为 8192）。msgsize_max 的上限随内核版本变化：
		Linux 2.6.28 之前，上限为 INT_MAX。
		Linux 2.6.28 至 3.4 版本，上限为 1048576。
		Linux 3.5 及之后版本，上限为 16777216（HARD_MSGSIZEMAX）。
		特权进程（具备 CAP_SYS_RESOURCE 权限）不受 msgsize_max 限制，但自 Linux 3.5 起，特权进程仍需要遵守 HARD_MSGSIZEMAX 硬性上限。
		5、/proc/sys/fs/mqueue/queues_max：
			该文件可用于查看和修改系统范围内可创建的消息队列数量上限。queues_max 的默认值为 256。该限制没有硬性上限；拥有特权（CAP_SYS_RESOURCE）的进程可以突破此限制（但参见缺陷说明）。
			
		RLIMIT_MSGQUEUE 资源限制用于限制属于进程真实用户 ID 的所有消息队列可占用的空间大小，相关说明参见 getrlimit (2)。
	return：
		同 mq_open()
*/
mqd_t mq_open(const char *name, int oflag, mode_t mode,struct mq_attr *attr);

/**
	用于关闭消息队列的文件描述符。
	如果调用进程已通过消息队列描述符mqdes向该消息队列绑定了通知请求（参见mq_notify(3)），则该请求会被移除，此时其他进程便可绑定通知请求。
	return：
		成功：0
		失败：-1，填充errno。
		EBADF：mqdes文件描述符不合法。
*/
int mq_close(mqd_t mqdes);
/**
	mq_unlink () 会删除指定的消息队列名称。消息队列名称会立即被移除。
	一旦其他所有已打开该队列的进程关闭（mq_close）其指向该队列的描述符，队列本身就会被销毁。
	注意：该函数只会删除name这个唯一标识，给mq打上删除标记，只有当所有进程打开该消息队列的fd被close后才会销毁这mq。
	return：
		成功：0
		失败：-1，填充errno。
			EACCES： 调用进程没有权限删除该消息队列。
			ENAMETOOLONG：名称过长。
			ENOENT： 不存在具有指定名称的消息队列。
*/
int mq_unlink(const char *name);
//编译时必须引入第三方库
Link with -lrt.
```

> 如果 oflag 指定了 O_CREAT，则必须额外提供两个参数。mode 参数指定新队列的权限，规则同 open (2)。（引入 <sys/stat.h> 头文件可获得权限位的符号定义。）权限设置会与进程的文件权限掩码（umask）做掩码运算。

attr 所指向的 mq_attr 结构体中的各个字段，用于指定消息队列允许的最大消息数量与单条消息的最大长度。该结构体定义如下：

```c
struct mq_attr {
    long mq_flags;       /* 标志位（mq_open()会忽略此字段） */
    long mq_maxmsg;      /* 队列上的最大消息数 */
    long mq_msgsize;     /* 单条消息最大长度（字节） */
    long mq_curmsgs;     /* 当前队列中的消息数量（mq_open()会忽略此字段） */
};
```

> 调用 mq_open () 时，仅使用 mq_maxmsg 和 mq_msgsize 字段，其余字段的值会被忽略。

> 如果 attr 为 NULL，则创建消息队列时会采用系统实现定义的默认属性。自 Linux 3.5 版本起，可以通过两个 /proc 文件来控制这些默认值；详细信息参见 mq_overview (7)。

> mq_open () 库函数基于同名系统调用实现。该库函数会检查名称是否以斜杠（/）开头，若不是则返回 EINVAL 错误。内核系统调用要求名称不能带有前置斜杠，因此 C 库函数会将去掉前置斜杠后的名称（即 name+1）传递给该系统调用。

#### 发送消息：

```c
#include <mqueue.h>
#define MQ_PRIO_MAX     32768	//定义消息的优先级最大值，实际上是该宏-1，即32767
/**
	发送消息。如果描述符无设置O_NONBLOCK ，队列满了会阻塞，直到发送成功或出错。
	mqdes：消息队列的文件描述符
	msg_ptr: 发送消息的地址。
	msg_len：发送消息长度，该长度必须不超过队列允许的最大限制mq_msgsize(默认8192B)。允许长度为零的消息。
	msg_prio: 指定本条消息的优先级(0~32767).值越大，优先级越高，消息会按照优先级降序排列，同等级的消息，旧的排在前面，符合队列FIFO特性。
		
	return：
		0：成功
		-1：失败，并填充errno。
		EAGAIN： 队列已满，并且 mqdes 引用的消息队列描述符设置了 O_NONBLOCK 标志。
		EBADF： mqdes 中指定的描述符无效，或者该描述符不是以可写模式打开。
		EINTR： 该调用被信号处理函数中断；参见 signal (7)。
		EINVAL： 本调用本应阻塞，且 abs_timeout 参数无效：原因是 tv_sec 小于 0，或者 tv_nsec 小于 0 或大于 10 亿。
		EMSGSIZE：msg_len 大于消息队列的 mq_msgsize 属性值。
		ETIMEDOUT：消息完成传输前，调用已超时。
*/
int mq_send(mqd_t mqdes, const char *msg_ptr,size_t msg_len, unsigned int msg_prio);
#include <time.h>
#include <mqueue.h>
/**
	mq_timedsend () 的行为与 mq_send () 基本一致.
	区别在于：当队列已满，且消息队列描述符未启用 O_NONBLOCK 标志时，abs_timeout 指向一个结构体，用于指定本次调用的阻塞时长。该值是自纪元时间（1970-01-01 00:00:00 +0000 (UTC)）起的绝对超时时间，包含秒与纳秒。
	超时返回值=-1,errno = ETIMEDOUT。
*/
int mq_timedsend(mqd_t mqdes, const char *msg_ptr,size_t msg_len, unsigned int msg_prio,const struct timespec *abs_timeout);

Link with -lrt.
```



> msg_prio 参数为非负整数，用于指定本条消息的优先级。队列中的消息按优先级降序排列；相同优先级下，新消息排在同优先级旧消息之后。消息优先级取值范围的详细说明请参见 mq_overview (7)。

> 每条消息都带有关联的优先级，消息总是按优先级从高到低发送到接收进程。消息优先级范围为 0（最低）到 sysconf (_SC_MQ_PRIO_MAX) - 1（最高）。在 Linux 系统中，sysconf (_SC_MQ_PRIO_MAX) 返回 32768，但 POSIX.1 标准仅要求实现至少支持 0 到 31 的优先级；部分实现仅提供该范围。

若消息队列已满（即队列内消息数量等于队列的 mq_maxmsg 属性），默认情况下 mq_send () 会阻塞，直到队列有足够空间存入消息，或是该调用被信号处理函数中断。如果消息队列描述符启用了 O_NONBLOCK 标志，则该调用会立即失败并返回 EAGAIN 错误。

mq_timedsend () 的行为与 mq_send () 基本一致，区别在于：当队列已满，且消息队列描述符未启用 O_NONBLOCK 标志时，abs_timeout 指向一个结构体，用于指定本次调用的阻塞时长。该值是自纪元时间（1970-01-01 00:00:00 +0000 (UTC)）起的绝对超时时间，包含秒与纳秒，结构体定义如下：

```c
struct timespec {
    time_t tv_sec;        /* 秒 */
    long   tv_nsec;       /* 纳秒 */
};
```

如果消息队列已满，且调用发生时超时时间已到期，mq_timedsend () 会立刻返回。

#### 接收消息：

```c
#include <mqueue.h>
/**
	按照优先级接收消息，如果优先级为NULL，获取最旧的那个消息，不为NULL，则获取对应优先级的最旧的那个消息。
	mqdes: 队列的文件描述符
	msg_ptr: 从mq接收消息拷贝到的地址。
	msg_len: msg_ptr的大小，该值必须大于等于mq_msgsize的属性值（参见 mq_getattr (3)），以保证能放得下一条消息。
	msg_prio: 消息的优先级的地址。
		=NULL时，获取最旧的那个消息，不分优先级。
		不为NULL，获取等于该缓冲区所在优先级的最旧的消息。
	return:
		成功： 返回消息的真实字节数。
		失败：-1，填充的errno如下：
			EAGAIN： 队列为空，且 mqdes 引用的消息队列描述符已设置 O_NONBLOCK 标志。
			EBADF： mqdes 指定的描述符无效，或未以读模式打开。
			EINTR： 调用被信号处理函数中断；参见 signal (7)。
			EINVAL： 本应阻塞该调用，但 abs_timeout 参数无效，原因是 tv_sec 小于 0，或 tv_nsec 小于 0、又或者大于 10 亿。
			EMSGSIZE：msg_len 小于消息队列的 mq_msgsize 属性值。
			ETIMEDOUT：在完成消息传输前，调用已超时。
*/
ssize_t mq_receive(mqd_t mqdes, char *msg_ptr,size_t msg_len, unsigned int *msg_prio);

#include <time.h>
#include <mqueue.h>
//与mq_receive()功能相同，多了一个最大等待时间，时间一到即使还没收到消息也会返回。此时返回值=-1,errno = ETIMEDOUT
ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr,size_t msg_len, unsigned int *msg_prio,
                        const struct timespec *abs_timeout);

Link with -lrt.
```



mq_receive () 会从消息队列描述符 mqdes 所指向的消息队列中，取出优先级最高且最旧的消息，并将其存入 msg_ptr 指向的缓冲区。msg_len 参数指定 msg_ptr 所指向缓冲区的大小；该值必须大于或等于队列的 mq_msgsize 属性（参见 mq_getattr (3)）。若 msg_prio 不为空，则其指向的缓冲区用于返回所接收消息的优先级。

如果队列为空，默认情况下 mq_receive () 会阻塞，直到有消息可用，或者该调用被信号处理函数中断。若消息队列描述符启用了 O_NONBLOCK 标志，则该调用会立即失败并返回 EAGAIN 错误。



#### 设置/获取消息队列mq的属性：

```c
#include <mqueue.h>
/**
	根据文件描述符获取消息队列的属性值。
	mqdes: 消息队列文件描述符
	attr: 存放消息队列属性值的缓冲区地址。	
    return：
		0：成功
		-1：失败，并填充errno。
			EBADF：文件描述符不合法。
			EINVAL： newattr->mq_flags 中包含 O_NONBLOCK 以外的置位标志。
*/
int mq_getattr(mqd_t mqdes, struct mq_attr *attr);
/**
	虽然名称为设置消息队列的属性，但实际上只能修改消息队列的mq_flags标志位，即队列是否是阻塞队列，其他字段使用mq_setattr()时都会被忽略。
*/
int mq_setattr(mqd_t mqdes, const struct mq_attr *newattr,struct mq_attr *oldattr);

struct mq_attr {
    long mq_flags;       /*  0 或 O_NONBLOCK，正常无其他取值 */
    long mq_maxmsg;      /* 队列上的最大消息数 */
    long mq_msgsize;     /* 单条消息最大长度（字节） */
    long mq_curmsgs;     /* 当前队列中的消息数量 */
};

Link with -lrt.
```

下面是mq_attr属性详解：

> mq_flags 字段包含与已打开消息队列描述符相关的标志。该字段在通过 mq_open (3) 创建队列时初始化。此字段中唯一可出现的标志为 O_NONBLOCK。

> mq_maxmsg 和 mq_msgsize 字段在通过 mq_open (3) 创建消息队列时进行设置。mq_maxmsg 字段为使用 mq_send (3) 放入队列的消息数量上限。mq_msgsize 字段为可放入队列的消息大小上限。这两个字段的值都必须大于 0。mq_overview (7) 中介绍了两个用于限制这两个字段取值上限的 /proc 文件。

> mq_curmsgs 字段返回队列中当前保存的消息数量。

> mq_setattr () 利用 newattr 指向的 mq_attr 结构体中提供的信息设置消息队列属性。唯一可修改的属性是 mq_flags 中的 O_NONBLOCK 标志位设置。newattr 中的其他字段会被忽略。若 oldattr 不为空，则其指向的缓冲区用于返回一个 mq_attr 结构体，该结构体包含与 mq_getattr () 返回内容相同的信息



###### 简单demo：API的使用，包括：



```c
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#define MQ_NAME "/mq"
#define EXIT(__MSG,__CODE) perror(__MSG); \
                        exit(__CODE)
//POSIX标准的mq使用demo
int main(){
        //创建消息队列
        mqd_t mqfd;
        long int buffer_size;//缓冲区上限，这里使用的是消息体长度上限。
        struct mq_attr attr;
        attr.mq_maxmsg = 10; //设置队列容纳最大消息数
        attr.mq_msgsize = 1024;//消息体的长度上限
        size_t rcv_len;//实际接收消息的长度
//      可以在创建消息队列时通过oflag设置它是否为非阻塞状态,但创建时不能通过attr设置非阻塞
//      创建阶段只能设置attr的mq_maxmsg与mq_msgsize这两个属性
        //if((mqfd = mq_open(MQ_NAME,O_RDWR | O_CREAT | O_EXCL , 0666,NULL)) < 0){ //使用默认属性创建的mq
        //使用attr设置mq的属性
        if((mqfd = mq_open(MQ_NAME,O_RDWR | O_CREAT | O_EXCL , 0666,&attr)) < 0){ // 使用attr属性设置mq
                if(errno == EEXIST)//队列存在，直接打开
                        mqfd = mq_open(MQ_NAME,O_RDWR); //以阻塞模式开启
                else{
                        EXIT("mq open error",EXIT_FAILURE);
                }
        }
        if(mq_unlink(MQ_NAME)){
                EXIT("unlink mq name error",EXIT_FAILURE);
        }
        //获取消息队列的属性值
        if(mq_getattr(mqfd,&attr)){
                EXIT("get mq attr error",EXIT_FAILURE);
        }
    	//可以通过mq_setattr修改消息队列是否能被阻塞，而且仅能修改这一项，至于队列大小与消息的个数无法再次更改
    
        buffer_size = attr.mq_msgsize;//获得单条消息的最大长度。
        //输出属性值
        //printf("mq_flags is nonblock ?: %d, mq_maxmsg = %ld,mq_msgsize = %ld,mq_curmsgs = %ld\n",attr.mq_flags == O_NONBLOCK,
        //      attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);

        char * bufp = (char*) malloc(buffer_size);//建议申请的内存空间等于属性值attr.mq_msgsize
        if(!bufp){
                EXIT("malloc error",EXIT_FAILURE);
        }
        //创建子进程
        if(!fork()){
                //子进程发送消息
                sprintf(bufp,"这是第一条消息...");
                if(mq_send(mqfd,bufp,strlen(bufp) + 1,0)){//发送消息，第三个参数长度不能超过队列运行的消息长度上限
                        free(bufp);
                        EXIT("send msg error",EXIT_FAILURE);
                }
                free(bufp);
                if(mq_close(mqfd)){
                        EXIT("close mq error",EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
        }
        //父进程接收消息，注意：接收消息的len字段必须不小于mq_msgsize属性值,返回值收到的字节数等于实际消息长度。
        if((rcv_len = mq_receive(mqfd,bufp,buffer_size,NULL)) == -1){
                free(bufp);
                EXIT("rcv msg error",EXIT_FAILURE);
        }
        printf("消息字节数 = %ld\n",rcv_len);
        printf("主线程收到的消息： %s\n",bufp);
        free(bufp);
        if(mq_close(mqfd)){
                EXIT("close mq error",EXIT_FAILURE);
        }
        return 0;
}
```



#### mq的唤醒服务：给进程注册消息驱动(主要是非阻塞模式下的异步处理)

> mq_notify () 允许调用进程注册或注销异步通知：当消息队列描述符 mqdes 所指向的空消息队列收到新消息时，触发该通知。

##### 下面是简单介绍，详情参考mq_notify(3):

```c
#include <mqueue.h>
/**
	注册信号驱动，当消息队列从空到出现消息时，给该进程异步通知，进行相关处理。
	mqdes: 消息队列描述符。
	sevp：信号处理配置项的地址。
		sigev_notify:指定通知的执行方式。如下：
			SIGEV_NONE：空通知，调用进程被注册为通知的接收目标，但消息到达时，不会发送任何通知。
			SIGEV_SIGNAL：
				通过发送 sigev_signo 中指定的信号来通知进程。通用详情参见 sigevent (7)。
				siginfo_t 结构体的 si_code 字段将被设置为 SI_MESGQ。
				此外，si_pid 将被设置为发送消息进程的进程 ID，si_uid 将被设置为发送消息进程的真实用户 ID。
			SIGEV_THREAD：消息送达时，创建新线程调用 sigev_notify_function，其行为如同该函数作为新线程的入口函数。详情参见 sigevent (7)。
	仅有一个进程可以注册接收来自消息队列的通知。
	
	return:
		成功：0
		失败：-1，填充errno。
			EBADF: 在 mqdes 中指定的消息队列描述符无效。
			EBUSY: 已有另一个进程注册接收该消息队列的通知。
			EINVAL:
            	sevp->sigev_notify 不是允许取值之一；或者 sevp->sigev_notify 为 SIGEV_SIGNAL，但 sevp->sigev_signo 不是有效的信号编号。
            	若 sevp 为空，且调用进程当前并未注册接收队列 mqdes 的通知.
			ENOMEM: 内存不足。
*/
int mq_notify(mqd_t mqdes, const struct sigevent *sevp);

Link with -lrt.
```

```c
//详情参考sigevent(7)
#include <signal.h>

union sigval {          /* 随通知传递的数据 */
    int     sival_int;         /* 整型值 */
    void   *sival_ptr;         /* 指针值 */
};

struct sigevent {
    int          sigev_notify; /* 通知方式 */
    int          sigev_signo;  /* 通知信号 */
    union sigval sigev_value;  /* 随通知传递的数据,可使用它传递参数 */
    void       (*sigev_notify_function) (union sigval); /* 用于线程通知的函数（SIGEV_THREAD） */
    void        *sigev_notify_attributes;/* 通知线程的属性（SIGEV_THREAD） */
    pid_t        sigev_notify_thread_id;/* 通知线程的属性ID（SIGEV_THREAD） */
};
```



> sevp 参数是指向 sigevent 结构体的指针。关于该结构体的定义与通用详情，请参见 sigevent (7)。

> 若 sevp 为非空指针，则 mq_notify () 将注册调用进程，使其接收消息通知。sevp 所指向的 sigevent 结构体中的 sigev_notify 字段指定通知的执行方式。
>
> sevp 参数是指向 sigevent 结构体的指针。有关该结构体的定义和通用详细信息，请参见 sigevent (7)。

> 如果 sevp 为 NULL，且调用进程当前已注册接收此消息队列的通知，则该注册将被移除；之后其他进程可以注册接收该队列的消息通知。

> **仅有一个进程可以注册接收来自消息队列的通知。**

> 消息通知仅在有新消息到达且队列此前为空时触发。如果调用 mq_notify () 时队列非空，则只有当队列被清空后再有新消息到达，才会触发一次通知。

> 如果有其他进程或线程正通过 mq_receive (3) 等待从空队列读取消息，则消息通知注册会被忽略：消息会发送给调用 mq_receive (3) 的该进程或线程，而消息通知注册仍然有效。

> **通知只会触发一次**：通知发送后，对应的通知注册会被移除，其他进程便可注册消息通知。如果收到通知的进程希望接收下一次通知，可以调用 mq_notify () 再次申请通知。**该操作应在清空队列中所有未读消息之前完成。（将队列设置为非阻塞模式，便于在队列清空后读取消息时不会发生阻塞。）**

#### demo: 使用notify唤醒注册信号驱动的进程，并执行相关回调函数。

##### 示例1：信号发送行为设置为：SIGEV_THREAD

###### 注意：

> 1、使用SIGEV_THREAD选项，即通过回调函数异步处理时，执行异步处理的线程不是主线程，而是一个创建的新线程。
>
> 2、在设置struct sigevent结构体时，新线程属性：sigev_notify_attributes的指针一定要有效，否则就置为NULL，即等同于pthread_create()的属性值为NULL。

下面是主函数:<mq_rcv.c>。该函数作用是创建一个消息队列，注册信号驱动事件，然后等待消息队列由空到出现消息，内核会创建新线程执行回调函数，回收资源后退出进程。

```c
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <signal.h>
#define MQ_NAME "/mq"
#define ERR_EXIT(__MSG) perror(__MSG); \
                        exit(EXIT_FAILURE)
//mq_notify()的demo

void sig_handler(union sigval sig_val){
        printf("回调函数处理线程ID = %ld\n",syscall(SYS_gettid));//获取的线程号TID不是主线程的TID，这是一个新线程执行的
        mqd_t mqfd = *((mqd_t*)sig_val.sival_ptr);
        struct mq_attr attr;
        if(mq_getattr(mqfd,&attr)){
                ERR_EXIT("get mq attr error");
        }
        char* buf = (char*) malloc(attr.mq_msgsize);
        ssize_t rcv_len;
        if((rcv_len = mq_receive(mqfd,buf,attr.mq_msgsize,NULL)) == -1){
                ERR_EXIT("rcv mq error");
        }
        mq_unlink(MQ_NAME);
        mq_close(mqfd);
        printf("收到的字节数 = %ld\n",rcv_len);
        printf("消息内容: %s\n",buf);
        free(buf);
        exit(EXIT_SUCCESS);
}

int main(){
        mqd_t mqfd;
        if((mqfd = mq_open(MQ_NAME,O_CREAT | O_RDWR,0666,NULL)) == (mqd_t)-1){
                ERR_EXIT("open mq error");
        }
        printf("进程ID = %d\n",getpid());
        //设置信号驱动
        struct sigevent event;
        event.sigev_notify_attributes = NULL;
        event.sigev_notify = SIGEV_THREAD;
        event.sigev_notify_function = sig_handler;
        event.sigev_value.sival_ptr = &mqfd;
        if(mq_notify(mqfd,&event)){
                ERR_EXIT("mq notify error");
        }
        pause();
}
```

下面是简单的发送函数：<mq_snd.c>

```c
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#define MQ_NAME "/mq"

int main(){
        mqd_t mqfd;
        mqfd = mq_open(MQ_NAME,O_WRONLY);
        if(mqfd == (mqd_t)-1){
                perror("open mq error");
                exit(EXIT_FAILURE);
        }
        if(mq_unlink(MQ_NAME)){
                perror("unlink mq error");
                exit(EXIT_FAILURE);
        }
        char buf[] = "你好吗，老朋友!";
        if(mq_send(mqfd,buf,sizeof(buf),0)){
                perror("send mq error");
                exit(EXIT_FAILURE);
        }
        printf("消息发送成功\n");
        mq_close(mqfd);
        return 0;
}
```



##### 示例2：信号发送行为设置为SIGEV_SIGNAL

> 该选项在满足示例1的条件时，不是创建新线程执行回调函数，而是给该进程发送指定的信号，内核再根据具体信号进行相关处理。
>
> 所以使用SIGEV_SIGNAL时，可以提前注册信号handler，达到异步处理的效果。

下面是指定当监听的消息队列由空到有消息事件触发时，通过发送SIGINT信号给进程，完成示例1相同的效果。(发送函数与示例1的<mq_snd.c>相同)，下面是修改后的<mq_rcv.c>代码：

```c
#include <sys/syscall.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <errno.h>
#include <signal.h>
#define MQ_NAME "/mq"
#define ERR_EXIT(__MSG) perror(__MSG); \
                        exit(EXIT_FAILURE)
//mq_notify()的demo,使用SIGEV_SIGNAL选项，给进程发送信号的方式处理
//信号处理的sa_flags包含SA_SIGINFO选项时的回调函数
//第三个参数用户层用不到，牵扯内核切换上下文用的。
//所有传入的参数都在第二个参数siginfo里面
void sig_handler(int signum,siginfo_t * siginfo,void * ucontext){
        printf("回调函数处理线程ID = %ld\n",syscall(SYS_gettid));
        mqd_t mqfd = *((mqd_t*)siginfo->si_value.sival_ptr);//获取传入的参数，在这里传入的是队列的描述符地址。
        //异步传过来的参数:信号类型
        printf("信号类型 == SIGINT ? : %d\n",siginfo->si_signo);
        struct mq_attr attr;
        if(mq_getattr(mqfd,&attr)){
                ERR_EXIT("get mq attr error");
        }
        char* buf = (char*) malloc(attr.mq_msgsize);
        ssize_t rcv_len;
        if((rcv_len = mq_receive(mqfd,buf,attr.mq_msgsize,NULL)) == -1){
                ERR_EXIT("rcv mq error");
        }
        mq_unlink(MQ_NAME);
        mq_close(mqfd);
        printf("收到的字节数 = %ld\n",rcv_len);
        printf("消息内容: %s\n",buf);
        free(buf);
        exit(EXIT_SUCCESS);
}

int main(){
        //注册SIGINT信号handler
        struct sigaction sa;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = sig_handler;
        if(sigaction(SIGINT,&sa,NULL)){
                ERR_EXIT("sigaction error");
        }
        mqd_t mqfd;
        if((mqfd = mq_open(MQ_NAME,O_CREAT | O_RDWR,0666,NULL)) == (mqd_t)-1){
                ERR_EXIT("open mq error");
        }
        printf("进程ID = %d\n",getpid());
        //设置信号驱动,消息传来发送SIGINT信号
        struct sigevent event;
        event.sigev_notify = SIGEV_SIGNAL;//启用SIGEV_SIGNAL方式处理信号
        event.sigev_signo = SIGINT;//发送的信号类型为SIGINT
        event.sigev_value.sival_ptr = &mqfd;//传参，有整型与指针2种类型，这里传入的是消息队列的描述符地址，用的指针类型。
        if(mq_notify(mqfd,&event)){
                ERR_EXIT("mq notify error");
        }
        pause();//持续阻塞等待信号事件回调。
}
```


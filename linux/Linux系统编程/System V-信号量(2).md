### System V信号量：

​		**System V的信号量与POSIX信号量不同的是，前者可以同时创建一个信号量数组(指定一次可创建多少个信号量)，并且对信号量进行PV操作不再局限于按照步长1进行增减(即一次可以增减大于1)，除了API怪异，System V的信号量组比POSIX标准的信号量要强大。**

###### 		注意：System V的信号量在被信号中断后不会重启函数，即信号sigaction.sa_flags | SA_RESTART 无效。

#### 创建信号量组semget(2)：

​		与System V的其他IPC手段(共享内存shm\*、消息队列msg\*)一样，信号量sem是以一个整型数据(key_t类型)作为一个唯一标识，不同进程可使用相同的key获取同一个信号量组。key可以通过ftok(3)来获取：

```c
#include <sys/types.h>
#include <sys/ipc.h>
/**
	利用文件名与签名生成消息队列的唯一标识key
	pathname: 文件名称，文件必须存在
	proj_id: 签名
	return:
		-1: 生成失败，错误码errno
		非-1：成功，返回唯一标识(标识为有符号32位整数)
*/
key_t ftok(const char *pathname, int proj_id);
typedef int key_t;
```

通过key_t来获取/创建信号量组：

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define IPC_PRIVATE ((__key_t) 0)
#define SEMMSL  32000
/**
	key: 标识
		特殊取值：等于IPC_PRIVATE(=0)时，系统调用将仅保留 semflg 的低 9 位，其余位全部忽略，并在调用成功时创建一个新的信号量集。
		
	nsems: 要创建多少个信号量，表示数组的容量。
		当不是创建新信号量集时，参数 nsems 可以为 0（表示忽略）。
		否则 nsems 必须大于 0，且不超过单个信号量集允许的最大信号量数量（SEMMSL）。
		
	semflg：行为 | 权限，是一个由操作 | 权限组成的一个集合，功能与系统调用open(2)相同。
		IPC_CREAT: 当信号量集不存在时会进行创建。
			如果 | IPC_EXCL,当信号量集已经存在时会报错，没有位或，信号量集存在，则会忽略IPC_CREAT。
		IPC_EXCL: 检测信号量集是否存在。
		除了添加IPC_CREAT，必须给信号量集添加权限，(与open系统调用的权限相同，但是没有可执行权限，所以可以位或读写权限),例如： IPC_CREAT | 0666，标识该信号量集对所有用户都是读写权限，不存在则创建，存在则打开。
		
	return：
		-1: 创建失败。错误码errno
		非负数: 创建成功，返回值为信号量的id。
		错误码如下：
		EACCES: 该键对应的信号量集已存在，但调用进程没有访问该集合的权限，并且在管控其 IPC 命名空间的用户命名空间中不具备 CAP_IPC_OWNER 权限。
		EEXIST: semflg 中同时指定了 IPC_CREAT 和 IPC_EXCL，但该键对应的信号量集已存在。
		EINVAL: nsems 小于 0，或是超出单个信号量集的信号量数量上限（SEMMSL）。
		EINVAL: 该键对应的信号量集已存在，但 nsems 大于该信号量集中的信号量数目。
		ENOENT: 不存在该键对应的信号量集，且 semflg 未指定 IPC_CREAT。
		ENOMEM: 需要创建信号量集，但系统没有足够内存来存放新的数据结构。
		ENOSPC: 需要创建信号量集，但操作会超出系统允许的信号量集最大数量上限（SEMMNI），或是系统全局信号量总数上限（SEMMNS）。
*/
int semget(key_t key, int nsems, int semflg);
```

​		

> ​		semget () 系统调用返回与参数 key 关联的 System V 信号量集标识符。该函数可用于获取已创建信号量集的标识符（当 semflg 为 0，且 key 不为 IPC_PRIVATE 时），也可用来新建信号量集。

> ​		若 key 的值为 IPC_PRIVATE，或者没有现存信号量集与该 key 绑定，且 semflg 中指定了 IPC_CREAT，则会创建一个包含 nsems 个信号量的新信号量集。

> ​		如果 semflg 同时指定 IPC_CREAT 和 IPC_EXCL，并且该 key 对应的信号量集已存在，那么 semget () 调用失败，错误号 errno 置为 EEXIST。（这与 open (2) 中 O_CREAT | O_EXCL 组合的效果类似。）

> ​		创建信号量集时，参数 semflg 的低 9 位定义信号量集的权限（所有者、用户组、其他用户）。这些位的格式与含义和 open (2) 的 mode 参数相同（不过执行权限对信号量无实际意义，写权限代表修改信号量值的权限）。

> ​		新建信号量集时，semget () 会按如下方式初始化信号量集关联的数据结构 semid_ds（参见 semctl (2)）：

> ​			sem_perm.cuid 和 sem_perm.uid 设置为调用进程的有效用户 ID。

> ​			sem_perm.cgid 和 sem_perm.gid 设置为调用进程的有效组 ID。

> ​			sem_perm.mode 的低 9 位设置为 semflg 的低 9 位。

> ​			sem_nsems 设置为 nsems 的值。

> ​			sem_otime 设置为 0。

> ​			sem_ctime 设置为当前时间。

> ​		当不是创建新信号量集时，参数 nsems 可以为 0（表示忽略）。否则 nsems 必须大于 0，且不超过单个信号量集允许的最大信号量数量（SEMMSL）。

> ​		如果信号量集已存在，则会校验访问权限。

###### 注意事项：

> ​		在 Linux 系统以及所有版本的 POSIX 标准中，并不要求必须包含头文件`<sys/types.h>`和`<sys/ipc.h>`。不过，一些旧版实现要求引入这两个头文件，SVID 标准中也记载了需要包含它们。如果应用程序需要兼容这类老旧系统，则可能需要引入这两个头文件。

> ​		IPC_PRIVATE 并非标志位，而是 key_t 类型。若将这个特殊值用作键（key），系统调用会仅取用 semflg 的低 9 位，并在调用成功时创建一个新的信号量集。

##### 信号量初始化

> ​		新创建的信号量集中，各个信号量的值是不确定的。（POSIX.1-2001 与 POSIX.1-2008 在此处表述明确，不过 POSIX.1-2008 提到，该标准的未来版本可能要求实现将信号量初始化为 0。）虽然 Linux 和许多其他实现会把信号量值初始化为 0，但具备可移植性的应用程序不能依赖这一特性：程序应当显式将信号量初始化为目标值。

> ​		可以通过`semctl(2)`的 SETVAL 或 SETALL 操作完成初始化。当多个对等进程无法确定谁最先初始化信号量集时，可以通过`semctl(2)`的 IPC_STAT 操作读取关联数据结构，检查 sem_otime 是否非零，以此避免竞态条件。

##### 信号量限制

> 以下信号量集资源限制会影响 semget () 调用：

> ​		SEMMNI：系统范围内信号量集数量上限。在 3.19 版本之前的 Linux 系统中，该限制默认值为 128；自 Linux 3.19 起，默认值为 32000。在 Linux 上，可通过`/proc/sys/kernel/sem`的第四个字段读取并修改该限制。

> ​		SEMMSL：单个信号量 ID 所能包含的信号量最大数量。在 3.19 版本之前的 Linux 系统中，该限制默认值为 250；自 Linux 3.19 起，默认值为 32000。在 Linux 上，可通过`/proc/sys/kernel/sem`的第一个字段读取并修改该限制。

> ​		SEMMNS：系统范围内信号量总数量上限，该值由系统策略决定（在 Linux 上，可通过`/proc/sys/kernel/sem`的第二个字段读取并修改该限制）。注意，系统全局信号量总数同时还受 SEMMSL 与 SEMMNI 二者乘积的约束。



#### 操作信号量集semctl(2):

###### 对已创建的信号量集进行设置、删除等操作

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
/**
	semid:	信号量集的id
	semnum： 要操作的信号量编号，从0开始。
	cmd：
		对信号量的操作，具体如下：
			一、IPC_STAT： 查询功能。
				1、将与信号量标识符 semid 相关联的内核数据结构中的信息复制到 arg.buf 指向的 semid_ds 结构体中。参数 semnum 会被忽略。
				2、调用进程必须对该信号量集拥有读权限。
				
			二、IPC_SET：修改功能。
            	1、将 arg.buf 指向的 semid_ds 结构体中部分成员的值写入与此信号量集关联的内核数据结构，同时更新其 sem_ctime 成员。
            	2、能修改的结构体成员如下：
            		sem_perm.uid、sem_perm.gid，以及 sem_perm.mode（低 9 位）。
            	3、调用进程的有效用户 ID 必须匹配该信号量集的所有者（sem_perm.uid）或创建者（sem_perm.cuid），或者调用者拥有特权。
            	4、参数 semnum 会被忽略。
			三、IPC_RMID： 立即删除该信号量集。（最常用）
				1、唤醒所有在该信号量集上因 semop (2) 调用而阻塞的进程（这些调用会返回错误，错误号 errno 设为 EIDRM）。
				2、调用进程的有效用户 ID 必须匹配该信号量集的创建者或所有者，或者调用者拥有特权。
				3、参数 semnum 会被忽略。
			四、SETVAL:初始化信号量的值。(最常用)
				1、将集合中第 semnum 个信号量的 semval 值设置为 arg.val，同时更新与该集合关联的 semid_ds 结构体的 sem_ctime 成员。
				2、所有进程中被修改信号量的撤销项都会被清除。
				3、如果信号量值的变更能够允许其他进程中阻塞的 semop (2) 调用继续执行，则唤醒这些进程。
				4、调用进程必须拥有该信号量集合的修改权限。
			五、GETVAL：返回该信号量集中第 semnum 个信号量的 semval 值。调用进程必须对该信号量集拥有读权限。
			六、还有很多其他命令，详情参考semctl(2)。

	return：
		成功：根据不同的cmd选项，返回值不同：（SETVAL与IPC_RMID均返回0）
			1、GETNCNT: 获取 semncnt 的值。
			2、GETPID： 获取 sempid 的值。
			3、GETVAL： 获取 semval 的值。
			4、GETZCNT： 获取 semzcnt 的值。
			5、IPC_INFO： 内核中记录所有信号量集信息的内部数组里，已使用条目的最大索引。（该信息可配合多次 SEM_STAT 或 SEM_STAT_ANY 操作，获取系统上全部信号量集的信息。）
			6、SEM_INFO： 同 IPC_INFO。
			7、SEM_STAT： 获取索引在 semid 中指定的信号量集的标识符。
			8、SEM_STAT_ANY：同 SEM_STAT。
			9、其余所有 cmd 值调用成功时均返回 0。
			
		失败：-1，错误码填充errno，类型如下：
			1、EACCES：参数 cmd 取值为 GETALL、GETPID、GETVAL、GETNCNT、GETZCNT、IPC_STAT、SEM_STAT、SEM_STAT_ANY、SETALL 或 SETVAL，且调用进程对该信号量集合不具备所需权限，同时在管控其 IPC 命名空间的用户命名空间中不拥有 CAP_IPC_OWNER 权限。
			2、EFAULT：arg.buf 或 arg.array 所指向的地址无法访问。
			3、EIDRM：该信号量集合已被移除。
			4、EINVAL：cmd 或 semid 的值无效。或者：执行 SEM_STAT 操作时，semid 中指定的索引指向当前未使用的数组槽位。
			5、EPERM：参数 cmd 取值为 IPC_SET 或 IPC_RMID，但调用进程的有效用户 ID 并非该信号量集合的创建者（sem_perm.cuid）或所有者（sem_perm.uid），并且该进程不具备 CAP_SYS_ADMIN 权限。
			6、ERANGE：参数 cmd 取值为 SETALL 或 SETVAL，且待设置的 semval 值（针对集合中的某个信号量）小于 0，或超出实现规定的上限 SEMVMX。
*/
int semctl(int semid, int semnum, int cmd, ...);
int semctl(int semid, int semnum, int cmd,union semun arg);
```



> ​		semctl () 根据 cmd 指定的控制命令，对由 semid 标识的 System V 信号量集，或是该信号量集中第 semnum 个信号量执行控制操作。（信号量集中的信号量编号从 0 开始。）

> ​		该函数的参数个数取决于 cmd，为 3 个或 4 个。当使用 4 个参数时，第四个参数的类型为 union semun(注意是结构体，不是指针)。调用程序必须按如下方式定义该联合体：

```c
//该联合体在<linux/sem.h>下面有定义,具体系统可能有所不同，以系统的实际定义为标准。
//如果<sys/sem.h>中定义了宏：_SEM_SEMUN_UNDEFINED，表示需要用户自行定义union semun
union semun {
    int              val;    /* SETVAL 使用的值 */
    struct semid_ds *buf;    /* IPC_STAT、IPC_SET 使用的缓冲区 */
    unsigned short  *array;  /* GETALL、SETALL 使用的数组 */
    struct seminfo  *__buf;  /* IPC_INFO 使用的缓冲区 */
    void *__pad;            /* (Linux 特有) */
};
//在<sys/sem.h>中包含semid_ds结构体：
struct semid_ds {
    struct ipc_perm sem_perm;  /* 拥有者以及权限 */
    time_t          sem_otime; /* 上次执行semop操作的时间 */
    time_t          sem_ctime; /* 上次改变的时间 */
    unsigned long   sem_nsems; /* 信号量集的信号量个数，也就是信号量数组中元素个数 */
};

struct ipc_perm {
    key_t          __key; /* Key supplied to semget(2) */
    uid_t          uid;   /* Effective UID of owner，可使用cmd的IPC_SET修改 */
    gid_t          gid;   /* Effective GID of owner，可使用cmd的IPC_SET修改 */
    uid_t          cuid;  /* Effective UID of creator */
    gid_t          cgid;  /* Effective GID of creator */
    unsigned short mode;  /* 权限，可使用cmd的IPC_SET修改 */
    unsigned short __seq; /* Sequence number */
};
```

> ​		***在部分早期 glibc 版本中，semun 联合体在\<sys/sem.h\>头文件内定义，但 POSIX.1 标准要求调用方自行定义该联合体。在未定义此联合体的 glibc 版本中，\<sys/sem.h\>头文件会定义宏 : _SEM_SEMUN_UNDEFINED。***

#### 信号量的PV操作semop(2)：

##### System V 信号量集中的每个信号量都包含以下关联值：(System V的信号量结构体不对外暴露)

```c
unsigned short semval; /* 信号量的值 */
unsigned short semzcnt; /* 等待信号量值变为 0 的线程数 */
unsigned short semncnt; /* 等待信号量值增加的线程数 */
pid_t sempid; /* 最后操作该信号量的线程 ID */
```

semval：信号量的当前值，PV操作围绕的中心。

semzcnt：记录等待semval ==0 的线程数，当semop()的sembuf.sem_op==0，并且信号量当前值semval !=0，该字段+1。

semncnt:  等待信号量值增加的线程数。当执行P操作但semval不够减时，会阻塞该线程，该字段+1.

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
/**
	根据第二个参数sops中的sem_op选项执行对编号为sem_num的信号量执行相关操作。
	semid：信号量集的id
	sops：结构体数组，每个结构体代表对指定的单个信号量执行的一项操作.对该数组对应的所有PV操作具有原子性，即这个数组内所有操作要么都成功，要么都失败。
	nsops：sops数组的元素个数，也就是操作次数。
	return：
		成功：0
		失败：-1，错误码errno，选项如下：
			1、E2BIG： 参数 nsops 大于 SEMOPM，即每次系统调用允许执行的最大操作数。
			2、EACCES： 调用进程没有执行指定信号量操作所需的权限，并且在管控其 IPC 命名空间的用户命名空间中不具备 CAP_IPC_OWNER 能力。
			3、EAGAIN： 操作无法立即执行，并且要么在 sem_flg 中指定了 IPC_NOWAIT，要么 timeout 中设置的时限已到期。
			4、EFAULT： sops 或 timeout 参数中指定的地址不可访问。
			5、EFBIG： 对于某一项操作，sem_num 的值小于 0，或者大于等于该信号量集合中的信号量数量。
			6、EIDRM： 该信号量集合已被删除。
			7、EINTR： 线程在阻塞于该系统调用期间捕获到信号；参见 signal (7)。
			8、EINVAL： 信号量集合不存在，或 semid 小于 0，或 nsops 为非正值。
			9、ENOMEM： 某一项操作的 sem_flg 指定了 SEM_UNDO，而系统没有足够内存来分配撤销结构。
			10、ERANGE： 对于某一项操作，sem_op+semval 大于 SEMVMX，即由实现定义的 semval 最大值。
*/
int semop(int semid, struct sembuf *sops, size_t nsops);

//semtimedop () 函数首次出现在 Linux 2.5.52 版本，随后被移植到内核 2.4.22 中。Glibc 对 semtimedop () 的支持最早在 2.3.3 版本中引入。
/**
		semtimedop () 的行为与 semop () 完全相同，区别在于：当调用线程需要休眠时，休眠时长受限于 timeout 参数传入地址所指向的 timespec 结构体指定的流逝时间。（该休眠时间间隔会向上取整至系统时钟精度，并且内核调度延迟会导致实际休眠时间可能略微超出设定值。）如果到达指定时间限制，semtimedop () 调用失败，错误号 errno 设为 EAGAIN（并且不会执行 sops 中的任何操作）。
		若 timeout 参数为 NULL，则 semtimedop () 的行为与 semop () 完全一致。
		请注意：如果 semtimedop () 被信号中断，导致调用失败并返回 EINTR 错误，timeout 中的内容将保持不变。
*/
int semtimedop(int semid, struct sembuf *sops, size_t nsops,const struct timespec *timeout);

//glibc 的特性测试宏要求（参见 feature_test_macros (7)）：
semtimedop(): _GNU_SOURCE
/**
	sem_num:信号量在信号量集的索引，从0开始.
	sem_op: 对编号为sem_num信号量的PV操作的具体值,取值有以下三种：
		一、>0 : semval += sem_op,也就是执行V操作。
			此外，若sem_flg指定了 SEM_UNDO，系统会从该信号量的调整值 semadj 中减去 sem_op。该操作总是可以直接执行，不会让线程阻塞等待。调用进程必须拥有该信号量集的修改权限。
			
		二、=0 : 等待信号量值归零。
			1、若 semval 为 0，操作可以立即执行。
			以下是semval不为0的操作：
			
			2、sem_flg 中指定了 IPC_NOWAIT，semop () 会失败，错误号设为 EAGAIN（并且 sops 中的所有操作都不会执行）。
			3、sem_flg 中没有指定了 IPC_NOWAIT，semzcnt（等待该信号量值变为 0 的线程计数）加一，线程休眠，直到发生以下任意情况：
				a、 semval 变为 0，此时 semzcnt 的值减一。
				b、 信号量集合被删除：semop () 失败，错误号设为 EIDRM。
				c、 被信号中断：semzcnt 的值减一，semop () 失败，错误号设为 EINTR。
				
		三、<0 : 执行P操作，semval -= |sem_op|.根据semval与|sem_op|的大小关系不同，出现不同的状况：
			1、semval >= |sem_op| : 够减，操作成功，可以立即执行 semval -= |sem_op|。
				如果本次操作sem_flg 指定了 SEM_UNDO,将|sem_op|添加到信号量调整值（semadj）以备进程终止时回滚信号量。
			2、semval < |sem_op| : 不够减，此时sem_flg的取值决定其行为:
				a、 sem_flg 中指定了 IPC_NOWAIT，semop()操作失败，errno = EAGAIN(且不会执行 sops 数组中的任何操作)。
				b、sem_flg没有指定IPC_NOWAIT，semncnt（等待该信号量值增大的线程计数器）加 1，线程进入休眠，直到发生以下任一情况：
					①、semval 变为大于或等于 sem_op 的绝对值，够减，执行1操作。
					②、该信号量集从系统中被移除：semop () 调用失败，errno 被设为 EIDRM。
					③、被信号中断：semzcnt 的值减一，semop () 失败，错误号设为 EINTR。
					
	sem_flg: 对信号量操作时的标志位。sem_flg 支持的标志为 IPC_NOWAIT 和 SEM_UNDO。该标志位可以进行或运算。
		IPC_NOWAIT：线程不等待，不阻塞，直接返回，如果出现操作不成功，会返回errno，详情参看字段sem_op的说明。
		SEM_UNDO: 进程终止时，撤销该进程对信号量的所有操作。每个进程都会维护一个对信号量调整的semadj表,该表记录了对每项信号量进行PV操作量总和的相反值，用于在进程非正常退出，该进程还有信号量没被释放时，内核通过该记录恢复信号量。
		
*/
struct sembuf {
        unsigned short  sem_num;        /* 信号量在信号量集的索引，从0开始 */
        short           sem_op;         /* 对编号为sem_num信号量的PV操作的具体值。 */
        short           sem_flg;        /* 操作标志位 */
};
```

###### 注意：SEM_UNDO是针对进程退出，semadj[]记录的也是进程内所有线程的信号量补偿值



##### demo:使用System V信号量实现互斥锁的功能，要求多个线程执行打印任务共1000次

```c
#include <sys/syscall.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PRINT_COUNT 1000
#define THREAD_MAX_COUNT 5
//使用System V的信号量实现互斥锁功能
//本人使用的Linux系统需要用户自身声明union semun：
union semun {
    int              val;    /* SETVAL 使用的值 */
    struct semid_ds *buf;    /* IPC_STAT、IPC_SET 使用的缓冲区 */
    unsigned short  *array;  /* GETALL、SETALL 使用的数组 */
    struct seminfo  *__buf;  /* IPC_INFO 使用的缓冲区 */
    void *__pad;            /* (Linux 特有) */
};

//定义临界资源
typedef struct {
        int sem_id; //System V的信号量集ID
        int cur_cnt; //当前已经打印的次数，临界资源，需要互斥量维护
}shared_src_t;

void* th_callback(void* arg){
        shared_src_t* sst = (shared_src_t*) arg;
        pid_t tid = syscall(SYS_gettid);
        const int sem_id = sst->sem_id;
        //设置操作信号量的结构体
        struct sembuf sb;
        sb.sem_num = 0; //要操作的信号量数组编号
        sb.sem_op = -1;//执行的PV操作，-1代表P
        sb.sem_flg = 0 | SEM_UNDO; //设定进程不正常退出时由内核负责释放进程未释放的信号量
        while(1){
                //获取互斥锁
                semop(sem_id,&sb,1);//执行P操作
                sb.sem_op = 1;//提前设定 sem_op为正数，代表接下来的操作是V。
                //查看打印次数是否已经到要求次数
                if(sst->cur_cnt >= PRINT_COUNT){
                        //次数已到，退出线程，一定注意释放锁
                        semop(sem_id,&sb,1);
                        break;
                }
                //打印
                ++sst->cur_cnt;
                fprintf(stdout,"线程[%d] 已打印第[%d]份文件.\n",tid,sst->cur_cnt);
                semop(sem_id,&sb,1); //执行V操作
        }
        fprintf(stdout,"子线程[%d]退出.\n",tid);
        pthread_exit(NULL);
}

int main(){
        key_t kt;
        int sem_id;
        int i;
        pthread_t threads[THREAD_MAX_COUNT];
        shared_src_t* sst =NULL;
        union semun sm;
        if((kt = ftok("./",1)) == -1){
                perror("ftok error");
                exit(-1);
        }
        //创建、获取信号量ID,这里只创建了一个信号量
        if((sem_id = semget(kt,1,IPC_CREAT | 0666)) == -1){
                perror("semget error");
                exit(-1);
        }
        sst = (shared_src_t*)malloc(sizeof(shared_src_t));
        if(!sst){
                perror("malloc error");
                exit(-1);
        }
        sst->sem_id = sem_id;
        sst->cur_cnt = 0;
        //设置信号量的初值为1，表示互斥锁
        sm.val = 1;
        if(semctl(sem_id,0,SETVAL,sm)){//注意semctl使用第四个参数时，传入的是结构体值而不是指针
                perror("semctl SETVAL error");
                exit(-1);
        }
        //创建线程执行任务
        for(i=0;i<THREAD_MAX_COUNT;++i)
                pthread_create(&threads[i],NULL,th_callback,sst);

        //阻塞等待线程退出
        for(i=0;i<THREAD_MAX_COUNT;++i)
                pthread_join(threads[i],NULL);
        fprintf(stdout,"任务结束!要求打印次数:[%d],实际打印次数:[%d].\n",PRINT_COUNT,sst->cur_cnt);
        //回收资源
        free(sst);
        //删除信号量
        if(semctl(sem_id,0,IPC_RMID,NULL)){
                perror("semctl IPC_RMID error");
                exit(-1);
        }
        return 0;
}
```

当将信号量的初值设为2，每次PV操作的绝对值同样设置为2时，亲自试验后仍然可以正常运行：

```c
#include <sys/syscall.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PRINT_COUNT 1000
#define THREAD_MAX_COUNT 5
//使用System V的信号量实现互斥锁功能
//这里测试semop执行PV进行加减>1是否正常运行

union semun {
    int              val;    /* SETVAL 使用的值 */
    struct semid_ds *buf;    /* IPC_STAT、IPC_SET 使用的缓冲区 */
    unsigned short  *array;  /* GETALL、SETALL 使用的数组 */
    struct seminfo  *__buf;  /* IPC_INFO 使用的缓冲区 */
    void *__pad;            /* (Linux 特有) */
};

//定义临界资源
typedef struct {
        int sem_id;
        int cur_cnt;
}shared_src_t;

void* th_callback(void* arg){
        shared_src_t* sst = (shared_src_t*) arg;
        pid_t tid = syscall(SYS_gettid);
        const int sem_id = sst->sem_id;
        //设置操作信号量的结构体
        struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_op = -2;
        sb.sem_flg = 0 | SEM_UNDO;
        while(1){
                //获取互斥锁
                semop(sem_id,&sb,1);
                sb.sem_op = 2;
                //查看打印次数是否已经到要求次数
                if(sst->cur_cnt >= PRINT_COUNT){
                        //次数已到，退出线程
                        semop(sem_id,&sb,1);
                        break;
                }
                //打印
                ++sst->cur_cnt;
                fprintf(stdout,"线程[%d] 已打印第[%d]份文件.\n",tid,sst->cur_cnt);
                semop(sem_id,&sb,1);
        }
        fprintf(stdout,"子线程[%d]退出.\n",tid);
        pthread_exit(NULL);
}

int main(){
        key_t kt;
        int sem_id;
        int i;
        pthread_t threads[THREAD_MAX_COUNT];
        shared_src_t* sst =NULL;
        union semun sm;
        if((kt = ftok("./",1)) == -1){
                perror("ftok error");
                exit(-1);
        }
        //创建、获取信号量ID,这里创建了一个信号量
        if((sem_id = semget(kt,1,IPC_CREAT | 0666)) == -1){
                perror("semget error");
                exit(-1);
        }
        sst = (shared_src_t*)malloc(sizeof(shared_src_t));
        if(!sst){
                perror("malloc error");
                exit(-1);
        }
        sst->sem_id = sem_id;
        sst->cur_cnt = 0;
        //设置信号量的初值为2，每次PV都是加减2
        sm.val = 2;
        if(semctl(sem_id,0,SETVAL,sm)){
                perror("semctl SETVAL error");
                exit(-1);
        }
        //创建线程执行任务
        for(i=0;i<THREAD_MAX_COUNT;++i)
                pthread_create(&threads[i],NULL,th_callback,sst);

        //阻塞等待线程退出
        for(i=0;i<THREAD_MAX_COUNT;++i)
                pthread_join(threads[i],NULL);
        fprintf(stdout,"任务结束!要求打印次数:[%d],实际打印次数:[%d].\n",PRINT_COUNT,sst->cur_cnt);
        //回收资源
        free(sst);
        //删除信号量
        if(semctl(sem_id,0,IPC_RMID,NULL)){
                perror("semctl IPC_RMID error");
                exit(-1);
        }
        return 0;
}
```

当信号量初值为2，semop的sembuf.sem_op每次减半(即绝对值为1),使用2个sembuf的数组进行PV操作，对sembuf数组的操作同样具有原子性：

```c
#include <sys/syscall.h>
#include <sys/sem.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PRINT_COUNT 1000
#define THREAD_MAX_COUNT 5
//使用System V的信号量实现互斥锁功能
//该程序测试semop()对sembuf数组的操作是否为原子性
//修改的部分：信号量初值=2，进行PV操作时，由原来的一个sembuf改成2个sembuf，每次都执行1次操作
//查看打印次数是否符合条件
union semun {
    int              val;    /* SETVAL 使用的值 */
    struct semid_ds *buf;    /* IPC_STAT、IPC_SET 使用的缓冲区 */
    unsigned short  *array;  /* GETALL、SETALL 使用的数组 */
    struct seminfo  *__buf;  /* IPC_INFO 使用的缓冲区 */
    void *__pad;            /* (Linux 特有) */
};

//定义临界资源
typedef struct {
        int sem_id;
        int cur_cnt;
}shared_src_t;

void* th_callback(void* arg){
        shared_src_t* sst = (shared_src_t*) arg;
        pid_t tid = syscall(SYS_gettid);
        const int sem_id = sst->sem_id;
        //设置操作信号量的结构体数组，一次P操作执行2遍，每次加减的信号量减半
        struct sembuf sb[2];
        int i;
        for(i=0;i<2;++i){
                sb[i].sem_num = 0;
                sb[i].sem_op = -1;
                sb[i].sem_flg = 0 | SEM_UNDO;
        }
        while(1){
                //获取互斥锁,本实验使用了数组2个元素，所以第三个参数为2
                semop(sem_id,&sb[0],2);
                for(i=0;i<2;++i) // 预设2次+1操作，合成V操作
                        sb[i].sem_op = 1;
                //查看打印次数是否已经到要求次数
                if(sst->cur_cnt >= PRINT_COUNT){
                        //次数已到，退出线程
                        semop(sem_id,&sb[0],2);
                        break;
                }
                //打印
                ++sst->cur_cnt;
                fprintf(stdout,"线程[%d] 已打印第[%d]份文件.\n",tid,sst->cur_cnt);
                semop(sem_id,&sb[0],2);
        }
        fprintf(stdout,"子线程[%d]退出.\n",tid);
        pthread_exit(NULL);
}

int main(){
        key_t kt;
        int sem_id;
        int i;
        pthread_t threads[THREAD_MAX_COUNT];
        shared_src_t* sst =NULL;
        union semun sm;
        if((kt = ftok("./",1)) == -1){
                perror("ftok error");
                exit(-1);
        }
        //创建、获取信号量ID,这里创建了一个信号量
        if((sem_id = semget(kt,1,IPC_CREAT | 0666)) == -1){
                perror("semget error");
                exit(-1);
        }
        sst = (shared_src_t*)malloc(sizeof(shared_src_t));
        if(!sst){
                perror("malloc error");
                exit(-1);
        }
        sst->sem_id = sem_id;
        sst->cur_cnt = 0;
        //设置信号量的初值为2，每次PV都是加减2,只是每次PV都分摊到了2个sembuf上
        sm.val = 2;
        if(semctl(sem_id,0,SETVAL,sm)){
                perror("semctl SETVAL error");
                exit(-1);
        }
        //创建线程执行任务
        for(i=0;i<THREAD_MAX_COUNT;++i)
                pthread_create(&threads[i],NULL,th_callback,sst);

        //阻塞等待线程退出
        for(i=0;i<THREAD_MAX_COUNT;++i)
                pthread_join(threads[i],NULL);
        fprintf(stdout,"任务结束!要求打印次数:[%d],实际打印次数:[%d].\n",PRINT_COUNT,sst->cur_cnt);
        //回收资源
        free(sst);
        //删除信号量
        if(semctl(sem_id,0,IPC_RMID,NULL)){
                perror("semctl IPC_RMID error");
                exit(-1);
        }
        return 0;
}
```


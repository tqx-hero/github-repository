#### 共享内存：

##### 多个进程共享相同的物理页。

##### 管道与消息队列除了在物理页中保有内核维护的内存段之外，每个连接管道与消息队列的进程还会在进程的逻辑地址内部保有一个缓冲区，用来存放接收、发送到内核缓冲区(物理页)的数据。

##### 发送&接收数据时，内核会通过： 进程1内缓冲区 -> 内核缓冲区 -> 进程2缓冲区进行2次拷贝、3次状态切换。

###### 共享内存与管道、消息队列不同的是，内核通过虚页表将同一个物理页映射到不同进程，不会创建缓冲区。

###### 进程通信时直接往该物理页进行读取，没有系统调用，不会进行拷贝。

###### 所以共享内存方式是进程通信效率最高的。

###### 但是正由于不同进程都可以对同一个物理页进行访问，必须使用信号量对它进行同步。

- ###### 创建、开启共享内存shmget(2):

```c
#include <sys/ipc.h>
#include <sys/shm.h>
/**
	创建、打开共享内存。
	key: 生成共享内存的key，可通过ftok()获取
	size: 指定共享内存的容量。
	shmflg: 
		IPC_CREAT: 当共享内存不存在时会进行创建。
			如果 | IPC_EXCL,当共享内存已经存在时会报错，没有位或，共享内存存在，则会忽略IPC_CREAT。
		IPC_EXCL: 检测共享内存是否存在。
		
		除了添加IPC_CREAT，必须给共享内存添加权限，(与open系统调用的权限相同，但是没有可执行权限，所以可以位或读写权限),例如： IPC_CREAT | 0666，标识该共享内存对所有用户都是读写权限，不存在则创建，存在则打开。
		
	return:
		-1: 创建失败。
		非负数: 创建成功，返回值为共享内存的标识。
*/
int shmget(key_t key, size_t size, int shmflg);
```

###### demo:创建、开启共享内存

```c
  1 #include <sys/ipc.h>
  2 #include <sys/shm.h>
  3 #include <unistd.h>
  4 #include <stdio.h>
  5 #include <stdlib.h>
  6 //shmget()
  7 int main(){
  8         key_t kt;
  9         int shm_id;
 10         //创建key
 11         if((kt = ftok("./",1)) == -1){
 12                 perror("ftok error");
 13                 exit(-1);
 14         }
 15         //通过key创建、打开共享内存
 16         //if((shm_id =  shmget(kt,sysconf(_SC_PAGE_SIZE),IPC_CREAT | 0666)) == -1){ //设置的共享内存大小为物理页大小4K
 17         if((shm_id =  shmget(kt,1024,IPC_CREAT | 0666)) == -1){	//设置共享内存大小为1024
 18                 perror("shmget error");
 19                 exit(-1);
 20         }
 21         printf("已创建共享内存，id = %d\n",shm_id);
 22         return 0;
 23 }
```

- ###### 挂载共享内存到进程逻辑地址shmat(2)：

  ```c
  #include <sys/types.h>
  #include <sys/shm.h>
  /**
  	将共享内存与进程虚拟地址进行绑定。当进程退出时，会自动解绑该共享内存。
  	shmid: 共享内存id。可通过shmget(2)返回值获得
  	shmaddr: 进程虚拟地址。填NULL(推荐)表示内核自己找一块合适的区域放入。
  		`shmaddr` 指定，遵循以下规则：
  		- 如果 **shmaddr 为 NULL**：操作系统会自行挑选一块合适、尚未使用、按页对齐的地址来挂载该共享内存段。
  		- 如果 **shmaddr 非 NULL，并且 shmflg 中设置了 SHM_RND**：挂载地址等于把 shmaddr **向下取整**到距离它最近的 `SHMLBA` 的整数倍地址。
  		- 其他情况：**shmaddr 本身必须是页对齐的地址**，共享内存就挂载到此地址上。
  	shmflg: 设置共享内存的权限位掩码。
  		0: 默认选项，共享内存有读写权限。
  		SHM_RND: 强制使用shmaddr作为进程的虚拟地址来绑定物理页。
  		SHM_EXEC（Linux 特有；自 Linux 2.6.9 版本起）：允许执行该共享内存段里面的内容。调用进程必须对该共享内存段拥有执行权限。
  		SHM_RDONLY: 
  			以只读模式挂载共享内存段。进程必须拥有该段的读权限。
  			如果不设置该标志，则以读写模式挂载；此时进程必须拥有读写权限。
  			System V 共享内存不存在只写模式
  		SHM_REMAP（Linux 特有：
  			该标志表示：挂载此共享内存段时，直接替换从 shmaddr 开始、长度等于共享内存段大小这一段地址上原有的已有映射
  			（正常情况下，如果该地址范围已经存在内存映射，shmat 调用会返回 EINVAL 错误。）
  			使用此标志时，shmaddr 不允许传 NULL。
  	return:
  		成功： 返回绑定的进程逻辑地址。
  		失败： 返回 (void *) -1
  */
  void *shmat(int shmid, const void *shmaddr, int shmflg);
  ```

  ###### demo:

  ```c
    1 #include <sys/ipc.h>
    2 #include <sys/shm.h>
    3 #include <unistd.h>
    4 #include <stdio.h>
    5 #include <stdlib.h>
    6 //shmat()
    7 int main(){
    8         key_t kt;
    9         int shm_id;
   10         char * shmp;
   11         //创建key
   12         if((kt = ftok("./",1)) == -1){
   13                 perror("ftok error");
   14                 exit(-1);
   15         }
   16         //通过key创建、打开共享内存
   17         //if((shm_id =  shmget(kt,sysconf(_SC_PAGE_SIZE),IPC_CREAT | 0666)) == -1){
   18         if((shm_id =  shmget(kt,1024,IPC_CREAT | 0666)) == -1){
   19                 perror("shmget error");
   20                 exit(-1);
   21         }
   22         printf("已创建共享内存，id = %d\n",shm_id);
   23         //shmat()绑定当前进程的逻辑地址
   24         shmp = shmat(shm_id,NULL,0);
   25         if(shmp == (void*)-1){
   26                 perror("shmat error");
   27                 exit(-1);
   28         }
   29         printf("绑定当前进程成功，逻辑地址 = %p\n",shmp);
   30         return 0;
   31 }
  ```

  ###### gdb调试绑定之后的共享内存：

  ```bash
  tqx@linux-ubuntu$ ipcs -m
  
  ------ Shared Memory Segments --------
  key        shmid      owner      perms      bytes      nattch     status
  0x01053779 32780      tqx        666        1024       1 #这里由之前的0变成1，表示有1个进程正在绑定这个共享内存段。
  ```

  

- ###### 分离共享内存与进程逻辑地址的关系shmdt(2)：

  ```c
  #include <sys/types.h>
  #include <sys/shm.h>
  /**
  	解绑共享内存与进程虚拟地址的关系。解绑后，共享内存只是不能通过shmaddr使用了，但是共享内存还是存在。
  	如果需要删除共享内存，使用shmctl(2)中的IPC_RMID选项(shell: ipcrm -m id)
  	shmaddr: 要解绑的进程虚拟地址。
  	return:
  		0:成功。
  		-1：失败，错误码在errno
  */
  int shmdt(const void *shmaddr);
  ```

  ###### demo:

  ```c
    2 #include <sys/shm.h>
    3 #include <unistd.h>
    4 #include <stdio.h>
    5 #include <stdlib.h>
    6 //shmdt()解绑
    7 int main(){
    8         key_t kt;
    9         int shm_id;
   10         char * shmp;
   11         //创建key
   12         if((kt = ftok("./",1)) == -1){
   13                 perror("ftok error");
   14                 exit(-1);
   15         }
   16         //通过key创建、打开共享内存
   17         //if((shm_id =  shmget(kt,sysconf(_SC_PAGE_SIZE),IPC_CREAT | 0666)) == -1){
   18         if((shm_id =  shmget(kt,1024,IPC_CREAT | 0666)) == -1){
   19                 perror("shmget error");
   20                 exit(-1);
   21         }
   22         printf("已创建共享内存，id = %d\n",shm_id);
   23         //shmat()绑定当前进程的逻辑地址
   24         shmp = shmat(shm_id,NULL,0);
   25         if(shmp == (void*)-1){
   26                 perror("shmat error");
   27                 exit(-1);
   28         }
   29         printf("绑定当前进程成功，逻辑地址 = %p\n",shmp);
   30         if(shmdt(shmp) == -1)	//解绑函数
   31                 perror("shmdt error");
   32         return 0;
   33 }
  ```

  ###### gdb调试调用shmdt(2)前后的共享内存列表:

  ```bash
  # 调用shmdt(2)之前：
  tqx@linux-ubuntu$ ipcs -m
  
  ------ Shared Memory Segments --------
  key        shmid      owner      perms      bytes      nattch     status
  0x01053779 32780      tqx        666        1024       1	#绑定的进程有1个
  # 调用shmdt(2)之后：
  tqx@linux-ubuntu$ ipcs -m
  
  ------ Shared Memory Segments --------
  key        shmid      owner      perms      bytes      nattch     status
  0x01053779 32780      tqx        666        1024       0 #没有绑定的进程
  ```

  

- ###### 控制共享内存的属性shmctl(2):

  ```c
  #include <sys/ipc.h>
  #include <sys/shm.h>
  /**
  	控制共享内存的属性，包括删改查。
  	shmid:	要操作的共享内存id
  	cmd：
  		IPC_STAT: 查询共享内存属性，将其拷贝到第三个参数struct shmid_ds指针中。
  		IPC_SET： 将第三个参数指针中的部分属性更新到共享内存，同时更新共享内存的shm_ctime属性值。
  			可以修改的字段仅有：
  			 	shm_perm.uid（所有者用户 ID）;
  			 	shm_perm.gid（所有者组 ID）;
  			 	shm_perm.mode（仅低 9 位有效，也就是权限位）。
  			调用进程的有效用户 ID (effective UID)必须等于该共享内存段的所有者 ID（shm_perm.uid）或者创建者 ID（shm_perm.cuid）；
  			或者调用进程拥有特权（root 权限），才可以执行本操作。
  		IPC_RMID： 将该共享内存段标记为待销毁。
  		该段并不会立刻销毁；要等到最后一个进程解除挂载之后（也就是对应的 shmid_ds 结构体里的 shm_nattch 值变为 0 的时候），才会真正被销毁。
  		cmd为该字段时，第三个参数将会被忽略。
  		IPC_INFO(GNU扩展Linux特有):
  			将整个系统层面的共享内存限制与参数信息填写到 buf 指向的结构体中返回。该结构体类型为 shminfo（因此调用时需要做强制类型转换）。
  			shmmni、shmmax、shmall 这几项配置可以通过同名的 /proc 文件进行修改；详细参见 proc(5) 手册页。
  		SHM_INFO(GNU扩展Linux特有):
  			返回一个 shm_info 结构体，结构体各个字段保存系统中共享内存所消耗资源的统计信息。
  			定义同样需要预先定义 _GNU_SOURCE 宏，才会在 <sys/shm.h>中暴露 shm_info
  		SHM_LOCK:
  			锁定共享内存所在的物理页，使得当内存紧张需要进行内存交换时不交换该物理页。只能超级用户才有权限。
  		SHM_UNLOCK:
  			解锁被SHM_LOCK设置的这个共享内存所在物理页。
  		return:
  			0: 成功。
  			-1: 失败
  */
  int shmctl(int shmid, int cmd, struct shmid_ds *buf);
   //结构体shmid_ds： #include <sys/shm.h>
   struct shmid_ds {
     struct ipc_perm shm_perm;    /* Ownership and permissions */
     size_t          shm_segsz;   /* Size of segment (bytes) */
     time_t          shm_atime;   /* Last attach time */
     time_t          shm_dtime;   /* Last detach time */
     time_t          shm_ctime;   /* Last change time */
     pid_t           shm_cpid;    /* PID of creator */
     pid_t           shm_lpid;    /* PID of last shmat(2)/shmdt(2) */
     shmatt_t        shm_nattch;  /* No. of current attaches */
     ...
  };
  
  struct ipc_perm {
     key_t          __key;    /* Key supplied to shmget(2) */
     uid_t          uid;      /* Effective UID of owner */
     gid_t          gid;      /* Effective GID of owner */
     uid_t          cuid;     /* Effective UID of creator */
     gid_t          cgid;     /* Effective GID of creator */
     unsigned short mode;     /* Permissions + SHM_DEST and
                                 SHM_LOCKED flags */
     unsigned short __seq;    /* Sequence number */
  };
  
  //IPC_INFO (Linux-specific)返回的结构体：shminfo(需要强转)
  #define  _GNU_SOURCE
  struct shminfo {
      unsigned long shmmax;   /* 单个共享内存段最大字节数 */
      unsigned long shmmin;   /* 共享内存段最小字节数；恒等于1 */
      unsigned long shmmni;   /* 系统最多允许的共享内存段总数量 */
      unsigned long shmseg;   /* 一个进程最多可挂载的共享内存段数目；
                                 内核内部并未使用该限制 */
      unsigned long shmall;   /* 整个系统范围内，共享内存最多占用的总页数 */
  };
  
  //SHM_INFO (Linux-specific)返回的结构体：shm_info
  #define  _GNU_SOURCE
  struct shm_info {
      int           used_ids;        /* 当前现存共享内存段的个数 */
      unsigned long shm_tot;         /* 共享内存占用总页面数量 */
      unsigned long shm_rss;         /* 驻留在物理内存的共享内存页面数 */
      unsigned long shm_swp;         /* 被换出到swap交换分区的共享内存页面数 */
      unsigned long swap_attempts;  /* Linux2.4之后不再使用 */
      unsigned long swap_successes;  /* Linux2.4之后不再使用 */
  };
  ```

  ###### demo:进程间的通信：

  ###### shm_t.h:共用结构体

  ```c
  #ifndef __MYSHM_T_H
  #define __MYSHM_T_H
  
  #include <sys/ipc.h>
  #include <sys/shm.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  //写入共享内存数据
  typedef struct {
          pid_t pid;
          char msg[128];
  }shm_msg_t;
  
  #endif
  ```

  

  ###### shm_w.c:负责写入共享内存数据：

  ```c
  #include "shm_t.h"
  int main(){
          key_t kt;
          int shm_id;
          char * shmp;
          //创建key
          if((kt = ftok("./",1)) == -1){
                  perror("ftok error");
                  exit(-1);
          }
          //通过key创建、打开共享内存
          if((shm_id =  shmget(kt,1024,IPC_CREAT | 0666)) == -1){
                  perror("shmget error");
                  exit(-1);
          }
          printf("已创建共享内存，id = %d\n",shm_id);
          //shmat()绑定当前进程的逻辑地址
          shmp = shmat(shm_id,NULL,0);
          if(shmp == (void*)-1){
                  perror("shmat error");
                  exit(-1);
          }
          printf("绑定当前进程成功，逻辑地址 = %p\n",shmp);
          //写入数据:当前进程ID、msg
          shm_msg_t *shg = (shm_msg_t*) shmp;
          shg->pid = getpid();	
          strcpy(shg->msg,"大家好才是真的好!");
          if(shmdt(shmp) == -1)
                  perror("shmdt error");
          return 0;
  
  ```

  ###### shm_w.c:负责读出共享内存数据，并设置删除标记，使共享内存在合适时机由内核删除。

  ```c
  #include "shm_t.h"
  int main(){
          key_t kt;
          int shm_id;
          char * shmp;
          //创建key
          if((kt = ftok("./",1)) == -1){
                  perror("ftok error");
                  exit(-1);
          }
          //通过key创建、打开共享内存
          if((shm_id =  shmget(kt,1024,IPC_CREAT | 0666)) == -1){
                  perror("shmget error");
                  exit(-1);
          }
          //shmat()绑定当前进程的逻辑地址
          shmp = shmat(shm_id,NULL,0);
          if(shmp == (void*)-1){
                  perror("shmat error");
                  exit(-1);
          }
          printf("绑定当前进程成功，逻辑地址 = %p\n",shmp);
          //读取数据
          shm_msg_t *shg = (shm_msg_t*) shmp;
          printf("共享内存中的结构体信息： pid = %d , msg = %s\n",shg->pid,shg->msg);
          if(shmdt(shmp) == -1)
                  perror("shmdt error");
          //给共享内存打上删除标记，当无进程使用该内存段，删除它
          if(shmctl(shm_id,IPC_RMID,NULL) == -1)
                  perror("shmctl rm error");
          return 0;
  }
  ```

  ###### 执行结果：

  ```bash
  tqx@linux-ubuntu$ ./shm_r
  绑定当前进程成功，逻辑地址 = 0x7f24128ae000
  共享内存中的结构体信息： pid = 139707 , msg = 大家好才是真的好!
  
  #再次查看共享内存列表,已删除
  tqx@linux-ubuntu$ ipcs -m
  
  ------ Shared Memory Segments --------
  key        shmid      owner      perms      bytes      nattch     status
  
  ```

  ###### demo：修改共享内存的权限：

  ```c
  #include <sys/ipc.h>
  #include <sys/shm.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  //使用shmctl()控制共享内存
  int main(){
          struct shmid_ds shd;
          shd.shm_perm.mode = 0644;	//将共享内存的权限设置为0644
          shd.shm_segsz = 64;	//尝试将它的大小改变，但是无法改变。
          if(shmctl(32780,IPC_SET,&shd) ==-1)
                  perror("shmctl error");
          return 0;
  }
  ```

  
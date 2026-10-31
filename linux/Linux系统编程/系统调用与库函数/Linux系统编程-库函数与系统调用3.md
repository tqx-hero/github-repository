### Linux系统编程-库函数与系统调用3：

- #### 重定向对标准输入、输出的影响：

  以输出重定向 `>` 为例,启动程序：

  ```shell
  $ ./menu > file
  ```

  上述程序会将程序中使用标准输出原本打印到终端的文本全部重定向输出到文件file中，原理就是：

  > 前置知识：
  >
  > 标准输入和输出是对终端的读与写的2个过程。在Linux中一切皆文件，终端也抽象成了一个文件:`/dev/tty`。
  >
  > 标准输入就是以只读方式打开了这个文件：
  >
  > ​	int in = open("/dev/tty",O_RDONLY);
  >
  > 标准输出就是只写方式打开了它：
  >
  > ​	int out = open("/dev/tty",O_WRONLY);

  > 1、在执行这个程序之前，当前终端，也就是shell进程使用系统调用open先把使用到的文件`file`，获得它的文件描述符fd，如：
  >
  > ​	int fd = open("file",O_CREAT | O_WRONLY,0664)。
  >
  > ​	打开的操作背后是：
  >
  > ​	内核会在全局文件打开表中新增一个文件表项，把表项在数组的下标复制到进程的文件描述符表中；
  >
  > ​	文件描述符表也可以看成是一个数组，添加这一项之后，系统调用open函数会返回这一项在数组中的偏移量，即下标，这就是文件描述符fd。
  >
  > 2、fork()创建子进程，该函数会复制父进程打开的文件描述符，同时内核会修改fd指向的文件打开表项，将它的打开记录+1。这样就实现了父子进程共享这个文件表项的所有信息，包括读写指针。
  >
  > 3、子进程调用dup2(fd,1)，将1指向的文件表项删除，也就是关闭标准输出；将fd指向的文件表项复制给标准输出的描述符1，close(fd)，关闭fd的引用。这样就将文件描述符1重定向到了文件file。
  >
  > 4、当库函数printf、fprintf(stdout)进行输出内容时，底层调用的都是write(1)，往文件描述符`1`中写数据，而子进程当前的文件描述符`1`指向的文件实际上不是`/dev/tty`文件，而是file文件，调用`write(1)`就会写入file文件。

  ##### demo1：

  源代码`menu1.c`编译后得到`menu`:

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  
  char* menu[] ={
          "a - add new record",
          "d - delete a record",
          "q - quit",
          NULL
  };
  //选择界面
  int getChose(char* info,char** menu){
          int selected,chosed;
          //加载界面
          char** ops = menu;
          while(*ops)
                  printf("%s\n",*ops++);
          printf("%s\n",info);
          selected = getchar();
          while(getchar() != '\n');//读取剩余字符直到读到\n
          ops = menu;
          chosed = 0;
          while(*ops){
                  if(selected == (*ops)[0]){
                          chosed =1;
                          break;
                  }
                  ops++;
          }
          //如果选择的不对，则进行选择
          if(!chosed){
                  printf("输入有误，请重新选择!\n");
                  return getChose(info,menu);
          }
          return selected;
  }
  
  int main(){
          int chose;
          do{
                  chose = getChose("请选择对菜单的操作:",menu);
                  printf("你选择的操作是: %c\n",chose);
          }while(chose != 'q');
          return 0;
  }
  ```

  当对程序进行重定向后：

  ```bash
  $./menu > file.txt
  ```

  所有printf输出的消息都放在了`file.txt`文件中。

  ##### demo2：

  `menu2.c` 使用打开文件流的方式`fopen("/dev/tty")`打开标准输入输出文件流，实现了对该文件的直接操作:

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #define FILE_NAME "/dev/tty"
  char* menu[] ={
          "a - add new record",
          "d - delete a record",
          "q - quit",
          NULL
  };
  //选择界面
  int getChose(char* info,char** menu,FILE* in,FILE* out){
          int selected,chosed;
          //加载界面
          char** ops = menu;
          while(*ops)
                  fprintf(out,"%s\n",*ops++);
          fprintf(out,"%s\n",info);
          selected = getc(in);
          while(getc(in) != '\n');//读取剩余字符直到读到\n
          ops = menu;
          chosed = 0;
          while(*ops){
                  if(selected == (*ops)[0]){
                          chosed =1;
                          break;
                  }
                  ops++;
          }
          //如果选择的不对，则进行选择
          if(!chosed){
                  fprintf(stderr,"输入有误，请重新选择!\n");
                  return getChose(info,menu,in,out);
          }
          return selected;
  }
  
  int main(){
          int chose;
          FILE *in,*out;
          //判断标准输出的fd是否连接到终端
          if(!isatty(fileno(stdout)))
                  fprintf(stderr,"标准输出已重定向!\n");
          //使用打开文件流的方式获取文件输入输出流
          in = fopen(FILE_NAME,"r");
          out = fopen(FILE_NAME,"w");
          do{
                  chose = getChose("请选择对菜单的操作:",menu,in,out);
                  fprintf(out,"你选择的操作是: %c\n",chose);
          }while(chose != 'q');
          return 0;
  }
  ```

  

  其中用到了两个函数：

  ```c
  #include <stdio.h>
  //通过文件流获得它的文件描述符
  int fileno(FILE *stream);
  
  //另一个fd与文件流关联函数,将fd关联到文件流并返回。
  FILE *fdopen(int fd, const char *mode);
  
  #include <unistd.h>
  //文件描述符fd是否指向终端：1、是；0：不是
  int isatty(int fd);
  ```

  使用命令：

  ```bash
  $./menu2 > file.txt 
  ```

  该文件中的所有输出都在终端正常显示，不受重定向的影响了，说明直接打开`/dev/tty`文件对其进行读写等同于对终端进行读写，验证了上面的观点。

- #### 文件锁：

  利用系统调用open的原子性，当O_CREAT | O_EXCL时，如果已经存在这个文件，会失败返回-1的特性：

  ```c
  #include <stdio.h>
  #include <fcntl.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #define FILE_LOCK_NAME "./LOCK"
  //使用 O_CREAT | O_EXCL 的原子性操作特性创建文件锁
  int main(){
          int fd ;
          pid_t pid = getpid();
          while(1){
                  //如果fd获取失败，说明已经有其他进程使用该锁
                  if((fd = open(FILE_LOCK_NAME,O_RDONLY | O_CREAT | O_EXCL,0444)) == -1){
                          //fprintf(stderr,"[%d]: 文件锁已被占用!\n",pid);
                          //sleep(3);
                          continue;
                  }
                  //fd获取成功，加锁成功，下面是执行临界区代码
                  fprintf(stdout,"文件加锁成功,进程：[%d]正在执行临界区代码..\n",pid);
                  sleep(1);
                  close(fd);
                  unlink(FILE_LOCK_NAME);//一定要注意删除文件，相当于解锁
          }
          return 0;
  }
  ```

  输出：

  ```bash
  $ ./filelock & ./filelock #直接启动两个进程，后台开启一个
  
  [1] 175781
  文件加锁成功,进程：[175782]正在执行临界区代码..	#可以发现两个进程互相争抢文件锁。
  文件加锁成功,进程：[175781]正在执行临界区代码..
  文件加锁成功,进程：[175782]正在执行临界区代码..
  文件加锁成功,进程：[175781]正在执行临界区代码..
  文件加锁成功,进程：[175782]正在执行临界区代码..
  文件加锁成功,进程：[175781]正在执行临界区代码..
  文件加锁成功,进程：[175782]正在执行临界区代码..
  文件加锁成功,进程：[175781]正在执行临界区代码..
  文件加锁成功,进程：[175782]正在执行临界区代码..
  文件加锁成功,进程：[175781]正在执行临界区代码..
  文件加锁成功,进程：[175782]正在执行临界区代码..
  文件加锁成功,进程：[175781]正在执行临界区代码..
  文件加锁成功,进程：[175782]正在执行临界区代码..
  ```

  文件锁实现非常简单，但是锁的粒度偏大，尤其对于大型文件，高并发场景下，这样就引出了分段锁。将文件的不同内存段进行按需锁定，减小锁的粒度，减小线程之间的竞态。

- #### 使用`fcntl(2)`对文件进行锁定:

  ***注意：当使用文件锁之后，一定要使用系统调用`read(2)`、`write(2)`对文件进行操作，千万不要使用带缓冲区的I/O函数`fread/fwrite`,因为这些函数存在缓冲区，在读取文件时会按照块进行读取，会出现实际读到的字节数超过当前需要的字节数(比如需要获取前100个字节，`fread`可能会读取1024个字节，并把剩余字节都放在缓冲区)，当下次再次读取数据时，如果没有记得刷新缓冲区，获取下100个字节就会从缓冲区中读取，而不会继续系统调用读取文件。在多进程存在竞态操作同一个文件的情况下会导致数据不一致的情况。***

  ###### 同一个进程的多线程是共享文件锁的，千万不要在同一进程中的多个线程中使用文件锁，要使用线程同步措施(`mutex`、`cond`、`semaphore`等)

  ```c
  #include <unistd.h>
  #include <fcntl.h>
  //读锁、写锁、解锁的宏定义
  # define F_RDLCK           0 
  # define F_WRLCK           1 
  # define F_UNLCK           2
  //文件基准位置的宏定义：
  # define SEEK_SET      0
  # define SEEK_CUR      1
  # define SEEK_END      2
  
  //函数原型，cmd参数后面还需添加一个参数：struct flock* fl
  int fcntl(int fd, int cmd, ... /* arg */ );
  /**
  	给文件加解锁(分段锁)，当描述符关闭，锁自动释放
  	成功：0
  	失败：-1，设置errno。注意，如果内核检测到了出现死锁，会返回错误，需要对死锁情况进行释放锁的操作。
  */
  int fcntl(int fd, int cmd, struct flock* flock_structure );
  /**
  	该结构体的 l_whence、l_start 和 l_len 字段用于指定我们希望锁定的字节范围。可以锁定文件末尾之后的字节，但不能锁定文件起始位置之前的字节。
  	若解锁时的区间比加锁区间小，内核只会释放这两个区间重叠部分的那段内存的锁，不重叠的部分仍然是有锁状态。
  	若解锁范围比加锁区间更大，包含了本没有锁的内存区域，内核只会把有锁的区间解锁，没锁的区间不受影响。
  */
  struct flock {
      short l_type;    /* 锁类型：F_RDLCK(读锁), F_WRLCK(写锁), F_UNLCK(解锁) */
      short l_whence;  /* l_start 的基准位置：SEEK_SET, SEEK_CUR, SEEK_END */
      off_t l_start;   /* 锁起始偏移（相对于 l_whence） */
      off_t l_len;     /* 锁定的字节长度；0 代表锁到文件末尾 */
      pid_t l_pid;     /* 持有锁的进程PID，仅 F_GETLK 查询时内核填充 */
      // ... 后面还有一些扩展成员，不同平台略有差异
  };
  ```

  ##### 对于锁的结构体`struct flock`,字段解释如下：

  > 1、`l_type` 字段可用于对文件施加读锁（F_RDLCK）或写锁（F_WRLCK）。多个进程可在同一文件区域持有读锁（共享锁），但同一时刻仅允许一个进程持有写锁（排他锁）。排他锁会阻止其他所有锁，无论是共享锁还是排他锁。
  >
  > ​	单个进程在同一个文件区域上只能持有一种类型的锁；如果对已加锁区域施加新锁，则原有锁会转换为新的锁类型。（如果新锁指定的字节范围和原有锁范围不完全重合，这类锁转换可能会对原有锁进行拆分、缩减或是合并操作。）

  > 2、`l_whence`为基准位置，取值有三个：
  >
  > SEEK_SET: 文件起始位置；
  >
  > SEEK_CUR:当前位置；
  >
  > SEEK_END：文件末尾。

  > 3、`l_start`: 相对于基准位置`l_whence`而言的偏移量，也是锁的起始偏移量。只要最终偏移量不会落在文件起始位置之前，l_start 可以取负值。

  > 4、`l_len` 指定待锁定的字节数量。
  >
  > 若 `l_len` 为正数，则锁定范围覆盖从 `l_start` 开始，到 `l_start+l_len-1`（包含该字节）为止的所有字节。
  >
  > 将 `l_len` 设置为0具有特殊含义：锁定由 `l_whence` 和 `l_start` 指定位置开始，一直到文件末尾的全部字节，无论后续文件增大到多大。
  >
  > `POSIX.1-2001` 允许（但不强制要求）实现支持负的 `l_len` 值；当 `l_len` 为负数时，锁描述的区间覆盖从 `l_start+l_len` 到 `l_start-1`（包含该字节）的字节，也就是相对于`l_start`往前`l_len`个字节。
  >
  > Linux 自内核版本2.4.21与2.5.49起支持该特性。

  

  > Linux 实现了符合 `POSIX` 标准的传统（与进程关联的）UNIX 记录锁。如需具备更优语义、Linux 特有的替代方案，请参阅下文关于打开文件描述符锁的说明。
  > `F_SETLK`、`F_SETLKW` 和 `F_GETLK` 用于获取、释放以及检测记录锁（也称作字节范围锁、文件段锁或文件区域锁）是否存在。第三个参数 lock 是一个结构体指针，该结构体至少包含下列字段（字段顺序未做规定）。

  ##### 锁的命令`cmd`参数有如下选项：

  ###### `F_SETLK (struct flock *)`:不阻塞版的加锁、解锁

  > ​	对lock结构体中l_whence、l_start和`l_len`字段指定的字节区域执行加锁（当l_type为`F_RDLCK`或`F_WRLCK`时）或解锁（当l_type为`F_UNLCK`时）操作。如果另一个进程持有冲突锁，该调用返回-1，并将`errno`设置为`EACCES`或`EAGAIN`。（不同实现在此场景返回的错误有所差异，因此POSIX标准要求可移植应用程序需要同时检查这两种错误。）

  ###### `F_SETLKW (struct flock *)`:阻塞版的加锁、解锁

  > ​	功能同`F_SETLK`，但如果文件上存在冲突锁，则会阻塞等待该锁释放。若等待过程中捕获到信号，该调用会被中断，（信号处理函数返回后）立即返回（返回值为-1，`errno`设置为`EINTR`；参见signal(7)）。

  ###### `F_GETLK (struct flock *)`:获取锁的状态(不会加锁，仅获得当前锁状态)

  > ​	调用传入时，lock结构体描述我们期望在文件上施加的锁。如果该锁可以成功施加，`fcntl()`并不会实际加锁，而是在lock结构体的l_type字段返回`F_UNLCK`，结构体其余字段保持不变。注意：调用方查看该返回信息时，信息可能已经失效(锁存在竞态)。
  >
  > ​	倘若存在一个或多个互斥锁导致本次上锁操作无法执行，`fcntl ()`会在 lock 的 l_type、l_whence、l_start 以及 l_len 字段中返回其中一个冲突锁的详细信息。若冲突锁是传统的（与进程关联的）记录锁，则 `l_pid` 字段会设置为持有该锁进程的进程 ID。若冲突锁是打开文件描述符锁，则 l_pid 设为 - 1。请注意，调用者查看返回信息时，该信息可能已经失效。

  ##### 测试锁：

  程序`segmentlock1.c`是创建文件，给文件的0~127这128个字节施加读锁，256~511这256个字节施加写锁：

  ```c
  #include <fcntl.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #define FILE_NAME "./segment.lock"
  #define FAIL_EXIT(__MSG,__FD) perror(__MSG); \
                          if(__FD >= 0) \
                                  close(__FD); \
                          exit(EXIT_FAILURE)
  //使用fcntl()设置分段锁
  int main(){
          int fd;
          if((fd = open(FILE_NAME,O_RDWR | O_CREAT | O_APPEND,0666))== -1){
                  FAIL_EXIT("open file error",-1);
          }
          //设置文件大小
          ftruncate(fd,1024);
          //设置分段锁
          struct flock region1,region2;
          //第一个区间0~127，128个字节设置读锁，即共享锁
          region1.l_type = F_RDLCK;
          region1.l_whence = SEEK_SET;
          region1.l_start = 0;
          region1.l_len = 128;
          //第二个区间 256~511,256个字节设置读锁
          region2.l_type = F_WRLCK;
          region2.l_whence = SEEK_SET;
          region2.l_start = 256;
          region2.l_len = 256;
  
          if(fcntl(fd,F_SETLKW,&region1)){
                  FAIL_EXIT("lock region2 error",fd);
          }
          if(fcntl(fd,F_SETLKW,&region2)){
                  FAIL_EXIT("lock region2 error",fd);
          }
          printf("分段锁加锁成功!\n");
          sleep(10);
          printf("10s时间到，释放写锁\n");
          region2.l_type = F_UNLCK;
          if(fcntl(fd,F_SETLKW,&region2)){
                  FAIL_EXIT("unlock region2 error",fd);
          }
          printf("释放写锁成功.\n");
          sleep(60);
          printf("60s时间到，进程正在退出.\n");
          close(fd);
          //unlink(FILE_NAME);
          return 0;
  }
  ```

  文件`segmentlock2.c`进行各种测试：

  ```c
  #include <fcntl.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #define FILE_NAME "./segment.lock"
  #define FAIL_EXIT(__MSG,__FD) perror(__MSG); \
                          if(__FD >= 0) \
                                  close(__FD); \
                          exit(EXIT_FAILURE)
  //输出锁结构体信息
  void print_flock(struct flock*);
  //获取锁的封装函数
  void getflock(int ,struct flock*);
  //测试区间锁
  int main(){
          int fd;
          if((fd = open(FILE_NAME,O_RDWR)) == -1){
                  FAIL_EXIT("open file error",-1);
          }
          //定义锁区间，测试锁
          struct flock test_region;
          //测试读锁
          test_region.l_type = F_RDLCK;
          test_region.l_whence = SEEK_SET;
          test_region.l_start = 0;
          test_region.l_len = 100;
          test_region.l_pid = -2;
          printf("测试0~127字节区间的读锁:\n");
          getflock(fd,&test_region);
          //测试写锁
          test_region.l_type = F_WRLCK;
          printf("测试0~127字节区间的写锁:\n");
          getflock(fd,&test_region);
          //测试256~655区间的读锁
          test_region.l_type = F_RDLCK;
          test_region.l_whence =SEEK_SET;
          test_region.l_start = 256;
          test_region.l_len = 400;
          test_region.l_pid = -2;
          printf("测试256~655区间的读锁:\n");
          getflock(fd,&test_region);
  
          //尝试在存在读锁的区间再次加读锁
          test_region.l_type = F_RDLCK;
          test_region.l_whence =SEEK_SET;
          test_region.l_start =0;
          test_region.l_len = 100;
          printf("尝试在0~99区间加读锁:\n");
          if(fcntl(fd,F_SETLKW,&test_region)){
                  FAIL_EXIT("set rdlck error",fd);
          }
          printf("添加读锁成功\n");
          char buf[101]={0};
          if(read(fd,buf,100) < 0){
                  FAIL_EXIT("read info error",fd);
          }
          printf("读到的内容 = %s\n",buf);
          test_region.l_type =F_UNLCK;
          if(fcntl(fd,F_SETLKW,&test_region)){
                  FAIL_EXIT("unlock rdlck error",fd);
          }
          //测试是否在有写锁时可写
          printf("测试有写锁时在不测试锁的状态下能否写入\n");
          strcpy(buf,"hello");
          lseek(fd,256,SEEK_SET);
          if(write(fd,buf,strlen(buf)+1) <=0){
                  FAIL_EXIT("不能写入!",fd);
          }
  
          /*
          test_region.l_type =F_UNLCK;
          if(fcntl(fd,F_SETLKW,&test_region)){
                  FAIL_EXIT("unlock error",fd);
          }
  
          */
          close(fd);
          return 0;
  }
  
  void getflock(int fd,struct flock* test_region){
          if(fcntl(fd,F_GETLK,test_region)){
                  FAIL_EXIT("getlock error",fd);
          }
          print_flock(test_region);
  }
  
  void print_flock(struct flock* info){
          printf("l_type = %d\n",info->l_type);
          printf("l_whence = %d\n",info->l_whence);
          printf("l_start = %ld\n",info->l_start);
          printf("l_len = %ld\n",info->l_len);
          printf("l_pid = %d\n",info->l_pid);
  }
  ```

  输出结果：

  ##### 启动顺序：先启动`./segmentlock1`,在启动`./segmentlock2`

  ```shell
  测试0~127字节区间的读锁:
  l_type = 2	# 2是宏F_UNLOCK，表示可以对该区间进行加锁，其他字段都没变
  l_whence = 0
  l_start = 0
  l_len = 100
  l_pid = -2
  
  测试0~127字节区间的写锁: 
  l_type = 0	# 0的宏为F_RDLCK,后面的字段也变了(l_len变成了128，l_pid改成了拥有锁进程ID)，
  l_whence = 0	#表示当前进程 176458 持有 0~127字节区间的读锁。
  l_start = 0
  l_len = 128
  l_pid = 176458
  
  测试256~655区间的读锁:
  l_type = 1	# 1是宏F_WRLCK,进程176458拥有 256~511区间的写锁。
  l_whence = 0
  l_start = 256
  l_len = 256
  l_pid = 176458
  
  尝试在0~99区间加读锁:	#读锁是共享锁，可以多进程同时读
  添加读锁成功
  读到的内容 = #include <fcntl.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #d
  测试有写锁时在不测试锁的状态下能否写入 #没有返回错误，查看文件确实写入了，所以多进程之间必须都遵守锁的约束，锁才有意义。
  ```

  

- #### 重定向的函数：

  函数原型如下：

  ```c
  #include <stdio.h>
  /**
  	以mode模式，打开pathname路径的文件，成功后将文件流绑定到stream(当然绑定之前关闭原先的stream)。
  	等价于：
  		int fd = open(pathname,mode);
  		dup2(fd,fileno(stream));
  		close(fd);
  	return:
  		成功：返回新的文件流。
  		失败：NULL，填充errno
  */
  FILE *freopen(const char *pathname, const char *mode, FILE *stream);
  ```

  将其重定向标准输入：

  程序1 `upper.c` ，功能是将键入的字符(标准输入)全部转成大写。

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  
  int main(){
          int ch;
          while((ch = getc(stdin)) != EOF)
                  putc(toupper(ch),stdout);
          return 0;
  }
  ```

  程序2 `upper2.c` ,功能是将传入的pathname打开，重定向到标准输入流，成功后执行`upper.c` 程序：

  程序中用到了两种方法：freopen()与系统调用open()、dup2()，两者原理相通。

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <unistd.h>
  #include <fcntl.h>
  //重定向,使用freopen()函数
  int main(int argc,char** argv){
          if(argc < 2){
                  fprintf(stderr,"参数必须不少于2个\n");
                  exit(EXIT_FAILURE);
          }
          //将文件打开，标准输入关闭，将文件重定向到标准输入
          //等价于fd = open();dup2(fd,0);close(fd)
          /**
          if(!freopen(argv[1],"r",stdin)){
                  perror("open fd error");
                  exit(EXIT_FAILURE);
          }
          */
          int fd = open(argv[1],O_RDONLY);
          if(dup2(fd,0) == -1){
                  perror("dup2 error");
                  exit(EXIT_FAILURE);
          }
          close(fd);
          //执行upper程序,该程序以O_RDONLY方式打开/dev/tty，从中read(0)，然后强转成大写write(1)
          execl("./upper","upper",NULL);
          return 0;
  }
  ```

  执行程序：

  ```bash
  $ ./upper2 test.dat	#效果等价于指令： ./upper < test.dat
  
  THIS IS A TEST FILE THIS IS A TEST FILE,THIS IS A TEST FILE
  THIS IS A TEST FILE
  THIS IS A TEST FILE
  THIS IS A TEST FILE,THIS IS A TEST FILETHIS IS A TEST FILE
  ```

  ##### 重定向标准输出:

  如果程序1 `upper.c` 修改为：

  在获取输入流之前，将文件重定向到标准输出，在执行：`./upper2 test.dat` 后，之前的终端输出变成了输出到文件 `a.txt`

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  #define OUT_FILE "./a.txt"
  //重定向
  int main(){
          int ch;
          //测试，重定向标准输出到文件
          if(freopen(OUT_FILE,"w",stdout) == NULL){
                  perror("reopen a.txt error");
                  exit(EXIT_FAILURE);
          }
          while((ch = getc(stdin)) != EOF)
                  putc(toupper(ch),stdout);
          return 0;
  }
  ```

  

- #### 获取系统的相关限制值(`APUE`第二章2.5节)：

  限制值都定义在 `<limits.h>` 或 `<unistd.h>` 中，有些是编译期就确定的常量，有些则是运行时确定的，可以通过以下函数来获取：

  `sysconf(3)` 、`pathconf(3)` 、 `fpathconf(3)` .

  ```c
  #include <unistd.h>
  /**
  	通过name查询该属性值的限制值,失败返回-1，成功则返回相应的值
  	name: 要查询的属性名称，在linux下需要在名称添加前缀 _SC_ ,具体详情查阅sysconf(3)或者查看APUE第二章p31-2.5.4节.
  */
  long sysconf(int name);
  
  //分别根据文件描述符fd、文件路径path 查询name的属性值，与sysconf返回值规定相同。
  //在Linux下这两个函数的name需要添加 _PC_ ，具体支持的name查阅pathconf(3)或APUE第二章2.5节
  long fpathconf(int fd, int name);
  long pathconf(const char *path, int name);
  ```

  demo:

  ```c
  #include <stdio.h>
  #include <limits.h>
  #include <unistd.h>
  int main(){
          //sysconf(3)获取系统的限制项,name以_SC_为开头
          printf("一个进程能同时打开的文件数量 = %ld\n",sysconf(_SC_OPEN_MAX));
          //pathconf(3)，name以_PC_开头
          printf("文件名的最长为 %ld\n",pathconf("./t1.c",_PC_PATH_MAX));
          //fpathconf(3)，name以_PC_开头
          printf("终端输入的最长字节数为 %ld\n",fpathconf(0,_PC_MAX_CANON));
          return 0;
  }
  ```

  

- #### 刷新缓冲区的脏数据到磁盘(2)：

  ```c
  #include <unistd.h>
  //刷新所有修改过的缓冲区，只会放到刷新队列后立刻返回不阻塞。
  //不能保证立刻落实到磁盘
  void sync(void);
  
  //阻塞刷新fd指向的文件，刷新完成才会返回。返回值：成功0；失败01，填充errno
  //刷新的内容包括文件的数据部分与文件的属性(大小、各种时间、权限等)。
  //适用于数据库这种对持久化要求较高的场景。
  int fsync(int fd);
  //功能同fsync，但是只更新文件的数据部分+文件的大小+文件布局等，至于各种时间、权限等可跳过。
  int fdatasync(int fd);
  ```

  ###### 目录创建文件 `fsync(2)` 时需要注意：

  > 该函数只会修改这个文件描述符`fd`文件`inode`的数据+属性，不会修改他所在目录的`inode`，所以遇到创建文件并且对实时性持久化要求非常高的场景，还需要更新文件所在目录的`inode`:
  >
  > ```c
  > int fd = open("./test",O_CREAT | O_RDWR,0600);
  > ...
  > fsync(fd);	//创建文件，更新到磁盘
  > 
  > int dirfd = open(".",O_RDWR); //不要忘了刷新当前目录的inode
  > fsync(dirfd);
  > ```
  >
  > 

- #### 设置文件流的缓冲区(3):

  ###### 常规情况下，Linux下对标准错误不带缓冲区，标准输入输出是行缓冲(即遇到 `\n` 刷新缓冲区)，其他的流是全缓冲，即缓冲区满了才会刷新到磁盘。下面的函数可以改变流的缓冲区模式。

  ```c
  #include <stdio.h>
  //开启或关闭stream的缓冲区。
  //buf:为缓冲区的地址，NULL时，会关闭缓冲区的功能，后续使用标准I/O函数，效果等同于系统调用，没有缓冲区
  void setbuf(FILE *stream, char *buf);
  /**
  	给stream设置缓冲区类型。
  	buf：缓冲区地址。
  		为NULL时，行为需要依据mode进一步讨论。如果mode指定需要缓冲区，内核会自动维护一个缓冲区。
  		不为NULL时，指定size大小的缓冲区作为stream的缓冲区。
  	mode：缓冲区的模式。
  		_IOFBF: 设置全缓冲区。
  		_IOLBF: 设置行缓冲区。
  		_IONBF: 不设置缓冲区，此时参数buf与size均被忽略。
  		
  	size：缓冲区大小。如果buf为NULL，size会被忽略，系统会自动维护适当大小的缓冲区(通常是BUFSIZ)
  	
  	return：
  		成功： 0
  		失败： 非0，填充errno
  */
  int setvbuf(FILE *stream, char *buf, int mode, size_t size);
  ```

  ###### demo1：使用setbuf启用/取消标准输出的缓冲区

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <string.h>
  //使用setbuf(3)设置缓冲区
  int main(){
      char buf[BUFSIZ];
      setbuf(stdout,buf); //设置标准输出的缓冲区为buf
      fprintf(stdout,"hello world\n");
      write(1,buf,strlen(buf)); //系统调用形式输出buf，结果同上面的语句相同
      //设置取消缓冲区
      setbuf(stdout,NULL); //取消缓冲区
      printf("hahahaha"); //没有换行符也会立即输出
      while(1);
      return 0;
  }
  ```

  输出结果：

  ```bash
  $ ./setbuf
  hello world	#fprintf标准输出
  hello world	# write系统调用直接输出buf到终端的内容，证实了已经把buf当作标准输出的缓冲区
  hahahaha	# 关闭了标准输出缓冲区后，printf没有换行符，内容也刷新出来了
  ```

  

  ###### demo2：使用setvbuf(3)设置标准输出流的全缓冲模式

  ```c
  #include <stdio.h>
  #include <unistd.h>
  //设置缓冲区模式：全缓冲、行缓冲、不缓冲
  int main(){
      //设置标准输出为全缓冲,使用的系统自己管理的缓冲区
      setvbuf(stdout,NULL,_IOFBF,0);
      printf("hello world..\n");
      sleep(5);
      fflush(stdout);
      sleep(2);
          return 0;
  }
  ```

  输出结果：

  ```bash
  $ ./setvbuf
  #在输出hello world.. 之前会有5s的等待时间，证实了stdout设置成全缓冲后，换行符\n不能再刷新缓冲区
  hello world..	#执行fflush主动刷新缓冲区后，才会输出内容
  ```

  

- 
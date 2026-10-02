1. 文件打开/关闭(man 2 ..)：

   ```c
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   
   int open(const char *pathname, int flags);
   int open(const char *pathname, int flags, mode_t mode);
   //flags选项如下： 必选项 [|可选项...]
   1、必选项：
       O_RDONLY: 只读模式
   	O_WRONLY:	只写
   	O_RDWR:	读写
   2、可选项：
       O_TRUNC:	清空文件内容
   	O_APPEND:	原有内容基础上追加
   	O_EXCL:		当|O_CREAT时如果文件存在，会报错，保证文件不会重复创建
   	O_CREAT:	创建文件
   	O_NONBLOCK:	操作文件非阻塞
           
   //mode_t:创建文件时的权限设置,使用三元组对文件的权限进行设置(所属用户 组成员 其他成员)
           //如：0700代表文件持有者拥有全部权限，而其他用户没有权限；0644代表所属用户可读写，组内用户以及其他成员只有读权限。
   1	:可执行x
   2	:写w
   4	：读r
   //返回值： 
       -1 :文件打开失败
       非0的整数：文件描述符
   
   //关闭文件流：
   #include <unistd.h>
   
   int close(int fd);
   ```

   ```c
   #include <stdio.h>
   #include <unistd.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #include <string.h>
   int main(int argc,char** argv,char** env){
           if(argc != 2){
                   fprintf(stderr,"请输入要写入文件的内容\n");
                   return -1;
           }
           int fd = open("test.txt",O_CREAT | O_RDWR | O_APPEND,0644);
           if(fd == -1){
                   fprintf(stderr,"文件打开失败\n");
                   return -1;
           }
           write(fd,argv[1],strlen(argv[1]));
           close(fd);
           return 0;
   }
   ```

   

2. 写入文件(man 2 ..)：

   ```c
   #include <unistd.h>
   /**
   *	fd：文件描述符
   	buf:从哪写
   	count：写入多少字节
   	return: 实际写入的字节数
   	示例见1.open
   */
   ssize_t write(int fd, const void *buf, size_t count);
   ```

   

3. 读取文件(man 2 ..)：

   ```c
   #include <unistd.h>
   /**
   	fd: 要读取文件的描述符
   	buf：往哪读
   	count：最多读取的字节数量
   	return： 实际读取的字节数
   */
   ssize_t read(int fd, void *buf, size_t count);
   ```

   ```c
   #include <stdio.h>
   #include <unistd.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #include <string.h>
   int main(int argc,char** argv,char** env){
           int fd = open("test.txt",O_RDONLY);
           if(fd == -1){
                   fprintf(stderr,"没有该文件\n");
                   return -1;
           }
           char buf[128]={0};
           int r_len = read(fd,buf,sizeof(buf));
           if(r_len){
                   printf("读取的文件长度=%d\n",r_len);
                   fprintf(stdout,"%s\n",buf);
           }
           close(fd);
           return 0;
   }
   ```

   ###### 拷贝文件DEMO：

   ```c
     1 #include <stdio.h>
     2 #include <stdlib.h>
     3 #include <unistd.h>
     4 #include <fcntl.h>
     5 #define BUF_SIZE 1024
     6 //拷贝文件argv[1] -> argv[2]
     7 int main(int argc ,char** argv ,char** env){
     8         char * buf =NULL;
     9         int r_fd = -1,w_fd = -1;
    10         if(argc !=3){
    11                 fprintf(stdout,"请输入要拷贝的文件名称\n");
    12                 exit(-1);
    13         }
    14         r_fd = open(argv[1],O_RDONLY);
    15         if(r_fd ==-1){
    16                 perror("");
    17                 goto fail_ret;
    18         }
    19         w_fd = open(argv[2],O_CREAT | O_WRONLY | O_TRUNC,0644);
    20         if(w_fd ==-1){
    21                 perror("");
    22                 goto fail_ret;
    23         }
    24         buf = malloc(BUF_SIZE);
    25         if(!buf){
    26                 perror("");
    27                 goto fail_ret;
    28         }
    29         //开始从a文件读取到b文件
    30         int r_len;
    31         while(1){
    32                 r_len = read(r_fd,buf,BUF_SIZE);
    33                 write(w_fd,buf,r_len);
    34                 //当读取到的字符数量小于buf总长，读取结束，退出
    35                 if(r_len < BUF_SIZE)
    36                         break;
    37         }
    38         fprintf(stdout,"拷贝结束\n");
    39         close(r_fd);
    40         close(w_fd);
    41         free(buf);
    42         return 0;
    43 fail_ret:
    44         if(r_fd != -1)
    45                 close(r_fd);
    46         if(w_fd != -1)
    47                 close(w_fd);
    48         if(buf)
    49                 free(buf);
    50         exit(-1);
    51 }
   ```

4. 修改文件指针(man 2 lseek)：

   ```c
   #include <sys/types.h>
   #include <unistd.h>
   //设置文件的当前光标位置
   /**
   	fd : 文件描述符
   	offset:	相对于第三个参数的偏移量，可正可负
       whence:	从哪个位置开始计算偏移量
   */
   off_t lseek(int fd, off_t offset, int whence);
   //whence取值：
   SEEK_SET: 文件起始位置
   SEEK_CUR: 当前位置
   SEEK_END: 文件结尾
   ```

   ###### DEMO:

   ```c
     1 #include <stdio.h>
     2 #include <unistd.h>
     3 #include <sys/types.h>
     4 #include <sys/stat.h>
     5 #include <fcntl.h>
     6 #include <string.h>
     7 //lseek设置光标位置
     8 int main(int argc,char** argv,char** env){
     9         int fd = open("test.txt",O_RDONLY);
    10         if(fd == -1){
    11                 fprintf(stderr,"没有该文件\n");
    12                 return -1;
    13         }
    14         char buf[128]={0};
    15         int r_len = read(fd,buf,sizeof(buf)-1);
    16         if(r_len){
    17                 printf("读取的文件长度=%d\n",r_len);
    18                 fprintf(stdout,"%s\n",buf);
    19         }
    20         //设置光标位置 = 当前位置往前移动r_len个字节
    21         lseek(fd,-r_len,SEEK_CUR);
    22         r_len = read(fd,buf,sizeof(buf)-1);
    23         if(r_len){
    24                 printf("读取的文件长度=%d\n",r_len);
    25                 fprintf(stdout,"%s\n",buf);
    26         }
    27         close(fd);
    28         return 0;
    29 }
   ```

   

5. 设置文件属性-fcntl(man 2 fcntl)：

   ```c
   #include <unistd.h>
   #include <fcntl.h>
   //对打开了的文件描述符进行各种操作，包括获取、复制、修改文件描述符的标志..
   /**
   fcntl函数有5种功能：
   
   1.复制一个现有的描述符（cmd=F_DUPFD）.
   
   2.获得／设置文件描述符标记(cmd=F_GETFD或F_SETFD).
   
   3.获得／设置文件状态标记(cmd=F_GETFL或F_SETFL).
   
   4.获得／设置异步I/O所有权(cmd=F_GETOWN或F_SETOWN).
   
   5.获得／设置记录锁(cmd=F_GETLK,F_SETLK或F_SETLKW).
   */
   int fcntl(int fd, int cmd, ... /* arg */ );
   ```

   设置文件描述符为非阻塞(仅针对设备，普通文件没有非阻塞特性)：

   ```c
     1 #include <stdio.h>
     2 #include <fcntl.h>
     3 #include <unistd.h>
     4 #include <stdlib.h>
     5 //设置设备文件为非阻塞
     6 int main(){
     7         //方案1：打开文件时设置打开方式 | O_NONBLOCK
     8         //int fd = open("/dev/tty",O_RDONLY | O_NONBLOCK );
     9         int fd = open("/dev/tty",O_RDONLY);
    10         if(fd == -1){
    11                 perror("");
    12                 exit(-1);
    13         }
    14         //方案2：使用系统调用fcntl设置文件的属性
    15         int flags = fcntl(fd,F_GETFL);
    16         flags |= O_NONBLOCK;
    17         fcntl(fd,F_SETFL,flags);
    18         fprintf(stdout,"设备的fd = %d\n",fd);
    19         char buf[128];
    20         read(fd,buf,sizeof(buf));
    21         printf("buf = %s\n",buf);
         		close(fd);
    22         return 0;
    23 }
   ```

   

6. 获取文件的属性stat(man 2 stat)：

   ```c
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <unistd.h>
   //获取文件属性，主要包括文件类型、权限、大小等等
   //return : 0 查询成功，结果放入stat结构体；-1：失败，错误信息码保存在errno
   int stat(const char *pathname, struct stat *statbuf);
   //stat结构体：
   struct stat {
          dev_t     st_dev;         /* ID of device containing file */
          ino_t     st_ino;         /* Inode number */
          mode_t    st_mode;        /* File type and mode 获取文件的属性以及权限 */
          nlink_t   st_nlink;       /* Number of hard links */
          uid_t     st_uid;         /* User ID of owner */
          gid_t     st_gid;         /* Group ID of owner */
          dev_t     st_rdev;        /* Device ID (if special file) */
          off_t     st_size;        /* 文件大小，以字节为单位 */
          blksize_t st_blksize;     /* Block size for filesystem I/O */
          blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */
   
          /* Since Linux 2.6, the kernel supports nanosecond
             precision for the following timestamp fields.
             For the details before Linux 2.6, see NOTES. */
   
          struct timespec st_atim;  /* Time of last access */
          struct timespec st_mtim;  /* Time of last modification */
          struct timespec st_ctim;  /* Time of last status change */
   
      #define st_atime st_atim.tv_sec      /* Backward compatibility */
      #define st_mtime st_mtim.tv_sec
      #define st_ctime st_ctim.tv_sec
   };
   
   //宏定义以及用来判断文件属性的宏函数
   
   //文件类型的宏定义：
   S_IFMT     0170000  //文件类型的宏定义
   
   S_IFSOCK   0140000   //套接字文件
   S_IFLNK    0120000   //链接文件
   S_IFREG    0100000   //普通文件
   S_IFBLK    0060000   //块设备
   S_IFDIR    0040000   //目录文件
   S_IFCHR    0020000   //字符设备
   S_IFIFO    0010000   //管道
       
   //文件权限的定义：
   S_IRWXU		00700	//文件持有者的读写可执行权限
   S_IRUSR     00400   //属主拥有读权限
   S_IWUSR     00200   //属主拥有写权限
   S_IXUSR     00100   //属主拥有可执行权限
       
   S_IRWXG		00070	//属组的读写可执行权限
   S_IRGRP     00040   //属组读权限
   S_IWGRP     00020   //属组写权限
   S_IXGRP     00010   //属组可执行权限
       
   S_IRWXO		00007	//其他用户的读写可执行权限
   S_IROTH     00004   //其他用户读权限
   S_IWOTH     00002   //其他用户写权限
   S_IXOTH     00001   //其他用户可执行权限
       
   //使用方法： stat.st_mode & S_IFMT == S_IFREG 用来判断是否为普通文件
   //或者可以使用后面的宏函数进行判断。
   stat(pathname, &sb);
   if ((sb.st_mode & S_IFMT) == S_IFREG) {
      /* Handle regular file */
   }
   
   //POSIX定义了宏函数，可以更方便的判断文件属性, m = st.st_mode
   S_ISREG(m)  //判断是否为普通文件
   S_ISDIR(m)  //是否为目录
   S_ISCHR(m)  //是否为字符设备
   S_ISBLK(m)  //是否为块设备
   S_ISFIFO(m) //是否为管道
   S_ISLNK(m)  //是否为链接文件(Not in POSIX.1-1996.)
   S_ISSOCK(m) //是否为socket(Not in POSIX.1-1996.)
   //使用方法：
   stat(pathname, &sb);
   if (S_ISREG(sb.st_mode)) {
      /* Handle regular file */
   }
   ```

   ###### DEMO:

   ```c
     1 #include <sys/types.h>
     2 #include <sys/stat.h>
     3 #include <unistd.h>
     4 #include <stdio.h>
     5 #include <stdlib.h>
     6 //stat函数的使用
     7 int main(int argc,char** argv,char** env){
     8         if(argc != 2){
     9                 fprintf(stderr,"请输入要查询的文件名\n");
    10                 exit(-1);
    11         }
    12         struct stat st;
    13         int flag = stat(argv[1],&st);
    14         if(flag == -1){
    15                 perror("");
    16                 exit(-1);
    17         }
         		//以宏函数方式去判断
    18         if(S_ISDIR(st.st_mode)){
    19                 printf("该文件为目录\n");
        		//以宏定义位运算处理:	判断该文件是否为普通文件。				判断该文件的属主是否有读写权限
    20         }else if((st.st_mode & S_IFMT) == S_IFREG  && (st.st_mode & S_IRWXU) == (S_IRUSR | S_IWUSR)){
    21                 printf("该文件为可读写的普通文件,大小为:%ld bytes\n",st.st_size);
    22         }
    23         return 0;
    24 }
   ```

   

7. ##### 目录操作(man 3 ...)：

   - ###### 打开目录：

   ```c
   #include <sys/types.h>
   #include <dirent.h>
   //根据目录名称打开，返回目录的文件句柄
   //return ： 成功返回非NULL指针，失败返回NULL，并填充errno
   DIR *opendir(const char *name);
   typedef struct __dirstream DIR;
   //该结构体在glibc的内部库，不对外透明，无法通过该结构体直接操作内部属性
   struct __dirstream
   {
       int fd;               /* associated file descriptor */
       char *data;           /* buffer for directory entries */
       size_t allocation;    /* buffer allocated size */
       size_t size;          /* valid bytes in buffer */
       size_t offset;        /* current read offset */
       struct dirent *entry; /* pointer to return entry */
       /* ...还有锁等其他成员 */
   };
   ```

   - ###### 读取目录中的内容：

     ```c
     #include <dirent.h>
     /**
     	根据目录句柄读取目录的内容，返回一个目录项的结构体。
     	迭代器模式，类似于迭代器的it.next(),DIR内部维护了一个指针，readdir根据该指针读取，可通过telldir()/seekdir()对指针进行读取、修改
     	return: 返回目录项结构体指针。
     			当为NULL时，表示目录已读完(不填充errno)，或者读取出现异常(填充errno)。
     */
     struct dirent *readdir(DIR *dirp);
     //目录项结构体： d_off与d_reclen这两项用于glibc在遍历内核缓冲区记录、组装目录项结构体时使用，用户调用层面不会用到
     struct dirent {
        ino_t          d_ino;       /* inode号 */
        off_t          d_off;       /* 下一个目录项的偏移 */
        unsigned short d_reclen;    /* 返回的记录的大小，由于文件名的长度参差不齐，内核缓冲区中的记录大小不同，glibc依靠这个字段来拆分记录组装结构体dirent。 */
        unsigned char  d_type;      /* 文件类型。详情见下方的宏 */
        char           d_name[256]; /* 文件名 */
     };
     
     //d_type的宏定义：
      DT_BLK      //块设备
     
     DT_CHR      //字符设备
     
     DT_DIR      //目录
     
     DT_FIFO     //管道
     
     DT_LNK      //链接文件
     
     DT_REG     //普通文件
     
     DT_SOCK     //套接字
     
     DT_UNKNOWN  //未知类型
     ```

   - ###### 获取当前流的指针位置：

     ```c
     #include <dirent.h>
     //返回的是一个long类型的地址，与dirent中的d_off值相同，表示当前指针的位置
     //注意：这里的当前指针不是指向当前dirent的指针，而是指向下一个目录项的指针
     long telldir(DIR *dirp);
     ```

   - ###### 设置目录流的指针位置：

     ```c
     #include <dirent.h>
     //设置目录流的指针到loc位置,loc可通过telldir()来获取
     void seekdir(DIR *dirp, long loc);
     ```

     ##### 注意：示例中设置的读取到文件：cplusplus时记录的指针为指向下一个目录项，所以在seekdir设置这个偏移量后，重新遍历读到的目录项是从cplusplus后面开始的，并不包括cplusplus本身。

     ##### 如果要想从cplusplus文件开始，或者截止到cplusplus。需要实时记录偏移量并修改，直到cplusplus这个目录项为止

     ```c
     28         //开始打开目录
     29         d_ptr =  opendir(argv[1]);
     30         if(!d_ptr){
     31                 perror("");
     32                 return -1;
     33         }
     34         //开始读取目录下的文件
     35         struct dirent* dir_ptr;
     36         long dir_off;
     37         while((dir_ptr = readdir(d_ptr))){
     38                 //记录读取到cplusplus文件时的指针位置
     39                 if(!strcmp(dir_ptr->d_name,"cplusplus")){
     40                         dir_off = telldir(d_ptr);
     41                         break;
     42                 }
     43         }
     44
     45         //seekdir
     46         seekdir(d_ptr,dir_off);
     47         //重新设置光标之后再次读取一遍
     48         int cnt =0;
     49         while((dir_ptr = readdir(d_ptr))){
     50                 cnt++;
     51                 printf("文件名：%s\n",dir_ptr->d_name);
     52                 switch(dir_ptr->d_type){
     53                         case DT_DIR :
     54                                 printf("类型为目录\n");
     55                                 break;
     56                         case DT_REG :
     57                                 printf("类型为普通文件\n");
     58                                 break;
     59                         default :
     60                                 printf("类型为设备(块、字符、管道、socket等)。\n");
     61                                 break;
     62                 }
     63         }
     ```

     ##### 修改后的版本：

     ```c
      28         //开始打开目录
      29         d_ptr =  opendir(argv[1]);
      30         if(!d_ptr){
      31                 perror("");
      32                 return -1;
      33         }
      34         //开始读取目录下的文件
      35         struct dirent* dir_ptr;
      36         long dir_off;
      37         while((dir_ptr = readdir(d_ptr))){
      38                 if(!strcmp(dir_ptr->d_name,"cplusplus"))
      39                         break;
      40                 //1、通过telldir()记录读取到指定文件时的指针位置
      41                 //dir_off = telldir(d_ptr);
      42                 //2、通过dirent结构体的d_off来获取，避免多次telldir()调用开销
      43                 dir_off = dir_ptr->d_off;
      44         }
      45
      46         //seekdir
      47         seekdir(d_ptr,dir_off);
      48         //重新设置光标之后再次读取一遍
      49         int cnt =0;
      50         while((dir_ptr = readdir(d_ptr))){
      51                 cnt++;
      52                 printf("文件名：%s\n",dir_ptr->d_name);
      53                 switch(dir_ptr->d_type){
      54                         case DT_DIR :
      55                                 printf("类型为目录\n");
      56                                 break;
      57                         case DT_REG :
      58                                 printf("类型为普通文件\n");
      59                                 break;
      60                         default :
      61                                 printf("类型为设备(块、字符、管道、socket等)。\n");
      62                                 break;
      63                 }
      64         }
     ```

     

   - ###### 关闭目录流：

     ```c
     #include <sys/types.h>
     #include <dirent.h>
     
     int closedir(DIR *dirp);
     ```

     

   - ###### 扫描目录，返回所有的目录项：

     ```c
     #define _GNU_SOURCE
     #include <dirent.h>
     /**
     	dirp:文件目录的路径。(该函数没有像上面那些函数一样使用DIR文件句柄)
     	namelist: 目录项数组的首地址。查询结果会放到一个malloc好的数组中，并将数组的首地址赋值给该参数。
     			(注意：该函数内部会主动malloc堆空间，所以调用该函数时必须要注意释放它的内存。)
     	filter：设置过滤规则的函数。
     			为NULL时会把所有文件放到namelist，自定义的filter返回值非0的会放到namelist中
     	compar: 数组列表的排序规则，不允许为空，可使用按照ASCII大小排序，或者按照版本号排序
     	return: -1:出现错误，错误码存储在errno
     			成功则返回数组的长度
     */
     int scandir(const char *dirp, struct dirent ***namelist,int (*filter)(const struct dirent *),
                 int (*compar)(const struct dirent **, const struct dirent **));
     //2种排序规则：注意，必须显式声明_GNU_SOURCE，并且声明位置要早于头文件dirent.h
     //按照ASCII大小排序
     int alphasort(const struct dirent **a, const struct dirent **b);
     //按照版本号排序
     int versionsort(const struct dirent **a, const struct dirent **b);
     ```

     ###### DEMO(过滤掉文件夹.与..):

     ```c
       1 #define _GNU_SOURCE
       2 #include <unistd.h>
       3 #include <sys/types.h>
       4 #include <dirent.h>
       5 #include <string.h>
       6 #include <stdio.h>
       7 #include <stdlib.h>
       8 int filter_dir(const struct dirent *);
       9 int main(int argc,char** argv,char** env){
      10         if(argc != 2){
      11                 fprintf(stderr,"请输入目录名称\n");
      12                 return -1;
      13         }
      14         struct dirent** dir_arr = NULL;
      15         int arr_len = scandir(argv[1],&dir_arr,filter_dir,alphasort);
      16         //int arr_len = scandir(argv[1],&dir_arr,filter_dir,versionsort);
      17         if(arr_len == -1){
      18                 perror("scandir error:");
      19                 return -1;
      20         }
      21         int i;
      22         for(i=0;i<arr_len;++i){
      23                 struct dirent* dir = dir_arr[i];
      24                 printf("文件: [%s],类型：%s\n",dir->d_name, 
                                dir->d_type ==  DT_REG ? "普通文件" : dir->d_type == DT_DIR ? "目录" : "其他设备文件");
      25                 free(dir);	//注意一定要释放堆内存，避免内存泄漏
      26                 dir_arr[i] =NULL;
      27         }
      28         free(dir_arr);	//释放内存
      29         dir_arr = NULL;
      30         return 0;
      31 }
      32
      33 //int (*filter)(const struct dirent *),
      34 //条件过滤。在这里过滤掉名称为. 与 ..的目录
      35 int filter_dir(const struct dirent * ent){
          		//返回值为0的过滤掉，不为0的会放到namelist数组
      36         if(!strcasecmp(ent->d_name,".") || !strcasecmp(ent->d_name,".."))
      37                 return 0;
      38         return 1;
      39 }
     ```

     

8. 信号：

   ```bash
   #可通过trap -l来查看系统支持的信号类型
   trap -l
   
   tqx@linux-ubuntu:~/linux-learn/shell$ trap -l
    1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
    6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
   11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
   16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
   21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
   26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
   31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
   38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
   43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
   48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
   53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
   58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
   63) SIGRTMAX-1  64) SIGRTMAX
   ```

   

9. #### 获取系统的进程号：

   ```c
   pid_t getpid();		//获取当前进程的进程号
   pid_t getppid();	//获取父进程号
   pid_t getpgid(pid_t pid); //获取指定进程的组id,参数为0，表示获取当前进程组的组号
   int setpgid(pid_t pid, pid_t pgid); //将pid进程放到进程组pgid中，成功返回0，失败返回-1，并填充errno
   typedef int pid_t;
   ```

   ###### DEMO:

   ```c
   #include <stdio.h>
   #include <unistd.h>
   
   int main(){
           pid_t cur_pid = getpid();
           printf("当前的组id = %d\n",getpgid(cur_pid));	//这两组获取组id的方式等价，都是获取当前进程组的组号
           printf("当前的组id2 = %d\n",getpgid(0));
           return 0;
   
   }
   ```

   

10. #### 创建进程fork(man 2 fork...):

    ```c
    #include <unistd.h>
    /**
    return: 
    	-1：创建失败，失败码在errno提取。
    	0: 子进程的返回值。
    	>0:父进程的返回值，返回的是子进程的ID。
    */
    pid_t fork(void);
    //fork时会对父进程的PCB、栈、堆、代码段等所有数据都会进行拷贝。注意，在Linux下，如果缓冲区内有数据没有取出，通过fork()创建出的子进程会复制缓冲区，这种情况缓冲区内数据也会被拷贝。
    ```

    ###### DEMO:

    ```c
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(int argc,char** argv,char** env){
            //char buf[] = "这是系统";
            if(argc !=3){
                    fprintf(stderr,"请输入父进程、子进程输入\n");
                    return -1;
            }
            printf("父进程的输入：%s\n",argv[1]);
            printf("当前进程ID：%d\n",getpid());
            pid_t pid;
            if((pid = fork()) < 0 ){
                    perror("");
            }
            if(!pid){
                    printf("子进程输入:%s\n",argv[2]);
                    printf("子进程中父进程的输入:%s\n",argv[1]);
                    printf("当前进程ID2 = %d\n",getpid());
                    printf("父进程ID= %d\n",getppid());
                	//执行exit后，子进程退出，后面的语句就不会执行
                    exit(0);
            }else{
                    printf("父进程fork(),子进程ID = %d\n",pid);
            }
            //当fork()完成后，会生成子进程共同执行该代码，一共2个进程执行，所以这条输出会生成2条。
            //不让子进程执行该代码，解决办法就是在子进程执行的代码最后添加退出语句exit
            printf("最后输出：pid = %d\n",getpid());
            return 0;
    }
    ```

    

11. 子进程的回收：

    ```c
    //fork()生成的子进程在退出后，系统会自动回收它所占用的除PCB之外的所有资源，但是PCB必须要父进程去回收，否则就要等到父进程退出时才会统一回收。
    //如下示例显示了内存泄漏的问题：
    #include <unistd.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    
    int main(){
            pid_t pid;
            if((pid = fork()) <0)
                    perror("");
            else if(pid == 0){
                    printf("子进程执行...\n");	//子进程执行后退出
                    exit(0);
            }else{
                    while(1){
                            printf("父进程正在执行...\n");	//父进程持续循环，不会退出，子进程的PCB不会被回收。
                            sleep(1);
                    }
            }
            return 0;
    }
    ```

    ```bash
    tqx@LAPTOP-G3KT1I3B:/mnt/c/Users/田庆新$ ps -aux | grep wait
    tqx        795  0.0  0.0   2676  1032 pts/0    S+   15:04   0:00 ./wait
    tqx        796  0.0  0.0      0     0 pts/0    Z+   15:04   0:00 [wait] <defunct>#Z为僵尸进程，PCB未被回收
    tqx        798  0.0  0.0   4084  1988 pts/1    S+   15:04   0:00 grep --color=auto wait
    ```

    ###### 使用wait进行回收：

    ```c
    #include <sys/wait.h>
    //阻塞等待子进程结束，并回收它的PCB
    /**
    	wstatus: 子进程的退出状态。该整形包括2部分：
    		0~7位表示子进程是否正常退出成功
    		8~15位表示子进程的退出码。该退出码是exit或者main函数的return的返回值
    	return: 
    		-1：回收失败
    		>0: 子进程ID
    */
    pid_t wait(int *_Nullable wstatus);
    /**
    	pid: 
    		要回收的子进程ID，填写-1表示任意子进程。
    	wstatus: 
    		子进程回收状态，与wait函数参数相同。
    	options:
    		0: 阻塞等待，直到出现一个子进程退出
    		WNOHANG: 立即返回，即使没有子进程退出也不会阻塞。
    			当仍有子进程执行但是没有子进程退出时，返回值pid=0
    			当没有子进程时，返回值pid=-1
    	return:
    		>0 : 子进程的pid
    		=0 : 当options为WNOHANG，没有子进程退出时返回值为0，表示没有子进程退出。
    		=-1: 函数出错，errno被填充，或者子进程已经全部退出。
    		
    */
    pid_t waitpid(pid_t pid, int *_Nullable wstatus, int options);
    //status通过宏函数获取来获取子进程的退出状态。
    //1、正常退出
    WIFEXITED(wstatus) //子进程正常退出返回true
    WEXITSTATUS(wstatus) //获取子进程的返回值(exit、return的返回值)
    //2、通过信号：
    WIFSIGNALED(wstatus) //子进程通过信号终止的返回true
    WTERMSIG(wstatus) //返回终止子进程的信号的号码,当且仅当WIFSIGNALED返回值为true时使用
    ```

    DEMO:

    ```c
    #include <unistd.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    
    int main(){
            pid_t pid;
            if((pid = fork()) <0)
                    perror("");
            else if(pid == 0){
                    printf("子进程: %d 执行...\n",getpid());
                    sleep(2);
                    exit(2);
            }else{
                    int status;
                    pid_t cid;
                    while(1){
                            printf("父进程正在执行...\n");
                            if((cid = wait(&status)) >0){
                                    if(WIFEXITED(status))
                                            printf("子进程: %d 已被回收,status = %d\n",cid,WEXITSTATUS(status));
                            }
                            sleep(1);
                    }
            }
            return 0;
    }
    ```

    

12. 获取文件描述符的文件名：

    ```c
    #include <unistd.h>
    //根据文件描述符获取文件名称
    char *ttyname(int fd);
    ```

    DEMO:

    ```c
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(){
            char* stdin_name =  ttyname(0);
            fprintf(stdout,"标准输入的文件 = %s\n",stdin_name);
            char* stdout_name =  ttyname(1);
            fprintf(stdout,"标准输出的文件 = %s\n",stdout_name);
            char* stderr_name =  ttyname(2);
            fprintf(stdout,"标准错误的文件 = %s\n",stderr_name);
            return 0;
    }
    
    //结果：
    tqx@LAPTOP-G3KT1I3B$ ./ttyname
    标准输入的文件 = /dev/pts/0
    标准输出的文件 = /dev/pts/0
    标准错误的文件 = /dev/pts/0
    ```

    

13. 守护进程：

    ```c
    #include <sys/types.h>
    #include <unistd.h>
    //剥离当前进程与父进程的关系，创建一个新的会话，当前进程设置为组长
    /**return : 
    	-1 : 创建失败，失败号码保存在errno
    	非-1： 创建成功，返回值为新的会话id
    */
    pid_t setsid(void);
    ```

    DEMO(设置子进程为守护进程，创建日志文件，每隔5秒往日志文件中添加hello world):

    ```c
      1 #include <stdio.h>
      2 #include <stdlib.h>
      3 #include <unistd.h>
      4 #include <sys/types.h>
      5 #include <sys/stat.h>
      6 #include <fcntl.h>
      7
      8 int main(){
      9         //fork创建子进程
     10         pid_t pid;
     11         if((pid = fork()) < 0)
     12         {
     13                 perror("");
     14                 return -1;
     15         }
     16         //父进程退出
     17         if(pid)
     18                 return 0;
     19         //子进程创建会话
     20         setsid();
     21         //改变工作目录到根目录(可选)
     22         chdir("/");
     23         //关闭文件描述符(可选)
     24         close(0);
     25         close(1);
     26         close(2);
     27         //设置进程的掩码(可选)
     28         umask(0000);
     29         //设置执行任务
     30         //每5秒向日志文件中追加信息
     31         int fd = open("/home/tqx/linux-learn/deamon/deamon.log",O_CREAT | O_WRONLY | O_APPEND,0644);
     32         if(fd == -1){
     33                 perror("");
     34                 exit(-1);
     35         }
     36         char buf[] = "hello world\n";
     37         while(1){
     38                 write(fd,buf,sizeof(buf));
     39                 sleep(5);
     40         }
     41         return 0;
     42 }
    ```

    

14. vfork(写时复制fork):

    ```c
    #include <sys/types.h>
    #include <unistd.h>
    //创建子进程，使用copyOnWrite写时复制策略，一开始不会直接拷贝内存，而是先共用父进程的内存空间，子进程先执行，父进程阻塞
    //当子进程执行到exec(声明需要执行的shell命令)时才会进行拷贝,替换内存中的信息为需要执行exec指令的内容
    //或者子进程显式调用exit(),子进程退出。
    //以上两种情况出现后，父进程才会移动PC继续往下执行。
    pid_t vfork(void);
    ```

    DEMO(vfork之后调用exit):

    ```c
      1 #include <stdio.h>
      2 #include <stdlib.h>
      3 #include <sys/types.h>
      4 #include <unistd.h>
      5 //vfork的使用
      6 int main(){
      7         pid_t pid;
      8         int a = 20;
      9         if((pid = vfork()) == -1){	//vfork之后父进程阻塞在这里，PC指向第10行
     10                 perror("");
     11                 exit(-1);
     12         }else if(pid == 0){
     13                 fprintf(stdout,"这是子进程...\n");
     14                 a+=10;	//此时子进程还没有复制父进程内存空间，与父进程共用，所以执行后会改变父进程a的输出
     15                 sleep(2);
     16                 exit(0);	//子进程调用exit退出后，父进程再从vfork()代码的下一条语句开始执行
     17         }else {
     18                 printf("这是父进程...\n");
     19                 printf("a = %d\n",a);	//输出30
     20         }
     21         return 0;	//注意：子进程与父进程使用的是同一块栈区，所以子进程如果执行return，会弹栈并销毁，一定不要在父子进程同时使用该内存区域时触发return
     22 }
    ```

    DEMO(子进程通过exec函数族执行其他任务):

    ```c
      1 #include <stdio.h>
      2 #include <stdlib.h>
      3 #include <sys/types.h>
      4 #include <unistd.h>
      5 //vfork的使用
      6 int main(){
      7         pid_t pid;
      8         int a = 20;
      9         if((pid = vfork()) == -1){
     10                 perror("");
     11                 exit(-1);
     12         }else if(pid == 0){
     13                 fprintf(stdout,"这是子进程...\n");
     14                 a+=10;	//此时子进程还没有复制父进程内存空间，与父进程共用，所以执行后会改变父进程a的输出
     15                 execl("/bin/echo","echo","hello world","\n",(char* )NULL);	//子进程通过exec函数执行命令，这时会启动写时复制
     16                 //execlp("touch","touch","vfork.txt",(char*)NULL);
     17                 sleep(2);
     18                 perror("exec failed");
     19                 exit(-1);
     20         }else {
     21                 printf("这是父进程...\n");
     22                 printf("a = %d\n",a);
     23         }
     24         return 0;
     25 }
    ```

    

15. exec函数族：

16. 
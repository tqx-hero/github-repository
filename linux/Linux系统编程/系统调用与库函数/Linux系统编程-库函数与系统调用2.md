### Linux系统编程-库函数与系统调用2：

- #### 获取、设置环境变量getenv(3)、putenv(3):

  ```c
  #include <stdlib.h>
  /**
  	通过键name获取环境变量的值。
  	name：环境变量的key
  	return:
  		成功：返回环境变量的值。
  		失败：NULL
  */
  char *getenv(const char *name);
  //GNU扩展
  char *secure_getenv(const char *name);
  /**
  	修改、添加环境变量
  	string: 以键值形式将字符串放到环境变量，形式如下：
  		name=value
  		如果name存在，则会修改它的value；
  		如果name不存在，将该项添加到环境变量。
  	return:
  		0:成功
  		-1:失败，errno：
  		ENOMEM：内存不足
  */
  int putenv(char *string);
  ```

  demo:

  ```c
  #include <stdlib.h>
  #include <stdio.h>
  //getenv、setenv
  int main(){
          printf("PWD = %s\n",getenv("PWD"));
          printf("myname = %s\n",getenv("myname"));
          putenv("myname=tqx");
          printf("myname = %s\n",getenv("myname"));
          return 0;
  }
  ```

  输出结果：

  ```bash
  $./a.out
  PWD = /home/tqx/linux-learn/system_call/Linux_program/page4
  myname = (null)
  myname = tqx
  ```

  如果在启动时给/bin/bash设置了环境变量，启动的进程里就可以直接回去该变量值：

  ```bash
  $ myname=abc ./env #在启动时给启动进程设置环境变量
  PWD = /home/tqx/linux-learn/system_call/Linux_program/page4
  myname = abc #进程内部可以直接获取这个环境变量
  myname = tqx
  ```

  

- #### 获取所有环境变量environ:

  ```c
  #include <stdlib.h>
  extern char **environ;
  ```

  environ是一个字符串数组，包含了所有环境变量，每个字符串都是一个"name=value"的键值对形式。

  ###### 遍历环境变量：

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  extern char** environ;
  int main(){
          char** env = environ;
          while(*env){
                  printf("%s\n",*env);
                  env++;
          }
          return 0;
  }
  ```

  输出结果：

  ```bash
  $./a.out
  
  XDG_SESSION_ID=1604
  XDG_RUNTIME_DIR=/run/user/1000
  SSH_CLIENT=192.168.1.24 48777 22
  XDG_DATA_DIRS=/usr/local/share:/usr/share:/var/lib/snapd/desktop
  PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/tqx/linux-learn/path
  DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
  SSH_TTY=/dev/pts/0
  OLDPWD=/home/tqx/linux-learn/system_call/Linux_program
  _=./environ
  ...
  ```

  

- #### 获取时间：

  ##### time(2):

  ```c
  #include <time.h>
  typedef long int time_t;
  //返回的是从纪元时间(Unix的纪元时间为1970-01-01 00-00-00)到当前时间所经历的秒数，返回值time_t为有符号long类型
  //tloc不为NULL，则会把返回值写到这个地址，为NULL则不会写入。
  time_t time(time_t *tloc);
  ```

  demo:

  ```c
  #include <time.h>
  #include <stdio.h>
  //time()的用法
  //返回的是从纪元时间(Unix的纪元时间为1970-01-01 00-00-00)到当前时间所经历的秒数
  int main(){
          time_t now;
          now = time(NULL);
          printf("%lu\n",now);
          return 0;
  }
  ```

  ##### difftime(3):

  计算两个time_t之间间隔的秒数，返回值为double

  ```c
  #include <time.h>
  //返回的是 time1 - time2的差
  double difftime(time_t time1, time_t time0);       
  ```

  在 POSIX 系统中，time_t 是一种算术类型。如果无需考虑减法运算可能出现的溢出问题，可以直接定义：

  \#define difftime(t1,t0) (double)(t1 - t0)

  ###### demo:

  ```c
  #include <unistd.h>
  #include <time.h>
  #include <stdio.h>
  #include <stdlib.h>
  //difftime的用法
  int main(){
          time_t t1,t2;
          t1 = time(NULL);
          sleep(2);
          t2 = time(NULL);
          printf("t1 - t2 = %.2g\n",difftime(t1,t2));
          printf("t2 - t1 = %.2g\n",difftime(t2,t1));
          return 0;
  }
  ```

  输出：

  ```bash
  ./difftime
  t1 - t2 = -2
  t2 - t1 = 2
  ```

  ##### 时间格式化(3)：

  ```c
  #include <time.h>
  /**
  	asctime () 函数将分解后的时间值 tm 转换为以空字符结尾的字符串，格式与 ctime () 相同。返回值指向一块静态分配的字符串，后续对任意日期和时间函数的调用都可能覆盖该字符串。asctime_r () 函数功能相同，但会将字符串存入用户提供的缓冲区，该缓冲区至少需要预留 26 字节空间。
  */
  char *asctime(const struct tm *tm);
  char *asctime_r(const struct tm *tm, char *buf);
  /**
  	调用 ctime(t) 等价于 asctime(localtime(t))。它将日历时间 t 转换为以空字符结尾的字符串，格式如下：
  "Wed Jun 30 21:49:08 1993\n"
  星期的缩写为："Sun"、"Mon"、"Tue"、"Wed"、"Thu"、"Fri"、"Sat"。月份的缩写为："Jan"、"Feb"、"Mar"、"Apr"、"May"、"Jun"、"Jul"、"Aug"、"Sep"、"Oct"、"Nov"、"Dec"。返回值指向一块静态分配的字符串，后续对任意日期时间函数的调用都可能覆盖该字符串。该函数还会使用当前时区信息设置外部变量 tzname、timezone 和 daylight（参见 tzset (3)）。可重入版本 ctime_r() 功能相同，但会将字符串存入用户提供的缓冲区，缓冲区至少需要 26 字节空间。该版本不会设置 tzname、timezone 和 daylight。
  */
  char *ctime(const time_t *timep);
  char *ctime_r(const time_t *timep, char *buf);
  /**
  	gmtime () 函数将日历时间 timep 转换为以协调世界时（UTC）表示的分解时间格式。当年份无法用整型存储时，该函数可能返回 NULL。其返回值指向一个静态分配的结构体，后续对任意日期时间函数的调用都可能覆盖该结构体中的数据。gmtime_r () 函数功能与之相同，但会将数据存入用户提供的结构体中。
  */
  struct tm *gmtime(const time_t *timep);
  struct tm *gmtime_r(const time_t *timep, struct tm *result);
  /**
  	localtime () 函数将日历时间 timep 转换为分解时间表示形式，该时间以用户指定的时区为基准。该函数的行为等同于调用 tzset (3)，并设置外部变量：tzname 存储当前时区相关信息；timezone 存储协调世界时（UTC）与本地标准时间的差值，单位为秒；若一年中部分时段适用夏令时规则，则 daylight 设为非零值。返回值指向一块静态分配的结构体，后续任意日期时间函数的调用都可能覆盖该结构体内容。localtime_r () 函数功能与之相同，但会将数据存入用户提供的结构体中，该函数无需设置 tzname、timezone 和 daylight。
  */
  struct tm *localtime(const time_t *timep);
  struct tm *localtime_r(const time_t *timep, struct tm *result);
  
  /**
  	mktime () 函数将以本地时间表示的分解时间结构体转换为日历时间表示形式。该函数会忽略调用者在 tm_wday 和 tm_yday 字段中提供的值。tm_isdst 字段指定的值用于告知 mktime ()，tm 结构体所提供的时间是否启用夏令时（DST）：正值表示启用夏令时；零表示未启用夏令时；负值则表示 mktime () 应当（利用时区信息与系统数据库）尝试判断指定时间是否启用夏令时。
  */
  time_t mktime(struct tm *tm);
  
  /**
  tm_sec 分钟后的秒数，通常范围为 0 至 59，但可达到 60，用于容纳闰秒。
  tm_min 小时后的分钟数，范围为 0 至 59。
  tm_hour 午夜过后的小时数，范围为 0 至 23。
  tm_mday 月份中的日期，范围为 1 至 31。
  tm_mon 自一月起的月份数，范围为 0 至 11。
  tm_year 自 1900 年起的年份数。
  tm_wday 自星期日起的天数，范围为 0 至 6。
  tm_yday 自 1 月 1 日起的天数，范围为 0 至 365。
  tm_isdst 标志位，用于指示所描述的时间是否启用夏令时。若启用夏令时值为正数，未启用则为 0，信息不可用时为负数。
  */
  struct tm {
      int tm_sec;    /* 秒（0-60） */
      int tm_min;    /* 分（0-59） */
      int tm_hour;   /* 时（0-23） */
      int tm_mday;   /* 月份中的日期（1-31） */
      int tm_mon;    /* 月份（0-11） */
      int tm_year;   /* 年份 - 1900 */
      int tm_wday;   /* 星期（0-6，星期日 = 0） */
      int tm_yday;   /* 一年中的第几天（0-365，1月1日 = 0） */
      int tm_isdst;  /* 夏令时标记 */
  };
  ```

  

- #### 临时文件temp(3)：

  生成一个全局唯一的临时文件名（tmpnam与mktemp都是线程不安全）：

  该函数不能保证原子性，多线程环境下可能会生成同样的文件名，导致错误出现，所以需要使用原子性的tmpfile(3)、mkstemp(3).

  ```c
  #include <stdio.h>
  #define L_tmpnam 20	//存放文件名缓冲区的最小大小，参数必须保证大于等于该值才能放得下文件名。
  /**
  	创建一个全局唯一的临时文件，返回它的绝对路径。
  	s： 
  		将生成的临时文件名(绝对路径)放到该地址。该缓冲区必须大于等于20，也就是L_tmpnam
  		若为NULL，则不会放入。
  	return：
  		非NULL：文件的绝对路径名。
  		NULL：无法生成临时文件。
  */
  char *tmpnam(char *s);
  //非标准扩展，可移植性差，但是线程安全
  char *tmpnam_r(char *s);
  
  /**
  	mktemp () 函数根据模板生成唯一的临时文件名。模板的最后六个字符必须为 XXXXXX，这部分会被替换为一串字符，以此保证文件名唯一。由于模板内容会被修改，它不能是字符串常量，而应声明为字符数组。
  	切勿使用 mktemp ()。部分实现遵循 4.3BSD 规范，会将 XXXXXX 替换为当前进程 ID 加单个字母，因此最多只能返回 26 个不同名称。一方面这类文件名容易被猜测，另一方面在检查文件是否存在与打开文件之间存在竞态条件，所以每次使用 mktemp () 都会带来安全风险。mkstemp (3) 和 mkdtemp (3) 可以规避该竞态问题。
  */
  #include <stdlib.h>
  char *mktemp(char *template);
  ```

  ###### demo:

  ```c
  #include <stdio.h>
  //tmpnam的用法
  int main(){
          printf("%s\n",tmpnam(NULL));
          char tmp_name[L_tmpnam];//L_tmpnam为20,缓冲区要不小于这个数
          printf("%s\n",tmpnam(tmp_name));
          printf("%s\n",tmp_name);
          return 0;
  }
  ```

  输出：

  ```bash
  $./tmpnam
  
  /tmp/fileTiakUm
  /tmp/fileYWWAOm
  /tmp/fileYWWAOm
  ```

  

- #### 生成临时文件并打开(3)：

  ```c
  #include <stdio.h>
  /**
  	直接生成临时文件，并打开返回文件流。该函数多线程安全。
  	该临时文件以读写方式打开(即调用fopen的w+方式)，当该文件所有引用全部关闭或者进程退出，内核会自动删除该文件。
  	return：
  		成功：返回文件流。
  		失败：返回NULL，填充errno。
  			EACCES： 文件路径前缀中的目录搜索权限被拒绝。
  			EEXIST： 无法生成唯一文件名。
  			EINTR： 该调用被信号中断；参见 signal (7)。
  			EMFILE： 已达到单个进程打开文件描述符数量的上限。
  			ENFILE： 已达到系统全局打开文件总数上限。
  			ENOSPC： 目录中没有剩余空间用于添加新文件名。
  			EROFS： 只读文件系统。
  */
  FILE *tmpfile(void);
  
  //指定模板的临时文件生成、打开，返回文件描述符。
  #include <stdlib.h>
  /**
  	模板的最后六个字符必须为 “XXXXXX”，这部分会被替换成一段字符串，用以保证文件名唯一。由于模板内容会被修改，模板不能是字符串常量，而应声明为字符数组。
  	创建的文件权限为 0600，即仅文件所有者拥有读写权限。
  	返回的文件描述符对该文件同时提供读、写访问权限。文件通过 open (2) 的 O_EXCL 标志打开，确保调用进程是创建该文件的进程。
  	template:
  		文件生成模板字符串，该字符串必须是可修改的字符串，所以它必须是一个数组，而不是字符串字面量。
  	return:
  		成功：非负文件描述符。
  		失败：-1，填充errno。
  			1、EEXIST： 无法创建唯一的临时文件名。此时模板的内容未定义。
  			2、EINVAL： 对于 mkstemp () 和 mkostemp ()：模板的最后六个字符不是 XXXXXX；模板保持不变。对于 mkstemps () 和 mkostemps ()：模板长度小于（6 + 后缀长度）个字符，或者模板中后缀之前的最后 6 个字符不是 XXXXXX。
  			3、这些函数也可能出现 open (2) 中描述的任意错误。
  */
  int mkstemp(char *template);
  /**
  	mkostemp () 函数类似 mkstemp ()，区别在于可以在 flags 参数中指定下列标志位（含义同 open (2)）：O_APPEND、O_CLOEXEC 和 O_SYNC。请注意，创建文件时，mkostemp () 会在传递给 open (2) 的 flags 参数中自动包含 O_RDWR、O_CREAT 和 O_EXCL；无需在传给 mkostemp () 的 flags 参数里设置这几个标志，在部分系统上这样做还会引发错误。
  */
  int mkostemp(char *template, int flags);
  /**
  	mkstemps () 函数类似于 mkstemp ()，区别在于模板字符串中包含长度为 suffixlen 个字符的后缀。因此，模板的形式为前缀 XXXXXX 后缀，字符串 XXXXXX 会像 mkstemp () 中那样被修改。
  */
  int mkstemps(char *template, int suffixlen);
  //mkostemps () 函数相对于 mkstemps () 的关系，等同于 mkostemp () 相对于 mkstemp () 的关系。
  int mkostemps(char *template, int suffixlen, int flags);
  
  //临时目录的创建：
  /**
  	mkdtemp () 函数根据模板生成一个具有唯一名称的临时目录。模板的最后六个字符必须是 XXXXXX，这部分会被一段字符串替换，以此保证目录名称唯一。随后该目录会以权限 0700 创建。由于模板会被修改，因此它不能是字符串常量，而应声明为字符数组。
  */
  #include <stdlib.h>
  char *mkdtemp(char *template);
  ```

  ###### demo1：使用tmpfile(3)生成临时文件。

  ```c
  #include <stdio.h>
  #include <unistd.h>
  //tmpfile()函数的用法
  int main(){
          FILE* file;
          if(!(file = tmpfile())){
                  perror("create tempfile error");
                  return -1;
          }
          printf("创建临时文件成功\n");
          fclose(file); //可选择关闭，如果进程退出也会自动回收该临时文件，所以flose为可选
          return 0;
  }
  ```

  ###### demo2：使用mkstemp(3)生成临时文件。

  ```c
  #include <stdlib.h>
  #include <stdio.h>
  //mkstemp()函数的用法
  int main(){
          int fd;
      	//该字符串必须有可修改的缓冲区,并且文件名必须以'XXXXXX'结尾，在生成临时文件时，会对这个缓冲区的后六个X进行修改
          char template[] ="helloworld_XXXXXX";
          if((fd = mkstemp(template)) == -1){
                  perror("make temp file error");
                  exit(EXIT_FAILURE);
          }
          printf("生成临时文件成功，文件名 = %s\n",template);
          return 0;
  }
  ```

  输出：

  ```bash
  $./mkstemp
  
  生成临时文件成功，文件名 = helloworld_AwgefF #文件名后六位被修改了
  ```

  至于其他版本的mk*temp(3)函数就不一一列举了，无非是对fd的权限、文件名等属性的修改版本，有需要可参考API或者Linux文档。

- #### 获取用户ID(2)：

  ```c
  #include <unistd.h>
  #include <sys/types.h>
  typedef unsigned int uid_t;	//在更早版本时，该类型为16位整型
  //getuid () 返回调用进程的真实用户 ID。
  uid_t getuid(void);
  //geteuid () 返回调用进程的有效用户 ID
  uid_t geteuid(void);
  
  int setuid(uid_t uid);
  
  #include <unistd.h>
  //获取用户的登录名
  char *getlogin(void);
  ```

  ###### demo:

  获取用户真实ID、用户有效ID：(正常情况下这俩相同，除非调用了setuid进行修改)

  ```c
  #include <unistd.h>
  #include <sys/types.h>
  #include <stdio.h>
  //getuid/geteuid
  int main(){
  
          printf("uid = %u\n",getuid());
          printf("uid = %u\n",geteuid());
          return 0;
  }
  ```

  获取用户名称：

  ```c
  #include <unistd.h>
  #include <stdio.h>
  //getuid/geteuid
  int main(){
          printf("login name = %s\n",getlogin());
          return 0;
  }
  ```

  

- #### 获取用户信息(3)：

  所有用户信息都存储在本地数据库文件：/etc/passwd中，可通过下面的接口获取相关用户的信息。

  ```c
  #include <sys/types.h>
  #include <pwd.h>
  typedef unsigned int gid_t;
  /**
  	getpwnam () 函数返回一个指向结构体的指针，该结构体包含密码数据库（例如本地密码文件 /etc/passwd、NIS 以及 LDAP）中与用户名 name 匹配的记录的各个拆分字段
  	name: 用户名
  	return:
  		成功：返回用户信息的地址。
  		失败：NULL，并填充errno
  */
  struct passwd *getpwnam(const char *name);
  /**
  	getpwuid () 函数返回一个指向结构体的指针，该结构体包含密码数据库中与用户 ID uid 匹配的记录的各个拆分字段。
  	uid：用户ID
  	return:
  		成功：返回用户信息的地址。
  		失败：NULL，并填充errno
  */
  struct passwd *getpwuid(uid_t uid);
  
  struct passwd {
      char   *pw_name;       /* username */
      char   *pw_passwd;     /* user password */
      uid_t   pw_uid;        /* user ID */
      gid_t   pw_gid;        /* group ID */
      char   *pw_gecos;      /* user information */
      char   *pw_dir;        /* 用户家目录 */
      char   *pw_shell;      /* 用户默认的shell */
  };
  ```

  demo:

  ```c
  #include <sys/types.h>
  #include <pwd.h>
  #include <stdio.h>
  #include <unistd.h>
  //获取用户信息
  int main(){
          struct passwd* userinfo;
          userinfo =  getpwuid(getuid());//通过用户ID获取
          printf("username = %s,passwd = %s,user ID = %u, group ID = %u,userinfo = %s,home dir = %s,shell = %s\n",
                  userinfo->pw_name,userinfo->pw_passwd,userinfo->pw_uid,userinfo->pw_gid,userinfo->pw_gecos,
                  userinfo->pw_dir,userinfo->pw_shell);
          userinfo = getpwnam(getlogin());//通过登录名获取
          printf("username = %s,passwd = %s,user ID = %u, group ID = %u,userinfo = %s,home dir = %s,shell = %s\n",
                  userinfo->pw_name,userinfo->pw_passwd,userinfo->pw_uid,userinfo->pw_gid,userinfo->pw_gecos,
                  userinfo->pw_dir,userinfo->pw_shell);
          return 0;
  }
  ```

  输出结果：

  ```bash
  $./getuserinfo
  #返回结果两者相同
  username = tqx,passwd = x,user ID = 1000, group ID = 1000,userinfo = linux0.11,,,,home dir = /home/tqx,shell = /bin/bash
  
  username = tqx,passwd = x,user ID = 1000, group ID = 1000,userinfo = linux0.11,,,,home dir = /home/tqx,shell = /bin/bash
  ```

  

- #### 遍历/proc/passwd文件，获取所有用户的信息：

  与上一个获取单个用户信息项不同，下面的函数可以获取文件下所有记录的用户信息：

  ```c
  #include <sys/types.h>
  #include <pwd.h>
  /**
  	读取当前指针所在的信息，返回信息结构体地址。
  	读取后，读取指针会自动后移，到文件末尾后，返回NULL。
  */
  struct passwd *getpwent(void);
  //将读取文件的指针重置到文件开头
  void setpwent(void);
  //endpwent () 函数用于完成所有处理后关闭密码数据库
  void endpwent(void);
  ```

  ###### demo：输出当前用户的信息，其他用户跳过

  ```c
  #include <unistd.h>
  #include <sys/types.h>
  #include <pwd.h>
  #include <stdio.h>
  #include <string.h>
  //getpwent()用法
  int main(){
          const char * username = getlogin();
           struct passwd* userinfo;
           while((userinfo = getpwent())){
                  if(strcmp(userinfo->pw_name,username)) //不是当前用户,跳过
                          continue;
                  printf("username = %s,passwd = %s,user ID = %u, group ID = %u,userinfo = %s,home dir = %s,shell = %s\n",
                          userinfo->pw_name,userinfo->pw_passwd,userinfo->pw_uid,userinfo->pw_gid,userinfo->pw_gecos,
                          userinfo->pw_dir,userinfo->pw_shell);
                  break;
           }
          endpwent();//关闭文件流
          return 0;
  }
  ```

  输出：

  ```bash
  $ ./getpwent
  
  username = tqx,passwd = x,user ID = 1000, group ID = 1000,userinfo = linux0.11,,,,home dir = /home/tqx,shell = /bin/bash
  ```

  

- #### 获取主机信息(2)：

  ```c
  #include <sys/utsname.h>
  //获取主机信息，结果输出到buf
  //成功：0，失败：-1，填充errno
  int uname(struct utsname *buf);
  
  struct utsname {
      char sysname[];    /* 操作系统名 (例如："Linux") */
      char nodename[];   /* 主机名 */
      char release[];    /* 系统发行级别 (e.g., "2.6.28") */
      char version[];    /* 发行版本 */
      char machine[];    /* 硬件类型 */
      #ifdef _GNU_SOURCE 
      char domainname[]; /* 域名，当定义了_GNU_SOURCE时可获得 */
      #endif
  };
  ```

  ###### demo:

  ```c
  #define _GNU_SOURCE	//只有定义了该宏才能解锁域名字段
  #include <sys/utsname.h>
  #include <stdio.h>
  //uname()用法
  int main(){
          struct utsname name;
          if(uname(&name)){
                  perror("uname error");
                  return -1;
          }
          printf("sysname = %s,nodename = %s,release = %s,version = %s,hardware = %s,domainname = %s\n",
                  name.sysname,name.nodename,name.release,name.version,name.machine,name.domainname);
          return 0;
  }
  ```

  

- #### 获取网络名gethostname(2)：

  ```c
  #include <unistd.h>
  /**
  	获取主机的网络名称，将结果拷贝到name指向的缓冲区，该缓冲区的大小为len
  	name:
  		保存网络名的缓冲区地址。
  	len：
  		缓冲区大小
  	return：
  		成功：0
  		失败：-1,填充errno。
  */
  int gethostname(char *name, size_t len);
  //设置网络名，返回值同上
  int sethostname(const char *name, size_t len);
  ```

  ###### demo：

  ```c
  #include <unistd.h>
  #include <stdio.h>
  //gethostname(2)的使用
  int main(){
          char name[20];
          if(gethostname(name,sizeof(name))){
                  perror("gethostname error");
                  return -1;
          }
          printf("hostname = %s\n",name);
          return 0;
  }
  ```

  

- #### 获取主机的ID(3)：

  该ID为厂家写入ROM的主机唯一标识。

  ```c
  #include <unistd.h>
  /**
  	gethostid() 和 sethostid() 分别用于获取或设置当前主机唯一的32位标识符。该32位标识符旨在在所有现存UNIX系统中保持唯一。该标识符通常与gethostbyname(3)返回的本机互联网地址类似，因此一般无需手动设置。
  */
  long gethostid(void);
  int sethostid(long hostid);
  ```

  ###### demo:

  ```c
  #include <unistd.h>
  #include <stdio.h>
  //gethostid(2)
  int main(){
          long hostid = gethostid();
          char* idp = (char*) &hostid;//转成网络字节序，以十六进制输出
          printf("host ID = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
                  idp[7] & 0xFF,idp[6] & 0xFF,idp[5] & 0xFF,idp[4] & 0xFF,idp[3] & 0xFF,idp[2] & 0xFF,idp[1] & 0xFF,idp[0] & 0xFF);
          return 0;
  }
  ```

  输出：

  ```bash
  $./gethostid
  
  host ID = ff:ff:ff:ff:f2:ac:0f:f8
  ```

  

- #### 添加系统日志syslog(3)：

  

  ```c
  #include <syslog.h>
  /**
  	openlog() 为程序打开一条通往系统日志记录器的连接。该函数对于syslog(3)是可选的，即不调用openlog(),syslog()也能正常选取默认值工作。
  	
  option 参数用于。facility 参数。option 和 facility 可设置的取值将在下文说明。
  
  openlog() 是可选调用；必要时 syslog() 会自动调用它，这种情况下 ident 默认为 NULL。
  	ident：
  		指向的字符串会被添加到每条消息的开头，通常设置为程序名称。如果 ident 为 NULL，则使用程序名。（POSIX.1-2008 未规定 ident 为 NULL 时的行为。）
  	option：指定标志，控制 openlog() 以及后续 syslog() 调用的行为，它是一个位掩码，由下列任意值按位或组合而成：
  			LOG_CONS：向系统日志守护进程发送消息出错时，直接写入系统控制台。
  			LOG_NDELAY：立即打开连接（默认行为是记录第一条日志消息时才建立连接）。
  				例如，如果后续会执行 chroot(2) 导致日志模块内部使用的路径无法访问，该选项会很有用。
  			LOG_ODELAY：与 LOG_NDELAY 相反；延迟建立连接，直到调用 syslog() 时才打开连接。
  				（此为默认行为，无需显式指定。）
  			LOG_NOWAIT：记录日志消息时，若创建了子进程，则不等待这些子进程。（GNU C 库不会创建子进程，因此该选项在 Linux 上无效。）
  			LOG_PERROR：（POSIX.1-2001、POSIX.1-2008 标准未定义。）同时将消息输出到标准错误流 stderr。
  			LOG_PID：每条日志消息中都带上调用进程的进程ID（PID）。
  			
  	facility：设定默认设施类型(就是进程类型)，若后续调用 syslog() 时未指定设施，则使用该默认值。
  	用于指定是哪类程序在记录日志消息。借此，配置文件可以规定，来自不同设施的消息将以不同方式处理。
  		LOG_AUTH：       安全/授权相关消息
  		LOG_AUTHPRIV：   安全/授权相关消息（私密）
  		LOG_CRON：       时钟守护进程（cron 和 at）
  		LOG_DAEMON：     无独立设施值的系统守护进程
  		LOG_FTP:        FTP守护进程
  		LOG_KERN:       内核消息（用户进程无法生成这类消息）
  		LOG_LOCAL0 至 LOG_LOCAL7:保留给本地使用
  		LOG_LPR:        行式打印机子系统
  		LOG_MAIL:       邮件子系统
  		LOG_NEWS:       USENET新闻子系统
  		LOG_SYSLOG:     syslogd(8)自身内部产生的消息
  		LOG_USER:（默认值）通用用户级消息
  		LOG_UUCP:       UUCP子系统
  */
  void openlog(const char *ident, int option, int facility);
  /**
  	syslog() 生成一条日志消息，由 syslogd(8) 分发。
  	
  	priority: 由设施值与级别值（下文描述）做按位或运算组合而成。(例如：LOG_USER | LOG_DEBUG)
  		其中低3位代表的是级别值。
  		高 28 位为设施值（0 至一个较大数值）
  		如果没有将设施值或入 priority，则使用 openlog() 设置的默认值；
  		若此前没有调用过 openlog()，则默认采用 LOG_USER。		
  		级别值按重要性从高到低排列如下(括号内为该宏代表的实际值)：
  			LOG_EMERG(=0): 紧急情况，系统不可用
  			LOG_ALERT(=1): 高优先级故障，比如数据库崩溃，必须立即采取处理动作
  			LOG_CRIT(=2)： 严重故障状态，比如硬件故障
  			LOG_ERR(=3)：        错误状态
  			LOG_WARNING(=4)：    警告状态
  			LOG_NOTICE(=5)：     正常但值得关注的状态
  			LOG_INFO(=6)：       提示类信息
  			LOG_DEBUG(=7)：      调试级信息
  		函数 setlogmask(3) 可用于限制日志，仅记录指定等级的日志。
  	
  	format：
  		其余参数为格式字符串（用法同 printf(3)）以及该格式所需的各项参数，区别在于双字符序列 %m 会被错误信息字符串 strerror(errno) 替换。格式字符串末尾不必包含换行符。
  */
  void syslog(int priority, const char *format, ...);
  //closelog() 会关闭用于写入系统日志的文件描述符。closelog() 的调用是可选的。
  void closelog(void);
  /**
  	进程拥有日志优先级掩码，该掩码决定哪些对 syslog (3) 的调用可以被记录日志。
  	其余所有调用都会被忽略。
  	掩码中对应位被置位的优先级，其日志记录功能开启。
  	初始掩码会开启所有优先级的日志记录。初始掩码为 255
  	setlogmask () 函数为调用进程设置该日志掩码，并返回之前的掩码。
  	mask：
  		要设置的掩码。若 mask 参数为 0，则当前日志掩码不会被修改。
  		共有八个优先级：LOG_EMERG、LOG_ALERT、LOG_CRIT、LOG_ERR、LOG_WARNING、LOG_NOTICE、LOG_INFO 和 LOG_DEBUG。		
  		优先级 p 对应的位由 LOG_MASK (p) 表示。部分系统还提供宏 LOG_UPTO (p)，用于生成上述列表中从最高优先级一直到 p（包含 p）在内所有优先级对应的掩码。
  		
  	return：返回覆盖之前的掩码。
  	
  */
  int setlogmask(int mask);
  
  //下面2个宏函数可作为setlogmask(3)的参数
  #define LOG_MASK(pri)   (1 << (pri))            /* 获取优先级 = pri的掩码 */
  #define LOG_UPTO(pri)   ((1 << ((pri)+1)) - 1)  /* 获取所有优先级大于等于pri掩码 */
  
  //函数 vsyslog() 的功能与 syslog() 相同，区别在于它接收通过 stdarg(3) 可变参数列表宏获取的一组参数。
  void vsyslog(int priority, const char *format, va_list ap);
  ```

  ###### demo：直接使用syslog

  ```c
  #include <syslog.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <fcntl.h>
  #define PRO_NAME "mysyslog"
  //syslog()的使用
  int main(){
          //1、直接使用syslog(3)
          /*
          if(open("./name12.txt",O_RDONLY)){
                  syslog(LOG_ERR | LOG_USER,"open file \"./name12.txt\" error : %m");
                  return -1;
          }
          */
  
          //2、使用openlog(3)，给日志输出进行适当配置
          /*
          openlog(PRO_NAME,LOG_PID | LOG_CONS,LOG_USER);
          if(open("./name12.txt",O_RDONLY)){
                  syslog(LOG_ERR | LOG_USER,"open file \"./name12.txt\" error : %m");
                  return -1;
          }
          */
  
          //3、设置了日志掩码
          openlog(PRO_NAME,LOG_PID | LOG_CONS,LOG_USER);
          int oldmask = setlogmask(LOG_UPTO(LOG_ERR));
          printf("原掩码 = %d\n",oldmask);//默认初始掩码为 255
          if(open("./name12.txt",O_RDONLY)){
                  syslog(LOG_ERR | LOG_USER,"open file \"./name12.txt\" [level: LOG_ERR] : %m");
                  syslog(LOG_WARNING | LOG_USER,"open file \"./name12.txt\" [level: LOG_WARNING] : %m");
                  return -1;
          }
          return 0;
  }
  ```

  1、使用第一种情况时的输出(直接使用syslog)：

  ```bash
  $ tail -f /var/log/syslog
  #输出格式为： 程序名称: 日志内容。
  Oct 20 01:08:28 linux-ubuntu syslog: open file "./name12.txt" error : No such file or directory
  Oct 20 01:16:27 linux-ubuntu syslog: open file "./name12.txt" error : No such file or directory
  ```

  2、使用第二种情况(使用openlog设置了日志开头的字符串为mysyslog)：

  ```bash
  $ tail -f /var/log/syslog
  #日志开头变成了 mysyslog,同时添加了进程号
  Oct 20 01:48:45 linux-ubuntu mysyslog[171449]: open file "./name12.txt" error : No such file or directory
  ```

  3、使用第三种情况(通过setlogmask函数设置日志掩码，只记录优先级LOG_ERR以上的日志)：

  ```bash
  $ tail -f /var/log/syslog
  #设置掩码后，只记录了LOG_ERR等级的，LOG_WARNING等级的没记录
  Oct 20 02:19:10 linux-ubuntu mysyslog[171539]: open file "./name12.txt" [level: LOG_ERR] : No such file or directory
  ```

  

- 
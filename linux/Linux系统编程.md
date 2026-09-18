1. 文件打开/关闭：

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

   

2. 写入文件：

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

   

3. 读取文件：

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

   

4. 
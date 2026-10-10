#### mmap:

##### 建立磁盘上的文件与内存段之间的关系，将文件中相关的数据以页的形式加载到进程的逻辑地址空间，让用户通过操作这个内存段来操作文件。

##### 内核层面会对文件进行不同策略的同步，减少I/O次数，增加CPU的利用率。

```c
#include <sys/mman.h>
/**
	将磁盘文件的一段地址空间映射到内存相应的一块区域，后续对内存这段区域进行操作，会以合适的时机同步到磁盘，减少磁盘IO次数。
	addr: 要映射到的内存地址。填入NULL，内核会自动找一合适的内存区域进行映射(由于每个机器上内存排布不同，使用固定的addr可移植性差，所以推荐NULL)。
	length: 内存地址的大小，也是要映射出的磁盘文件的字节数。该字段必须大于0字节。
	prot: 设置内存的访问权限。可使用如下权限按位或运算。
		PROT_EXEC: 允许执行该内存段。
		PROT_READ: 允许读取内存段。
		PROT_WRITE: 允许写入内存段。
		PROT_NONE: 内存段不允许访问。
	flags: 对该内存映射的修改是否对其他映射同一区域的进程可见；以及修改是否会同步到底层文件。该行为由 flags必须且只能设置下面其中一个标志位来决定：
		MAP_SHARED: 共享映射。对映射做出的修改会同步磁盘文件，并且其他进程都会看见所做的修改。
					如果需要精确控制何时将修改刷到底层文件，需要调用 `msync(2)`。
		MAP_PRIVATE: 内存段私有，写时复制。当前进程对内存段进行的修改对其他映射同一文件区域的进程不可见，
					 仅修改留在进程私有页，不会写到磁盘。
					 注意：如果其他进程对文件这段区域进行了修改，POSIX标准没有限定这个修改会不会同步到该进程内存段，所以这个选项不可控。
		MAP_FIXED: 该内存段必须位于指定的addr地址处。
	fd：要映射的磁盘文件的文件描述符。fd在执行完成该函数后就可以关闭，不影响映射关系。
		还要注意，空文件大小为0时，不能进行mmap映射(length大于0，无法映射空文件)，可以使用truncate(2)来重新设置文件大小。
	offset: 映射的磁盘文件fd的起始偏移量。
			文件映射是从文件描述符 `fd` 所指向的文件（或其他对象）内，**以偏移量 offset 为起点读取 length 个字节来初始化的**。
			该字段必须是页大小的整数倍(内存对齐)。
			页大小的值可通过 `sysconf(_SC_PAGE_SIZE)` 获取。
	return:
		void* : 
			成功： 返回内存段的起始地址。
			失败： 返回MAP_FAILED( = void(*)-1),errno被填充。
*/
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
/**
	释放映射到的内存段
	addr: 内存段地址
	length： 内存段长度。
	return：
		0：释放成功
		-1：释放失败，errno错误码。
*/
int munmap(void *addr, size_t length);
/**
	将内存段中的修改刷新到映射文件。
	本调用只会更新与 `addr` 起始、长度为 `length` 的这片内存区域相对应的那一部分文件内容。
	addr: 内存区域地址
	length: 要刷新的字节数
	flags:
		参数**必须二选一指定 MS_ASYNC 或者 MS_SYNC**；在此基础之上还可以额外或上 `MS_INVALIDATE`标志位
		MS_ASYNC: 异步写入文件。不阻塞直接返回。
		MS_SYNC: 同步写入文件。阻塞等待IO完成才会返回。
		MS_INVALIDATE： 请求作废同一个文件的其他进程内的内存映射副本；这样其他进程的映射就可以获取刚刚写入的最新数据。
	return:
		0：释放成功
		-1：释放失败，errno错误码。
*/
int msync(void *addr, size_t length, int flags);
#define MAP_FAILED  ((void *) -1)
```

###### demo:

###### mmap简单获取test.txt文件的前16个字节：

```c
  1 #include <sys/mman.h>
  2 #include <unistd.h>
  3 #include <stdio.h>
  4 #include <stdlib.h>
  5 #include <fcntl.h>
  6 #include <string.h>
  7 #define MMAP_BUF_SIZE 16
  8 //mmap()文件映射初体验
  9 int main(){
 10         int fd;
 11         if((fd = open("./test.txt",O_CREAT | O_APPEND | O_RDWR,0644)) == -1){
 12                 perror("open file error");
 13                 exit(-1);
 14         }
 15         printf("页大小 = %ld\n",sysconf(_SC_PAGE_SIZE));
 16         char* buf = mmap(NULL,MMAP_BUF_SIZE,PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
 17         if(buf == MAP_FAILED){
 18                 perror("mmap error");
 19                 exit(-1);
 20         }
 21         char msg_buf[MMAP_BUF_SIZE];
 22         memcpy(msg_buf,buf,MMAP_BUF_SIZE);
 23         msg_buf[MMAP_BUF_SIZE] = '\0';
 24         fprintf(stdout,"该文件内容: %s\n",msg_buf);
 25         if(munmap(buf,MMAP_BUF_SIZE) == -1)
 26                 perror("munmap error");
 27         close(fd);
 28         return 0;
 29 }
```

###### 将test.txt文件的前几个字符改成helloworld:

```c
  1 #include <sys/mman.h>
  2 #include <unistd.h>
  3 #include <stdio.h>
  4 #include <stdlib.h>
  5 #include <fcntl.h>
  6 #include <string.h>
  7 #define MMAP_BUF_SIZE 16
  8 //mmap()修改文件
  9 int main(){
 10         int fd;
 11         if((fd = open("./test.txt",O_CREAT | O_APPEND | O_RDWR,0644)) == -1){
 12                 perror("open file error");
 13                 exit(-1);
 14         }
 15         printf("页大小 = %ld\n",sysconf(_SC_PAGE_SIZE));
 16         char* buf = mmap(NULL,MMAP_BUF_SIZE,PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
 17         if(buf == MAP_FAILED){
 18                 perror("mmap error");
 19                 exit(-1);
 20         }
 21         char msg_buf[]="hello world";
 22         memcpy(buf,msg_buf,sizeof(msg_buf)); //操作内存块buf = 操作文件
 23         if(munmap(buf,MMAP_BUF_SIZE) == -1)
 24                 perror("munmap error");
 25         close(fd);
 26         return 0;
 27 }
```

###### 同步刷新：

```c
  1 #include <sys/mman.h>
  2 #include <unistd.h>
  3 #include <stdio.h>
  4 #include <stdlib.h>
  5 #include <fcntl.h>
  6 #include <string.h>
  7 #define MMAP_BUF_SIZE 16
  8 //使用msync()主动刷新到文件
  9 int main(){
 10         int fd;
 11         if((fd = open("./test.txt",O_CREAT | O_APPEND | O_RDWR,0644)) == -1){
 12                 perror("open file error");
 13                 exit(-1);
 14         }
 15         char* buf = mmap(NULL,MMAP_BUF_SIZE,PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
 16         close(fd);	//关闭fd
 17         if(buf == MAP_FAILED){
 18                 perror("mmap error");
 19                 exit(-1);
 20         }
 21         int cnt =1;
 22         cnt++;
 23         char msg_buf[]="hello world";
 24         memcpy(buf,msg_buf,sizeof(msg_buf)-1);
 25         if(msync(buf,sizeof(msg_buf)-1,MS_SYNC | MS_INVALIDATE) == -1)	//同步刷新到文件，并使其他映射该块文件区域的内容无效。
 26                 perror("msync error");
 27         if(munmap(buf,MMAP_BUF_SIZE) == -1)
 28                 perror("munmap error");
 29         return 0;
 30 }
```


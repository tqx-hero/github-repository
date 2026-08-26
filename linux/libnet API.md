# libnet API(组包工具) : #include <libnet.h>

1. 创建libnet实例，返回libnet上下文：

   ```c
   /*
   	1、injection_type：包的注入类型：决定libnet在哪一层发包、打开什么套接字，具体有7个宏，在下面详细展开。
   	2、device：设备名称，可以为NULL，此时libnet会自己选一个网卡
   	3、err_buf:加载失败时存储失败信息。
   	返回值：NULL为失败；
   		 成功则返回有效的上下文。
   */
    char err_buf[LIBNET_ERRBUF_SIZE];
   libnet_t * libnet_init (int injection_type, const char *device, char *err_buf);
   #injection_type注入类型宏如下：
   	LIBNET_LINK： 数据链路层普通模式。
           底层打开 Linux 的`PF_PACKET`套接字，直接操作以太网帧
           1、必须自己构造以太网帧头(libnet_build_ethernet())
           2、可调用libnet_get_ipaddr4()、libnet_get_hwaddr()获取IP地址与MAC地址。
           3、完全自定义MAC，可以伪造二层帧。
           4、需要root权限。
   	LIBNET_LINK_ADV：数据链路层高级模式。
           同样是 PF_PACKET 链路层发包，和 LINK 行为一致。
           改进：
           	高级模式使用新的packet-block内存管理，更稳定，内存泄漏与bug更少。
       LIBNET_RAW4：IPV4原始套接字。
           底层打开`SOCK_RAW`（IP 层原始套接字）
           1、内核自动生成数据链路层的头部(以太网帧头)，用户只需要自己构造IPV4与上层的包。
           2、同样需要root权限。
           3、可以伪造IP。
       LIBNET_RAW4_ADV：IPV4原始套接字高级模式。
           与LIBNET_RAW4相同语义。只是使用了packet-block内存管理。
       LIBNET_RAW6：IPV6原始套接字。
           1、构造 IPv6 头部，内核处理二层以太网帧。
           2、IPv6 原始套接字有些系统限制，不能随意伪造源地址。
       LIBNET_RAW6_ADV:IPV6原始套接字高级模式。
           LIBNET_RAW的高级内存版本。
       LIBNET_NONE：不注入，仅内存组包，不发送。
           **不打开任何套接字，不能发送报文**。
           只做一件事：在内存组装数据包，把组装好的报文拿出来，交给自己的 socket 发送。
   		用法场景：用 libnet 做报文构造，但是自己调用 sendto 发送，不走 libnet_write。
   //组包顺序：libnet要求从高层到底层进行组包
           传输层->网络层->数据链路层
   ```

   

2. struct libnet_ether_addr:

   ```c
   //以太网MAC地址结构体
   struct libnet_ether_addr
   {
       uint8_t  ether_addr_octet[6];        /* Ethernet address */
   };
   ```

   

3. libnet_get_ipaddr4:

   ```c
   //根据上下文获取ipv4地址(大端序)
   /*
   	l:libnet上下文。
   	return：
   		-1：获取失败，可通过libnet_geterror(libnet_t *)获取失败信息。
   			注意：返回值为无符号数，所以-1应该将其解释成0xffffffff,或者直接使用(uint32_t)(-1)强转
   		成功返回一个有效的ip地址。
   */
   uint32_t libnet_get_ipaddr4 (libnet_t *l);
   ```

   

4. libnet_get_hwaddr:

   ```c
   //根据上下文获取网卡的硬件地址。
   //struct libnet_ether_addr结构体参看该文档第2项
   /*
   	l:libnet上下文。
   	return：
   		NULL：获取失败，可通过libnet_geterror(libnet_t *)获取失败信息。
   		成功返回一个非空指针。
   */
   struct libnet_ether_addr * libnet_get_hwaddr (libnet_t *l);
   ```

   

5. libnet_geterror:

   ```c
   //根据上下文获取错误信息。
   //当调用libnet_*函数时如果出现错误，错误信息会存储在libnet_t结构体内
   char * libnet_geterror (libnet_t *l);
   ```

   

6. libnet_t结构体：

   ```c
   //libnet_t上下文
   struct libnet_context
   {
   #if ((_WIN32) && !(__CYGWIN__)) 
       SOCKET fd;
       LPADAPTER  lpAdapter;
   #else
       int fd;                             /* file descriptor of packet device */
   #endif
       int injection_type;                 /* one of: */
   #define LIBNET_NONE     0xf8            /* no injection type, only construct packets */
   #define LIBNET_LINK     0x00            /* link-layer interface */
   #define LIBNET_RAW4     0x01            /* raw socket interface (ipv4) */
   #define LIBNET_RAW6     0x02            /* raw socket interface (ipv6) */
   /* the following should actually set a flag in the flags variable above */
   #define LIBNET_LINK_ADV 0x08            /* advanced mode link-layer */
   #define LIBNET_RAW4_ADV 0x09            /* advanced mode raw socket (ipv4) */
   #define LIBNET_RAW6_ADV 0x0a            /* advanced mode raw socket (ipv6) */
   #define LIBNET_ADV_MASK 0x08            /* mask to determine adv mode */
   
       /* _blocks is the highest level, and _end is closest to link-level */
       libnet_pblock_t *protocol_blocks;   /* protocol headers / data */
       libnet_pblock_t *pblock_end;        /* last node in list */
       uint32_t n_pblocks;                /* number of pblocks */
   
       int link_type;                      /* link-layer type, a DLT_ value. */
       /* These are the only values used by libnet (see libnet_build_arp and
        * libnet_build_link).  Other values are assigned by the various
        * libnet_link_*.c OS support functions, but are not yet used or supported,
        * they are effectively dead code. <pcap.h> claims these two are invariant
        * across operating systems... hopefully it is correct!
        */
   #ifndef DLT_EN10MB
   # define DLT_EN10MB      1       /* Ethernet (10Mb) */
   #endif
   #ifndef DLT_IEEE802
   # define DLT_IEEE802     6       /* IEEE 802 Networks */
   #endif
   
       int link_offset;                    /* link-layer header size */
       int aligner;                        /* used to align packets */
       char *device;                       /* device name */
   
       struct libnet_stats stats;          /* statistics */
       libnet_ptag_t ptag_state;           /* state holder for pblock tag */
       char label[LIBNET_LABEL_SIZE];      /* textual label for cq interface */
   
       char err_buf[LIBNET_ERRBUF_SIZE];   /* error buffer */
       uint32_t total_size;               /* total size */
   
       struct libnet_ether_addr link_addr; /* Link HW addr */
   };
   typedef struct libnet_context libnet_t;
   ```

   

7. 
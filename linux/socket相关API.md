# socket相关API : #include <sys/socket.h>

1. struct sockaddr：

   ```c
   	//socket的基类结构体
   #include <bits/socket.h>
       struct sockaddr
   179   {
   180     __SOCKADDR_COMMON (sa_);    /* Common data: address family and length. 协议族：sa_family  */
   181     char sa_data[14];           /* Address data.  */
   182   };
   typedef unsigned short int sa_family_t;
   #define __SOCKADDR_COMMON(sa_prefix) sa_family_t sa_prefix##family
   ```

   

2. struct sockaddr_in:

   ```c
   /* Structure describing an Internet socket address.  */
   //IPV4 socket结构体
   struct sockaddr_in
     {
       __SOCKADDR_COMMON (sin_); // 等价于 sa_familt_t sin_family
       in_port_t sin_port;                 /* Port number.  */
       struct in_addr sin_addr;            /* Internet address.  */
   
       /* Pad to size of `struct sockaddr'.  */
       unsigned char sin_zero[sizeof (struct sockaddr)
                              - __SOCKADDR_COMMON_SIZE
                              - sizeof (in_port_t)
                              - sizeof (struct in_addr)];
     };
   
   typedef uint32_t in_addr_t;
   struct in_addr
     {
       in_addr_t s_addr;
     };
   ```

   

3. struct sockaddr_v6:

   ```c
   /* IPv6 address */
   /* Ditto, for IPv6.  */
   struct sockaddr_in6
     {
       __SOCKADDR_COMMON (sin6_); //等价 sa_family_t sin6_family
       in_port_t sin6_port;        /* Transport layer port # */
       uint32_t sin6_flowinfo;     /* IPv6 flow information */
       struct in6_addr sin6_addr;  /* IPv6 address */
       uint32_t sin6_scope_id;     /* IPv6 scope-id */
     };
   struct in6_addr
     {
       union
         {
           uint8_t __u6_addr8[16];
           uint16_t __u6_addr16[8];
           uint32_t __u6_addr32[4];
         } __in6_u;
       #define s6_addr                 __in6_u.__u6_addr8
   #ifdef __USE_MISC
   # define s6_addr16              __in6_u.__u6_addr16
   # define s6_addr32              __in6_u.__u6_addr32
   #endif
   }
   ```

   

4. struct sockaddr_ll:

   ```c
   #include <netpacket/packet.h>
   //用于原始套接字
   struct sockaddr_ll
     {
       unsigned short int sll_family;
       unsigned short int sll_protocol;
       int sll_ifindex;
       unsigned short int sll_hatype;
       unsigned char sll_pkttype;
       unsigned char sll_halen;
       unsigned char sll_addr[8];
     };
   ```

   

5. struct ifreq:

   ```c
   #include <net/ethernet.h>
   //位置：/usr/include/linux/if.h
   //数据链路层：获取网络硬件相关信息,通常搭配ioctl函数获取网卡相关数据
   struct ifreq {
   #define IFHWADDRLEN     6
           union
           {
                   char    ifrn_name[IFNAMSIZ];            /* if name, e.g. "en0" */
           } ifr_ifrn;
   
           union {
                   struct  sockaddr ifru_addr;
                   struct  sockaddr ifru_dstaddr;
                   struct  sockaddr ifru_broadaddr;
                   struct  sockaddr ifru_netmask;
                   struct  sockaddr ifru_hwaddr;
                   short   ifru_flags;
                   int     ifru_ivalue;
                   int     ifru_mtu;
                   struct  ifmap ifru_map;
                   char    ifru_slave[IFNAMSIZ];   /* Just fits the size */
                   char    ifru_newname[IFNAMSIZ];
                   void *  ifru_data;
                   struct  if_settings ifru_settings;
           } ifr_ifru;
   };
   //结构体中各成员的宏定义：
   #define ifr_name        ifr_ifrn.ifrn_name      /* interface name       */
   #define ifr_hwaddr      ifr_ifru.ifru_hwaddr    /* MAC address          */
   #define ifr_addr        ifr_ifru.ifru_addr      /* address              */
   #define ifr_dstaddr     ifr_ifru.ifru_dstaddr   /* other end of p-p lnk */
   #define ifr_broadaddr   ifr_ifru.ifru_broadaddr /* broadcast address    */
   #define ifr_netmask     ifr_ifru.ifru_netmask   /* interface net mask   */
   #define ifr_flags       ifr_ifru.ifru_flags     /* flags                */
   #define ifr_metric      ifr_ifru.ifru_ivalue    /* metric               */
   #define ifr_mtu         ifr_ifru.ifru_mtu       /* mtu                  */
   #define ifr_map         ifr_ifru.ifru_map       /* device map           */
   #define ifr_slave       ifr_ifru.ifru_slave     /* slave device         */
   #define ifr_data        ifr_ifru.ifru_data      /* for use by interface */
   #define ifr_ifindex     ifr_ifru.ifru_ivalue    /* interface index      */
   #define ifr_bandwidth   ifr_ifru.ifru_ivalue    /* link bandwidth       */
   #define ifr_qlen        ifr_ifru.ifru_ivalue    /* Queue length         */
   #define ifr_newname     ifr_ifru.ifru_newname   /* New name             */
   #define ifr_settings    ifr_ifru.ifru_settings  /* Device/proto settings*/
   ```

   

6. ioctl函数:

   ```c
   #include <sys/ioctl.h>
   //系统调用：设置/获取文件描述符相关信息：
   int ioctl(int fd, unsigned long request, ...);
   
   ```

   ```c
   //demo:
   		struct ifreq req;
    52         memcpy(&req.ifr_name,"ens33",IFNAMSIZ);
    53         //获取源mac地址
    54         if(ioctl(sfd,SIOCGIFHWADDR,&req) == -1)
    55                 perror_close_exit("get hw addr error",sfd);
    56       //  memcpy(message_buf+6,req.ifr_hwaddr.sa_data,6);
    57         //获取源IP地址
    58         if(ioctl(sfd,SIOCGIFADDR,&req) == -1)
    59                 perror_close_exit("get addr error",sfd);
   
    			struct sockaddr_ll addr;
    85         bzero(&addr,sizeof(addr));
    86         //设置要发送的网卡的index
    87         if(ioctl(sfd,SIOCGIFINDEX,&req) == -1)
    88                 perror_close_exit("get hw index error",sfd);
    89         addr.sll_ifindex = req.ifr_ifindex;
   ```

   

7. check_sum(计算校验和：反码求和):

   ```c
   /*
   	target: 要求和的帧
   	target_size:帧的长度
   */
   uint16_t check_sum(uint8_t* target,int target_size){
           uint32_t sum=0;
           while(target_size >1){
                   sum+= ((uint16_t)target[0] <<8 | target[1]);
                   target +=2;
                   target_size -=2;
           }
           if(target_size)
                   sum += (uint16_t)target[0] <<8;
           //处理最高位的进位
           while(sum >> 16)
                   sum = (sum & 0xFFFF) + (sum >> 16);
           return ~(uint16_t)sum;
   }
   ```

   

8. 创建socket：

   ```c
   /*
   	domain:  
   		协议族：AF_*与PF_*,如IPV4、IPV6为地址协议族AF，IPV4为AF_INET
   		原始套接字为：AF_PACKET
   	type：
   		创建套接字的类型：
   		如:SOCK_DGRAM为UDP
   		SOCK_STREAM为流式套接字TCP
   		SOCK_RAW为更低(数据链路层)一层的数据包，也就是一个完整帧
   	protocol:
   		附加协议：
   			没有写0；
   			如果要创建原始套接字，则可以设置抓包的类型：
   			ETH_P_ALL：所有以太网帧
   			ETH_P_IP：只抓IP协议的帧
   			...
   	返回值：
   		-1：套接字创建失败，可通过errno获取失败信息
   		非负数：套接字的文件描述符
   */
   int socket(int domain, int type, int protocol);
   ```

   

9. getsockopt与setsockopt:

   ```c
   //获取套接字相关数据信息
   int getsockopt(int sockfd, int level, int optname,void *optval, socklen_t *optlen);
   //设置套接字相关参数
   int setsockopt(int sockfd, int level, int optname,const void *optval, socklen_t optlen);
   ```

   ```c
   //demo
   //设置端口/地址复用
   int opt =1;
   setsockopt(listen_fd,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(int));
   setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(int));
   ```

   

10. struct ether_header：

    ```c
    //以太网帧头部结构体：
    #include <net/ethernet.h>
    /* 10Mb/s ethernet header */
    #define ETH_ALEN 6
    struct ether_header
    {
      uint8_t  ether_dhost[ETH_ALEN];       /* destination eth addr */
      uint8_t  ether_shost[ETH_ALEN];       /* source ether addr    */
      uint16_t ether_type;                  /* packet type ID field */
    } 
    ```

    

11. struct iphdr:

    ```c
    //ipv4首部的结构体
    #include <netinet/ip.h>
    struct iphdr {
    #if defined(__LITTLE_ENDIAN_BITFIELD)
            __u8    ihl:4,
                    version:4;
    #elif defined (__BIG_ENDIAN_BITFIELD)
            __u8    version:4,
                    ihl:4;
    #else
    #error  "Please fix <asm/byteorder.h>"
    #endif
            __u8    tos;
            __be16  tot_len;
            __be16  id;
            __be16  frag_off;
            __u8    ttl;
            __u8    protocol;
            __sum16 check;
            __be32  saddr;
            __be32  daddr;
            /*The options start here. */
    };
    ```

    

12. struct tcphdr：

    ```c
    //tcp首部结构体
    #include <netinet/tcp.h>
    typedef uint32_t tcp_seq;
    /*
     * TCP header.
     * Per RFC 793, September, 1981.
     */
    struct tcphdr
      {
        __extension__ union
        {
          struct
          {
            uint16_t th_sport;      /* source port */
            uint16_t th_dport;      /* destination port */
            tcp_seq th_seq;         /* sequence number */
            tcp_seq th_ack;         /* acknowledgement number */
    # if __BYTE_ORDER == __LITTLE_ENDIAN
            uint8_t th_x2:4;        /* (unused) */
            uint8_t th_off:4;       /* data offset */
    # endif
    # if __BYTE_ORDER == __BIG_ENDIAN
            uint8_t th_off:4;       /* data offset */
            uint8_t th_x2:4;        /* (unused) */
    # endif
            uint8_t th_flags;
    # define TH_FIN 0x01
    # define TH_SYN 0x02
    # define TH_RST 0x04
    # define TH_PUSH        0x08
    # define TH_ACK 0x10
    # define TH_URG 0x20
            uint16_t th_win;        /* window */
            uint16_t th_sum;        /* checksum */
            uint16_t th_urp;        /* urgent pointer */
          };
          struct
          {
            uint16_t source;
            uint16_t dest;
            uint32_t seq;
            uint32_t ack_seq;
    # if __BYTE_ORDER == __LITTLE_ENDIAN
            uint16_t res1:4;
            uint16_t doff:4;
            uint16_t fin:1;
            uint16_t syn:1;
            uint16_t rst:1;
            uint16_t psh:1;
            uint16_t ack:1;
            uint16_t urg:1;
            uint16_t res2:2;
            uint16_t doff:4;
            uint16_t res1:4;
            uint16_t res2:2;
            uint16_t urg:1;
            uint16_t ack:1;
            uint16_t psh:1;
            uint16_t rst:1;
            uint16_t syn:1;
            uint16_t fin:1;
            uint16_t window;
            uint16_t check;
            uint16_t urg_ptr;
          };
        };
    };
    ```

    

13. 一个使用首部结构体来解包的demo：

    ```c
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <net/ethernet.h>
    #include <netinet/ip.h>
    #include <netinet/tcp.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <err.h>
    /**
            接收SYN包
    */
    int main(){
            int sfd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_IP));
            if(sfd == -1)
                    err(EXIT_FAILURE,"create socket error");
            uint8_t message_buf[1500];
            struct sockaddr_in con_addr;
            //定义协议栈各层指针，解包使用
            struct ether_header* eth_hdr_ptr;
            struct iphdr* ip_header_ptr;
            struct tcphdr* tcp_header_ptr;
            while(1){
                    socklen_t stklen = sizeof(con_addr);
                    int recv_len = recvfrom(sfd,message_buf,sizeof(message_buf),0,(struct sockaddr*)&con_addr,&stklen);
                    uint8_t ip[INET_ADDRSTRLEN]={0};
                    /*
                    inet_ntop(AF_INET,&con_addr.sin_addr.s_addr,ip,INET_ADDRSTRLEN);
                    printf("ip = %s\n",ip);
                    if(strcmp(inet_ntop(AF_INET,&con_addr.sin_addr.s_addr,ip,INET_ADDRSTRLEN),"192.168.1.7"))
                            continue;
                    */
                    eth_hdr_ptr = (struct ether_header*)message_buf;
                    tcp_header_ptr = (struct tcphdr*)(message_buf+34);
                    ip_header_ptr = (struct iphdr*)(message_buf+14);
                    inet_ntop(AF_INET,&ip_header_ptr->saddr,ip,INET_ADDRSTRLEN);
                    //判断是否为tcp协议
                    if(strcmp(ip,"192.168.1.7") || ip_header_ptr->protocol == 17 || tcp_header_ptr->th_dport != htons(12000))
                            continue;
                    printf("拦截到192.168.1.7的tcp数据包\n");
                    printf("数据帧长度 = %d\n",recv_len);
                    printf("********************IP首部内容************************\n");
                    printf("version = %d\n",ip_header_ptr->version);
                    printf("首部长度 = %d\n",ip_header_ptr->ihl);
                    printf("ip分组总长度 = %d\n",ntohs(ip_header_ptr->tot_len));
                    printf("TTL = %d\n",ip_header_ptr->ttl);
                    printf("上层协议 = %d\n",ip_header_ptr->protocol);
                    printf("源IP = %s\n",inet_ntop(AF_INET,&ip_header_ptr->saddr,ip,INET_ADDRSTRLEN));
                    printf("目的IP = %s\n",inet_ntop(AF_INET,&ip_header_ptr->daddr,ip,INET_ADDRSTRLEN));
                    printf("********************TCP首部内容************************\n");
                    printf("源端口号 = %d\n",ntohs(tcp_header_ptr->th_sport));
                    printf("目的端口号 = %d\n",ntohs(tcp_header_ptr->th_dport));
                    printf("序列号 = %d\n",ntohl(tcp_header_ptr->th_seq));
                    printf("确认序列号 = %d\n",ntohl(tcp_header_ptr->th_ack));
                    printf("TCP首部长度 = %d\n",tcp_header_ptr->th_off);
                    printf("控制位 = %d\n",tcp_header_ptr->th_flags);
                    printf("窗口大小 = %d\n",ntohs(tcp_header_ptr->th_win));
                    break;
            }
            close(sfd);
            return 0;
    }
    ```

    

14. struct udphdr:

    ```c
    //udp首部结构体
    #include <netinet/udp.h>
    struct udphdr
    {
      __extension__ union
      {
        struct
        {
          uint16_t uh_sport;        /* source port */
          uint16_t uh_dport;        /* destination port */
          uint16_t uh_ulen;         /* udp length */
          uint16_t uh_sum;          /* udp checksum */
        };
        struct
        {
          uint16_t source;
          uint16_t dest;
          uint16_t len;
          uint16_t check;
        };
      };
    };
    ```

    

15. 
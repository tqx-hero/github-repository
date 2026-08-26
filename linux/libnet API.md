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
       libnet_ptag_t ptag_state;           /* state holder for pblock tag从0开始，每创建一个新的+1，可看作节点数量 */
       char label[LIBNET_LABEL_SIZE];      /* textual label for cq interface */
   
       char err_buf[LIBNET_ERRBUF_SIZE];   /* error buffer */
       uint32_t total_size;               /* total size */
   
       struct libnet_ether_addr link_addr; /* Link HW addr */
   };
   typedef struct libnet_context libnet_t;
   ```

   

7. libnet_build_arp:

   ```c
   //构建ARP包,返回该arp包在libnet_t中的位置标记(int32_t有符号整数)
   /*
   Parameters:
              hrd: 帧类型，以太网帧：ARPHRD_ETHER
              pro: 上层协议类型ETHERTYPE_IP
              hln: mac地址长度 6
              pln: 上层协议长度，ipv4=4
              op: arp操作：1、请求；2、应答
              sha: src mac
              spa: src ip
              tha: dst mac
              tpa: dst ip
              payload: 数据载荷，会在arp报文后面追加
              payload_s: 数据载荷长度
              l: libnet上下文
              ptag: protocol tag to modify an existing header, 0 to build a new one
   		  参数写入ptag =0，会给libnet上下文新建一个协议控制块，并设置ptag为原控制块
          Returns:
              protocol tag value on success, -1 on error
            
   */
    libnet_ptag_t libnet_build_arp (uint16_t hrd, uint16_t pro, uint8_t hln, uint8_t pln, uint16_t op, const uint8_t *sha, const uint8_t *spa, const uint8_t *tha, const uint8_t *tpa, const uint8_t *payload,
          uint32_tpayload_s, libnet_t *l, libnet_ptag_tptag);
   #define LIBNET_PTAG_INITIALIZER         0
   typedef int32_t libnet_ptag_t;
   ```

   

8. libnet_pblock_t结构体：

   ```c
   /*
    *  Libnet generic protocol block memory object.  Sort of a poor man's mbuf.
    	libnet协议控制块结构体(双向链表)：用ptag作为ID标识，处理每个包时，可通过该标识在struct libnet_context(该文档第6个)上下文的protocol_blocks指针遍历来获取该协议所有信息。
    */
   struct libnet_protocol_block
   {
       uint8_t *buf;                      /* protocol buffer */
       uint32_t b_len;                    /* length of buf */
       uint16_t h_len;                    /* header length */
          /* Passed as last argument to libnet_do_checksum(). Not necessarily used
           * by that function, it is essentially a pblock specific number, passed
           * from _builder to the _do_checksum
           *
           * Unused for IPV4_H block types.
           *
           * For protocols that sit on top of IP, it should be the the amount of
           * buf that will be included in the checksum, starting from the beginning
           * of the header.
           */
       uint32_t copied;                   /* bytes copied - the amount of data copied into buf */
          /* Used and updated by libnet_pblock_append(). */
       uint8_t type;                      /* type of pblock */
   /* this needs to be updated every time a new packet builder is added */
   /* libnet_diag_dump_pblock_type() also needs updating for every new pblock tag */
   #define LIBNET_PBLOCK_ARP_H             0x01    /* ARP header */
   #define LIBNET_PBLOCK_DHCPV4_H          0x02    /* DHCP v4 header */
   #define LIBNET_PBLOCK_DNSV4_H           0x03    /* DNS v4 header */
   #define LIBNET_PBLOCK_ETH_H             0x04    /* Ethernet header */
   #define LIBNET_PBLOCK_ICMPV4_H          0x05    /* ICMP v4 base header */
   #define LIBNET_PBLOCK_ICMPV4_ECHO_H     0x06    /* ICMP v4 echo header */
   #define LIBNET_PBLOCK_ICMPV4_MASK_H     0x07    /* ICMP v4 mask header */
   #define LIBNET_PBLOCK_ICMPV4_UNREACH_H  0x08    /* ICMP v4 unreach header */
   #define LIBNET_PBLOCK_ICMPV4_TIMXCEED_H 0x09    /* ICMP v4 exceed header */
   #define LIBNET_PBLOCK_ICMPV4_REDIRECT_H 0x0a    /* ICMP v4 redirect header */
   #define LIBNET_PBLOCK_ICMPV4_TS_H       0x0b    /* ICMP v4 timestamp header */
   #define LIBNET_PBLOCK_IGMP_H            0x0c    /* IGMP header */
   #define LIBNET_PBLOCK_IPV4_H            0x0d    /* IP v4 header */
   #define LIBNET_PBLOCK_IPO_H             0x0e    /* IP v4 options */
   #define LIBNET_PBLOCK_IPDATA            0x0f    /* IP data */
   #define LIBNET_PBLOCK_OSPF_H            0x10    /* OSPF base header */
   #define LIBNET_PBLOCK_OSPF_HELLO_H      0x11    /* OSPF hello header */
   #define LIBNET_PBLOCK_OSPF_DBD_H        0x12    /* OSPF dbd header */
   #define LIBNET_PBLOCK_OSPF_LSR_H        0x13    /* OSPF lsr header */
   #define LIBNET_PBLOCK_OSPF_LSU_H        0x14    /* OSPF lsu header */
   #define LIBNET_PBLOCK_OSPF_LSA_H        0x15    /* OSPF lsa header */
   #define LIBNET_PBLOCK_OSPF_AUTH_H       0x16    /* OSPF auth header */
   #define LIBNET_PBLOCK_OSPF_CKSUM        0x17    /* OSPF checksum header */
   #define LIBNET_PBLOCK_LS_RTR_H          0x18    /* linkstate rtr header */
   #define LIBNET_PBLOCK_LS_NET_H          0x19    /* linkstate net header */
   #define LIBNET_PBLOCK_LS_SUM_H          0x1a    /* linkstate as sum header */
   #define LIBNET_PBLOCK_LS_AS_EXT_H       0x1b    /* linkstate as ext header */
   #define LIBNET_PBLOCK_NTP_H             0x1c    /* NTP header */
   #define LIBNET_PBLOCK_RIP_H             0x1d    /* RIP header */
   #define LIBNET_PBLOCK_TCP_H             0x1e    /* TCP header */
   #define LIBNET_PBLOCK_TCPO_H            0x1f    /* TCP options */
   #define LIBNET_PBLOCK_TCPDATA           0x20    /* TCP data */
   #define LIBNET_PBLOCK_UDP_H             0x21    /* UDP header */
   #define LIBNET_PBLOCK_VRRP_H            0x22    /* VRRP header */
   #define LIBNET_PBLOCK_DATA_H            0x23    /* generic data */
   #define LIBNET_PBLOCK_CDP_H             0x24    /* CDP header */
   #define LIBNET_PBLOCK_IPSEC_ESP_HDR_H   0x25    /* IPSEC ESP header */
   #define LIBNET_PBLOCK_IPSEC_ESP_FTR_H   0x26    /* IPSEC ESP footer */
   #define LIBNET_PBLOCK_IPSEC_AH_H        0x27    /* IPSEC AH header */
   #define LIBNET_PBLOCK_802_1Q_H          0x28    /* 802.1q header */
   #define LIBNET_PBLOCK_802_2_H           0x29    /* 802.2 header */
   #define LIBNET_PBLOCK_802_2SNAP_H       0x2a    /* 802.2 SNAP header */
   #define LIBNET_PBLOCK_802_3_H           0x2b    /* 802.3 header */
   #define LIBNET_PBLOCK_STP_CONF_H        0x2c    /* STP configuration header */
   #define LIBNET_PBLOCK_STP_TCN_H         0x2d    /* STP TCN header */
   #define LIBNET_PBLOCK_ISL_H             0x2e    /* ISL header */
   #define LIBNET_PBLOCK_IPV6_H            0x2f    /* IP v6 header */
   #define LIBNET_PBLOCK_802_1X_H          0x30    /* 802.1x header */
   #define LIBNET_PBLOCK_RPC_CALL_H        0x31    /* RPC Call header */
   #define LIBNET_PBLOCK_MPLS_H            0x32    /* MPLS header */
   #define LIBNET_PBLOCK_FDDI_H            0x33    /* FDDI header */
   #define LIBNET_PBLOCK_TOKEN_RING_H      0x34    /* TOKEN RING header */
   #define LIBNET_PBLOCK_BGP4_HEADER_H     0x35    /* BGP4 header */
   #define LIBNET_PBLOCK_BGP4_OPEN_H       0x36    /* BGP4 open header */
   #define LIBNET_PBLOCK_BGP4_UPDATE_H     0x37    /* BGP4 update header */
   #define LIBNET_PBLOCK_BGP4_NOTIFICATION_H 0x38  /* BGP4 notification header */
   #define LIBNET_PBLOCK_GRE_H             0x39    /* GRE header */
   #define LIBNET_PBLOCK_GRE_SRE_H         0x3a    /* GRE SRE header */
   #define LIBNET_PBLOCK_IPV6_FRAG_H       0x3b    /* IPv6 frag header */
   #define LIBNET_PBLOCK_IPV6_ROUTING_H    0x3c    /* IPv6 routing header */
   #define LIBNET_PBLOCK_IPV6_DESTOPTS_H   0x3d    /* IPv6 dest opts header */
   #define LIBNET_PBLOCK_IPV6_HBHOPTS_H    0x3e    /* IPv6 hop/hop opts header */
   #define LIBNET_PBLOCK_SEBEK_H           0x3f    /* Sebek header */
   #define LIBNET_PBLOCK_HSRP_H            0x40    /* HSRP header */
   #define LIBNET_PBLOCK_ICMPV6_H          0x41    /* ICMPv6 header (unused) */
   #define LIBNET_PBLOCK_ICMPV6_ECHO_H     0x46    /* ICMPv6 echo header */
   #define LIBNET_PBLOCK_ICMPV6_UNREACH_H  0x42    /* ICMPv6 unreach header */
   #define LIBNET_PBLOCK_ICMPV6_NDP_NSOL_H 0x43    /* ICMPv6 NDP neighbor solicitation header */
   #define LIBNET_PBLOCK_ICMPV6_NDP_NADV_H 0x44    /* ICMPv6 NDP neighbor advertisement header */
   #define LIBNET_PBLOCK_ICMPV6_NDP_OPT_H  0x45    /* ICMPv6 NDP option */
   #define LIBNET_PBLOCK_LLDP_H            0x50    /* LLDP header */
   #define LIBNET_PBLOCK_LLDP_CHASSIS_H    0x51    /* LLDP Chassis header */
   #define LIBNET_PBLOCK_LLDP_PORT_H       0x52    /* LLDP Port header */
   #define LIBNET_PBLOCK_LLDP_TTL_H        0x53    /* LLDP TTL header */
   #define LIBNET_PBLOCK_LLDP_END_H        0x54    /* LLDP End of LLDPDU header */
   #define LIBNET_PBLOCK_LLDP_ORG_SPEC_H   0x55    /* LLDP Organization Specific header */
   #define LIBNET_PBLOCK_UDLD_H            0x56    /* UDLD header */
   #define LIBNET_PBLOCK_UDLD_DEVICE_ID_H  0x57    /* UDLD Device ID header*/
   #define LIBNET_PBLOCK_UDLD_PORT_ID_H    0x58    /* UDLD Port ID header */
   #define LIBNET_PBLOCK_UDLD_ECHO_H       0x59    /* UDLD Echo ID header */
   #define LIBNET_PBLOCK_UDLD_MSG_INTERVAL_H 0x60  /* UDLD Message Interval header */
   #define LIBNET_PBLOCK_UDLD_TMT_INTERVAL_H 0x61  /* UDLD Timeout Interval header */
   #define LIBNET_PBLOCK_UDLD_DEVICE_NAME_H  0x62  /* UDLD Device Name header*/
   #define LIBNET_PBLOCK_UDLD_SEQ_NUMBER_H 0x63    /* UDLD Sequence Number header */
   
       uint8_t flags;                             /* control flags */
   #define LIBNET_PBLOCK_DO_CHECKSUM       0x01    /* needs a checksum */
       libnet_ptag_t ptag;                 /* protocol block tag */
       /* Chains are built from highest level protocol, towards the link level, so
        * prev traverses away from link level, and next traverses towards the
        * link level.
        */
       struct libnet_protocol_block *next; /* next pblock */
       struct libnet_protocol_block *prev; /* prev pblock */
   };
   typedef struct libnet_protocol_block libnet_pblock_t;
   ```

   

9. libnet_autobuild_arp:

   ```c
   //Autouilds an Address Resolution Protocol (ARP) header. Dependingon the op value, the function builds one of several different types of RFC 826 or RFC 903 RARP packets.
   /*
   Parameters:
              op ARP operation type
              sha sender's hardware address
              spa sender's protocol address
              tha target hardware address
              tpa targer protocol address
              l pointer to a libnet context
    Returns:
              protocol tag value on success, -1 on error
   */
   libnet_ptag_t libnet_autobuild_arp (uint16_top, const uint8_t *sha, const uint8_t *spa, const uint8_t *tha, uint8_t *tpa, libnet_t *l) ;
   typedef int32_t libnet_ptag_t;
   ```

   

10. libnet_autobuild_ethernet:

    ```c
    /*
    	Autobuilds an Ethernet header. The RFC 894 Ethernet II header is almost identical to the IEEE 802.3 header, with
           the exception that the field immediately following the source address holds the layer 3 protocol (as opposed to frame's length). You should only use this function when libnet is initialized with
           the LIBNET_LINK interface.
    */
    /*
    Parameters:
               dst destination ethernet address
               type upper layer protocol type
               l pointer to a libnet context
    
           Returns:
               protocol tag value on success, -1 on error
    */
    libnet_ptag_t libnet_autobuild_ethernet (const uint8_t *dst, uint16_ttype, libnet_t *l);
    ```

    

11. libnet_build_ethernet:

    ```c
    /*
    Builds an Ethernet header. The RFC
           894 Ethernet II header is almost identical to the IEEE 802.3 header, with the exception that the field immediately following the source address holds the layer 3 protocol (as opposed to frame's
           length). You should only use this function when libnet is initialized with the LIBNET_LINK interface.
           Parameters:
               dst destination ethernet address
               src source ethernet address
               type upper layer protocol type
               payload optional payload or NULL
               payload_s payload length or 0
               l pointer to a libnet context
               ptag protocol tag to modify an existing header, 0 to build a new one
    
           Returns:
               protocol tag value on success, -1 on error
    */
    libnet_ptag_t libnet_build_ethernet (const uint8_t *dst, const uint8_t *src, uint16_t type, const uint8_t *payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag) ;
    ```

    

12. libnet_adv_cull_packet:

    ```c
    //该函数是拷贝一份报文副本放入packet指针的地址。当配合pcap_sendpacket/send发送包时，可直接使用packet包。
    //如果使用libnet_write()进行发包，那不需要这个函数，避免重复拷贝。
    /*
    将 handle 内部已经组装完成的报文，**拷贝一份出来，堆上 malloc，返回给你指针 packet**.
    该函数会在拷贝的同时计算校验和放入副本报文相关缓冲区(不会更新libnet结构体中的原始报文)。
    此函数是高级接口的一部分，仅在libnet以高级模式初始化时可用
    值得注意的是，该函数执行隐式malloc（），并应相应地调用libnet_adv_free_packet（）以释放占用的内存包
    如果出现错误，可调用libnet_geterror(libnet_t *)来获取失败信息
    */
    /*
    Parameters:
               l :libnet上下文
               packet：包的指针的地址。libent先malloc一块内存，地址写入这个packet地址，再将组好的包拷贝一份放到这个内存区域
               packet_s：包的长度。
    
           Returns:
               1 on success, -1 on failure
    */
    int libnet_adv_cull_packet (libnet_t *l, uint8_t **packet, uint32_t *packet_s);
           
    ```

    

13. libnet_adv_free_packet:

    ```c
    //释放libnet_adv_cull_packet()函数内部malloc申请的内存。
    /**
    Parameters:
               l pointer to a libnet context
               packet :要释放的内存的指针
    */
    void libnet_adv_free_packet (libnet_t *l, uint8_t *packet);
    ```

    

14. libnet_write:

    ```c
    /*
    	计算报文的校验和，写入报文并发送
    	 Parameters:
               l pointer to a libnet context
    
           Returns:
               the number of bytes written, -1 on error
    */
    int libnet_write (libnet_t *l);
          
    ```

    

15. 
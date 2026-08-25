## libpcap三方库API：

1. 安装libpcap三方库:

   ```shell
   sudo apt install libpcap-dev
   ```

   

2. pcap_lookupdev(已弃用):

   ```c
   //查找第一个可用的网卡设备，返回它的名称。该函数只能返回第一个可用设备，如果有多个网卡，只能获取第一个，无法获取所有进行筛选。
   //所以该函数被弃用，使用pcap_findalldevs代替
   #include <pcap/pcap.h>
   char errbuf[PCAP_ERRBUF_SIZE];
   [DEPRECATED] char *pcap_lookupdev(char *errbuf);
   ```

   ```c
    //DEMO
   	#include <pcap/pcap.h>
     2 #include <string.h>
     3 #include <stdlib.h>
     4 /**
     5         pcap_looupdev用法:返回第一个可用的网卡。
     6         仅仅返回第一个，如果有多个网卡可用，无法满足条件。
     7         所以该函数已经被pcap_findalldevs淘汰。
     8         后者可以返回所有可用的网络设备，自行筛选即可
     9 */
    10 int main(){
    11         //pcap_lookupdev的使用
    12         char errbuf[PCAP_ERRBUF_SIZE];
    13         char * dev_ptr = pcap_lookupdev(errbuf);
    14         if(dev_ptr)
    15                 printf("dev:%s\n",dev_ptr);
    16         return 0;
    17 }
   ```

   

3. pcap_findalldevs:

   ```c
   //查找所有可用的网络设备，以链表的形式返回它们各自的信息
   #include <pcap/pcap.h>
   char errbuf[PCAP_ERRBUF_SIZE];
   /**
   	1、alldevsp:指针pcap_if_t*所在地址，生成的链表头节点会放入该指针所在的地址中
   	2、errbuf：遇到错误时返回的错误信息地址
   	返回值：0、成功获取（包括没有设备,获取的指针需要判空）；PCAP_ERROR：失败，errbuf中存放失败信息
   */
   int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf);
   //释放malloc申请的链表节点。与上面的find函数配套使用，避免内存泄漏
   void pcap_freealldevs(pcap_if_t *alldevs);
   
   //pcap_if_t结构体：
   typedef struct pcap_if pcap_if_t;
   254 /*
   255  * Item in a list of interfaces.
   256  */
   257 struct pcap_if {
   258         struct pcap_if *next;
   259         char *name;             /* name to hand to "pcap_open_live()" */
   260         char *description;      /* textual description of interface, or NULL */
   261         struct pcap_addr *addresses;
   262         bpf_u_int32 flags;      /* PCAP_IF_ interface flags */
   263 };
   264
   265 #define PCAP_IF_LOOPBACK                                0x00000001      /* interface is loopback */
   266 #define PCAP_IF_UP                                      0x00000002      /* interface is up */
   267 #define PCAP_IF_RUNNING                                 0x00000004      /* interface is running */
   268 #define PCAP_IF_WIRELESS                                0x00000008      /* interface is wireless (*NOT* necessarily Wi-Fi!) */
   269 #define PCAP_IF_CONNECTION_STATUS                       0x00000030      /* connection status: */
   270 #define PCAP_IF_CONNECTION_STATUS_UNKNOWN               0x00000000      /* unknown */
   271 #define PCAP_IF_CONNECTION_STATUS_CONNECTED             0x00000010      /* connected */
   272 #define PCAP_IF_CONNECTION_STATUS_DISCONNECTED          0x00000020      /* disconnected */
   273 #define PCAP_IF_CONNECTION_STATUS_NOT_APPLICABLE        0x00000030      /* not applicable */
   274
   275 /*
   276  * Representation of an interface address.
   		sockaddr如果是ipv4的地址要转成sockaddr_in类型
   277  */
   278 struct pcap_addr {
   279         struct pcap_addr *next;
   280         struct sockaddr *addr;          /* address，ipv4的地址要转成sockaddr_in类型 */
   281         struct sockaddr *netmask;       /* netmask for that address，ipv4的地址要转成sockaddr_in类型 */
   282         struct sockaddr *broadaddr;     /* broadcast address for that address */
   283         struct sockaddr *dstaddr;       /* P2P destination address for that address */
   284 };
   ```

   ```c
   //函数使用demo
     1 #include <pcap/pcap.h>
     2 #include <string.h>
     3 #include <stdlib.h>
     4 /**
     5         pcap_findalldevs
     6         //查找所有可用的网络设备，以链表的形式返回它们各自的信息
     7 #include <pcap/pcap.h>
     8 char errbuf[PCAP_ERRBUF_SIZE];
     9 int pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf);
    10 //释放malloc申请的链表节点。与上面的find函数配套使用，避免内存泄漏
    11 void pcap_freealldevs(pcap_if_t *alldevs);
    12 */
       	//定义一个包含网卡信息的结构体  
         typedef struct {
           uint32_t ip_addr,netmask_addr;
           uint8_t dev_name[DEV_NAME_SIZE];
   	} my_netdev_ipv4_t;
    13 int main(){
    14
    15         //pcap_findalldevs函数的使用
    16         char errbuf[PCAP_ERRBUF_SIZE];
    17         pcap_if_t* head;
    18         int ret = pcap_findalldevs(&head,errbuf);
    19         if(ret == PCAP_ERROR){
    20                 printf("find all devs failure: %s\n",errbuf);
    21                 exit(-1);
    22         }
        		my_netdev_ipv4_t net_info[5];
    23        int cnt =0;
           //过滤掉回环地址127与断开连接的
           bpf_u_int32 flag = PCAP_IF_LOOPBACK | PCAP_IF_CONNECTION_STATUS_DISCONNECTED;
           while(head && !(head->flags & flag) && cnt < dev_size){
                   strcpy(netinfo[cnt].dev_name,head->name);
                   struct pcap_addr* haddr = head->addresses;
                   while(haddr){
                           uint32_t ip = ((struct sockaddr_in*)haddr->addr)->sin_addr.s_addr;
                           struct sockaddr* netmask = haddr->netmask;
                           if(!ip || !netmask)
                                   goto goto_next;
                           char ip_addr[INET_ADDRSTRLEN],netmask_addr[INET_ADDRSTRLEN];
                           netinfo[cnt].ip_addr = ip;
                           netinfo[cnt].netmask_addr = ((struct sockaddr_in*)netmask)->sin_addr.s_addr;
                           break;
                   goto_next:
                           haddr = haddr->next;
                   }
                   cnt++;
                   head = head->next;
           }
    36         pcap_freealldevs(head);
    37
    38         return 0;
    39 }
   ```

   

4. pcap_open_live:

   ```c
   //开启网络设备进行捕获数据包
   #include <pcap/pcap.h>
   char errbuf[PCAP_ERRBUF_SIZE];
   /**
   	  5         pcap_open_live函数
     6         打开一个用于捕获数据的网络接口(存活的)
     7          pcap_t *pcap_open_live(const char *device, int snaplen,
     8                int promisc, int to_ms, char *errbuf);
     9         参数：
    10                 device : 设备名称
    11                 snaplen:捕获数据包的长度
    12                 promisc:是否是混杂模式。1、是；0、不是
    13                 to_ms:等待数据包的超时时间。如果设置为0，阻塞等待直到数据包被捕获到
    14                 errbuf:存放出错时的错误信息
    15         返回值：
    16                 返回一个pcap_t句柄指针，该句柄相当于文件描述符，对开发人员不透明
   */
   pcap_t *pcap_open_live(const char *device, int snaplen,int promisc, int to_ms, char *errbuf);
   ```

   ```c
    //demo
     1 #include <pcap/pcap.h>
     2 #include <string.h>
     3 #include <stdlib.h>
        int main(){
    19         //先用pcap_lookupdev等函数获取网卡名称
    20         char errbuf[PCAP_ERRBUF_SIZE];
    21         char * dev_name = pcap_lookupdev(errbuf);
    22         if(dev_name)
    23                 printf("dev_name:%s\n",dev_name);
    24         pcap_t* pt =  pcap_open_live(dev_name,1500,0,0,errbuf);
    25         return 0;
    26 }
   ```

   

5. pcap_lookupnet:

   ```c
   6         //用于搜索网卡的网段与子网掩码
     7                #include <pcap/pcap.h>
     8
     9        char errbuf[PCAP_ERRBUF_SIZE];
    10			/*
    				参数：
    14                 device:设备名
    15                 netp:存放网段的指针
    16                 maskp:存放子网掩码的指针
    17                 errbuf:出现错误时的错误信息
    			*/
    11        int pcap_lookupnet(const char *device, bpf_u_int32 *netp,bpf_u_int32 *maskp, char *errbuf);
   
   ```

   ```c
    19 int main(){
    20         //先用pcap_lookupdev等函数获取网卡名称
    21         char errbuf[PCAP_ERRBUF_SIZE];
    22         char * dev_name = pcap_lookupdev(errbuf);
    23         if(!dev_name)
    24                 exit(-1);
    25         bpf_u_int32 netp,maskp;
    26         int ret = pcap_lookupnet(dev_name,&netp,&maskp,errbuf);
    27         if(ret == PCAP_ERROR){
    28                 printf("error:%s\n",errbuf);
    29                 return -1;
    30         }
    31         //获取网卡的网段与子网掩码
    32         uint8_t * net_addr = (uint8_t*) &netp,*net_mask = (uint8_t*)&maskp;
    33         printf("net addr:%d.%d.%d.%d\n",net_addr[0],net_addr[1],net_addr[2],net_addr[3]);
    34         printf("mask :%d.%d.%d.%d\n",net_mask[0],net_mask[1],net_mask[2],net_mask[3]);
    35         return 0;
    36 }
   ```

   

6. pcap_next(不常用):

   ```c
   //捕获一个包
   /**
   	1、pcap_t* open_live生成的文件句柄
   	2、struct pcap_pkthdr 捕获的包的信息，包括长度、时间戳
   	返回值为包的数组地址
   */
   const u_char *pcap_next(pcap_t *p, struct pcap_pkthdr *h);
   
   //struct pcap_pkthdr:
   201 struct pcap_pkthdr {
   202         struct timeval ts;      /* time stamp */
   203         bpf_u_int32 caplen;     /* length of portion present,捕获的包长度，解包以这个为准 */
   204         bpf_u_int32 len;        /* length this packet (off wire)，包的总长度，不能以此为解包长度，因为长度可能会超过帧限定长度 */
   205 };
   ```

   

7. pcap_loop:

   ```c
   //循环捕获包，回调函数进行处理
   /**
   	1、p： 网络的文件句柄
   	2、cnt：捕获包的次数。大于0则捕获该次数包后结束，置-1表示无限捕获
   	3、callback:回调函数，调用该函数对包进行处理
   	4、user：传入回调函数的参数
   	返回值：成功0；失败或者被pcap_breakloop中断，返回PCAP_ERROR(-1的宏定义)
   */
   int pcap_loop(pcap_t *p, int cnt,pcap_handler callback, u_char *user);
   //回调函数声明：
   /**
   	从左到右参数分别为：
   	1、上述函数带过来的参数user
   	2、包的额外信息：包括时间戳、包长
   	3、包的首元素地址
   */
   typedef void (*pcap_handler)(u_char *, const struct pcap_pkthdr *,const u_char *);
   ```

   

8. pcap_close:

   ```c
   //关闭文件句柄
   void pcap_close(pcap_t *p);
   ```

   

9. pcap_compile:

   ```c
   //编译过滤规则
   /*
   	1、p：文件句柄
   	2、fp：要编译的规则（机器识别）
   	3、str:认为设置的过滤器(字符形式表示)
   	4、optimize:1开启bpf优化，0关闭
   	5、netmask：子网掩码。为了处理广播类地址，无需要可传0
   	返回值：成功：0，失败：-1
   	可用pcap_geterr(p)拿去失败信息
   */
   int pcap_compile(pcap_t *p, struct bpf_program *fp,const char *str, int optimize, bpf_u_int32 netmask);
   //释放上述申请的bpf_program内存
   void pcap_freecode(struct bpf_program *);
   //编译规则结构体：
   	#include <pcap/bpf.h>
   104 struct bpf_program {
   105         u_int bf_len;
   106         struct bpf_insn *bf_insns;
   107 };
   
   234 struct bpf_insn {
   235         u_short code;
   236         u_char  jt;
   237         u_char  jf;
   238         bpf_u_int32 k;
   239 };
   ```

   

10. 过滤规则表达式语法：

    ```shell
    #可通过命令行tcpdump调试过滤规则语法是否正确
    #正确输出BPF字节码，错误则会报错
    tcpdump -i eth0 'udp port 9799' -d
    ```

    ```c
    //常见表达式：
    //1.抓取本机9799端口udp(飞秋)
    "udp and port 9799"
    
    //2.只看源ip 192.168.1.105发往192.168.1.7的udp
    "udp and src host 192.168.1.105 and dst host 192.168.1.7"
    
    //3.排除arp，只看ip报文
    "ip and not arp"
    
    //4.以太网源mac过滤
    "ether src 00:11:22:33:44:55"
    
    ```

    ```plaintext
    //基础语法规则：
    1）限定符（3 类）
    类型限定符：host、net、port、portrange
    
    host 192.168.1.7        # ip主机
    net 192.168.1.0/24      #网段
    port 9799               #端口（飞秋就是9799）
    portrange 1000‑2000
    
    
    ```

    ````c
    2. **方向限定符**：`src`、`dst`、`src or dst`、`src and dst`
    
    ```
    src host 192.168.1.105
    dst port 9799
    ```
    ````

    ````c
    3. **协议限定符**：`ether`、`ip`、`arp`、`tcp`、`udp`、`icmp`
    
    ```
    udp and dst port 9799
    ip and src host 192.168.1.7
    ether src aa:bb:cc:dd:ee:ff
    ```
    ````

    ````c
    ### 2）逻辑运算符（优先级：not > and > or）
    
    `not`、`and`、`or`，支持括号改变优先级
    
    ```
    udp and (src port 9799 or dst port 9799)
    not arp and host 192.168.1.7
    ```
    ````

    ````c
    BPF 支持直接访问报文指定偏移：
    
    ```
    ether[0] & 0x01 = 1         #以太网目的mac最低位=1，广播/组播帧
    ip[8] = 0x40                #ipTTL字段，ip头偏移8字节
    udp[8:2] = 0x0030           #udp payload偏移8，取2字节
    ```
    
    格式：`协议[偏移[:长度]] 运算符 值`
    长度省略默认 1 字节；支持`=` `!=` `<` `>` `&`按位与
    ````

    

11. pcap_setfilter:

    ```c
    //设置过滤规则:将第10个函数编译过的BPF规则设置生效
    //成功返回0，失败返回PCAP_ERROR,可通过pcap_geterr(pcap_t *)来获取失败信息
    int pcap_setfilter(pcap_t *p, struct bpf_program *fp);
    ```

    

12. 
### **bufferevent：**

1. evconnlistener_new_bind:

   ```c
   //对socket执行：创建、绑定、监听、accept等一系列操作
   /**
      Allocate a new evconnlistener object to listen for incoming TCP connections
      on a given address.
   
      @param base: 需要绑定到的event_base句柄
      @param cb  :	回调函数。当有新链接进入(accept后)调用该函数。如果为NULL，则监听器为禁用状态，无法进行监听操作
      @param ptr : 传入回调函数的参数
      @param flags :	监听的标志位，均以LEV_OPT_* 开头，详细信息在下面展开
     @param backlog：设置连接队列的长度，-1则会选择默认长度
      @param addr : bind的服务端的ip、端口号信息
      @param socklen：addr的大小
    */
   struct evconnlistener *evconnlistener_new_bind(struct event_base *base,evconnlistener_cb cb, 
                                                  void *ptr, unsigned flags, int backlog,
                                                  const struct sockaddr *sa, int socklen);
   
   /**
     有新链接的回调函数
      @param listener ：监听器
      @param fd ：新连接的文件描述符(accept后的返回结果)
      @param addr:客户端的addr(accept函数返回时放置的结果)
      @param socklen ： socketlen_t 
      @param user_arg 绑定监听事件时传入的参数
    */
   typedef void (*evconnlistener_cb)(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
   
   /**
   	连接出现不可修复错误时的回调函数
      @param listener :监听器
      @param user_arg ：绑定监听时传入的参数
    */
   typedef void (*evconnlistener_errorcb)(struct evconnlistener *, void *);
   
   //unsigned flags宏取值：
   //1、将新连接的套接字con_fd设置为阻塞模式(默认是非阻塞)
   #define LEV_OPT_LEAVE_SOCKETS_BLOCKING	(1u<<0)
   //2、在释放监听器时关闭底层的socket
   #define LEV_OPT_CLOSE_ON_FREE		(1u<<1)
   /** 表示在可行的情况下，我们应当设置执行时关闭标志 */
   #define LEV_OPT_CLOSE_ON_EXEC		(1u<<2)
   /** 单进程场景下跳过断开链接的TIME_WAIT状态，可以直接复用ip+port */
   #define LEV_OPT_REUSEABLE		(1u<<3)
   /** 保证线程安全 */
   #define LEV_OPT_THREADSAFE		(1u<<4)
   /** 禁用监听，可使用evconnlistener_enable()使能 */
   #define LEV_OPT_DISABLED		(1u<<5)
   /**
   表示监听器应尽可能推迟 accept () 调用，直至有数据就绪。在不支持该特性的平台上此标志会被忽略。
   该选项可提升部分协议的性能，这类协议中客户端建立连接后会立刻发送数据。如果你的协议并非以客户端发送数据作为起始流程，则不要使用该选项；否则在内核层面可能出现完全不通知你连接事件的情况。
   此选项仅受 evconnlistener_new_bind () 支持，无法配合 evconnlistener_new_fd () 使用，原因是监听器需要在完成实际绑定操作之前就获知要启用该选项。
   */
   #define LEV_OPT_DEFERRED_ACCEPT		(1u<<6)
   /** 
   	 只会在linux且内核为3.9+生效
    1、允许多个监听 socket，同时 bind 完全相同的 IP:port，每个进程 / 线程拥有自己独立 listener fd
    负载均衡时使用。
    2、他只解决多个socket可以同时绑定同一个IP：port，不能解决断开连接后的端口复用问题。
    所以如果需要开启端口复用，需要与LEV_OPT_REUSEABLE一同使用：
    	LEV_OPT_REUSEABLE | LEV_OPT_REUSEABLE_PORT
    */
   #define LEV_OPT_REUSEABLE_PORT		(1u<<7)
   /**
   指示侦听器仅使用 IPv6 套接字进行工作。
   根据 RFC3493 标准以及大多数 Linux 发行版，默认工作模式为 IPv4 映射模式。如果需要在相同 IP 地址的同一端口上，为 IPv4 和 IPv6 配置不同的处理程序，则必须设置 IPV6_V6ONLY 套接字选项，以确保代码按预期运行，不受系统中 bindv6only 系统控制参数的影响。
   Windows 系统同样支持该套接字选项。
    */
   #define LEV_OPT_BIND_IPV6ONLY		(1u<<8)
   //去使能监听事件并且释放资源 = evconnlistener_disable + free...
   void evconnlistener_free(struct evconnlistener *lev);
   //使能监听事件
   int evconnlistener_enable(struct evconnlistener *lev);
   //去使能监听事件
   int evconnlistener_disable(struct evconnlistener *lev);
   //给监听事件设置出现错误时的回调函数
   void evconnlistener_set_error_cb(struct evconnlistener *lev,evconnlistener_errorcb errorcb);
   ```

   DEMO:

   ```c
   #include <event.h>
   #include <string.h>
   #include <stdlib.h>
   #include <stdio.h>
   #include <unistd.h>
   #include <event2/listener.h>
   #include <arpa/inet.h>
   #define SERVER_PORT 9000
   /**
    * 使用bufferevent的demo
    */
   
   //自定义结构体，创建每一个连接监听事件时传入的参数
   typedef struct con_socket_t{
   	int con_fd;
   	struct sockaddr addr;
   	char ip[INET_ADDRSTRLEN];
   	uint16_t port;
   }con_socket_t;
   
   void listen_callback (struct evconnlistener *listener,evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr);
   void listener_error_callback(struct evconnlistener * listener, void * arg);
   void  read_handler (struct bufferevent *bev, void *ctx);
   void  write_handler (struct bufferevent *bev, void *ctx);
   void signal_handler (struct bufferevent *bev, short what, void *ctx);
   int main(){
   	//直接使用api创建socket、绑定、监听
   	struct event_base * evb;
   	struct evconnlistener * ev_listener;
   	evb = event_base_new();
   	/* struct evconnlistener *evconnlistener_new_bind(struct event_base *base,
    27     evconnlistener_cb cb, void *ptr, unsigned flags, int backlog,
    28     const struct sockaddr *sa, int socklen);
    29 void evconnlistener_free(struct evconnlistener *lev);
    
    typedef void (*evconnlistener_cb)(struct evconnlistener *listener,
   118     evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr);
    */
   	struct sockaddr_in serveraddr;
   	bzero(&serveraddr,sizeof(serveraddr));
   	serveraddr.sin_family = AF_INET;
   	serveraddr.sin_port = htons(SERVER_PORT);
   	ev_listener = evconnlistener_new_bind(evb,listen_callback,evb,LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
   		-1,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
   	if(!ev_listener){
   		fprintf(stderr,"create listener error\n");
   		return -1;
   	}
   	//可以选择设置监听出现异常时的回调函数
   // typedef void (*evconnlistener_errorcb)(struct evconnlistener *, void *);
   	evconnlistener_set_error_cb(ev_listener,listener_error_callback);
   	event_base_dispatch(evb);
   	evconnlistener_free(ev_listener);
   	event_base_free(evb);
   	return 0;
   }
   
   
   /**
    * 有新连接的回调函数
    */
   void listen_callback (struct evconnlistener *listener,evutil_socket_t con_fd, struct sockaddr *addr, int len, void *arg){
   	//可以通过listener获取event_base
   	struct event_base* base =  evconnlistener_get_base(listener);
   	//也可以传参形式传递过来
   	// struct event_base* bs = (struct event_base*) arg;
   	struct sockaddr_in* addr_in = (struct sockaddr_in*)addr;
   	con_socket_t* cst =  malloc(sizeof(con_socket_t));
   	if(!cst){
   			fprintf(stderr,"malloc con_socket_t error!\n");
   			event_base_loopexit(base,NULL);
   	}
   	//填充结构体属性
   	cst->con_fd =con_fd;
   	memcpy(cst,addr,sizeof(addr));
   	fprintf(stdout,"[%s:%d] 已上线\n",
   		inet_ntop(AF_INET,&addr_in->sin_addr.s_addr,cst->ip,INET_ADDRSTRLEN),cst->port= (addr_in->sin_port));
   	//通过bufferevent_socket_new 给新连接注册监听事件
   	struct bufferevent * bev = bufferevent_socket_new(base,con_fd,BEV_OPT_CLOSE_ON_FREE);
   	//设置事件的回调函数
   	/* void bufferevent_setcb(struct bufferevent *bufev,
       bufferevent_data_cb readcb, bufferevent_data_cb writecb,
       bufferevent_event_cb eventcb, void *cbarg); */
   // typedef void (*bufferevent_data_cb)(struct bufferevent *bev, void *ctx);
   // typedef void (*bufferevent_event_cb)(struct bufferevent *bev, short what, void *ctx);
   	bufferevent_setcb(bev,read_handler,write_handler,signal_handler,cst);
   	//使能所要监听的事件
   	bufferevent_enable(bev,EV_READ);
   }
   //注册套接字的读、写以及信号处理事件
   void  read_handler (struct bufferevent *bev, void *ctx){
   	//struct evbuffer *bufferevent_get_input(struct bufferevent *bufev);
   	
   	// struct evbuffer* r_buf = bufferevent_get_input(bev);
   	// int r_len = evbuffer_get_length(r_buf);
   	char r_buf[1500];
   	int r_len = bufferevent_read(bev,r_buf,sizeof(r_buf));
   	r_buf[r_len] ='\0';
   	//可通过以下方式获取套接字
   	// int con_fd = bufferevent_get_fd(bev);
   	//直接解析参数
   	con_socket_t* cst = (con_socket_t*) ctx;
   	fprintf(stdout,"[%s:%d]:%s\n",cst->ip,cst->port,r_buf);
   	// bufferevent_read(bev);
   	//回射回客户端
   	bufferevent_write(bev,r_buf,r_len);
   }
   void  write_handler (struct bufferevent *bev, void *ctx){
   
   
   }
   
   void signal_handler (struct bufferevent *bev, short events, void *ctx){
   	con_socket_t* cst = (con_socket_t*) ctx;
   	if(events & (BEV_EVENT_ERROR | BEV_EVENT_EOF)){
   		if(events & BEV_EVENT_ERROR)
   			perror("buffer event handler error");
   		else 
   			//连接关闭了，需要释放资源
   			fprintf(stdout,"[%s:%d]已下线\n",cst->ip,cst->port);
   		//关闭连接
   		free(cst);
   		bufferevent_free(bev);
   	}
   }
   //监听出现异常的回调函数
   //第二个参数是在创建监听时传入的参数。上面传入的是event_base的指针，所以这里可以直接强转使用
   //如果不是传递的该指针，可以通过evconlistener_get_base(listener)获取
   void listener_error_callback(struct evconnlistener * listener, void * arg){
   	//struct event_base* base = (struct event_base*) arg;
   	struct event_base* base = evconnlistener_get_base(listener);
   	//printf("equals = %d\n",base == bs);
   	//通过EVUTIL_SOCKET_ERROR()获取errno
   	int errfd = EVUTIL_SOCKET_ERROR();
   	fprintf(stderr,"error: %d ; error message: %s\n",errfd,evutil_socket_error_to_string(errfd));
   	//关闭连接
   	event_base_loopexit(base,NULL);
   }
   ```
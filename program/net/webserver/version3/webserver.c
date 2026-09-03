#include "./function/header/http_handler.h"
#include <arpa/inet.h>
#define SERVER_PORT 9000
/**
 * 使用bufferevent的web服务器
 */

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
	char r_buf[1500];
	int r_len = bufferevent_read(bev,r_buf,sizeof(r_buf));
	r_buf[r_len] ='\0';
	//可通过以下方式获取套接字
	// int con_fd = bufferevent_get_fd(bev);
	//直接解析参数
	con_socket_t* cst = (con_socket_t*) ctx;
	//调用http相应处理函数
	char error_buf[64];
	parse_http_request(bev,r_buf,r_len,error_buf);
	//设置需要关闭的标志，当写入完成后会调用写事件，在那里关闭连接
	((con_socket_t*) ctx) ->close =1;
}
//当写入内核的发送缓冲区完成后的回调函数，在这里关闭连接
void  write_handler (struct bufferevent *bev, void *ctx){
	con_socket_t* cst = (con_socket_t*)ctx;
	if(cst->close){
		printf("数据已发送完毕,正在关闭连接...\n");
		bufferevent_free(bev);
		free(cst);
	}
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
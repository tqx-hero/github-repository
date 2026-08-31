#include "/home/tqx/net/wrapper/sockwrapper.h"
#include "/home/tqx/net/thread-pool/thread-pool.h"
#include "./function/header/decode.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#define MAX_THREAD_SIZE 20
#define SERVER_PORT 9000
#define STATIC_HOME_DIR "static"
#define EVENT_BUFFER_SIZE 1024
#define MESSAGE_BUFFER_SIZE 1499
/**
 * 优化服务器，将每个套接字与需要处理的业务函数绑定
 * 当事件触发时，根据不同事件进行相关处理，这就是反应堆模式
 */
typedef struct epoll_event event_type;
typedef struct sockaddr sock_addr_type;

// 反应堆的文件描述符与函数处理绑定的结构体
typedef struct
{
	int cur_fd;
	func_type func_handler;
	void *arg;
} reactor_t;
// 各事件触发后回调函数的参数
typedef struct
{
	int epfd;
	int con_fd;
	uint16_t cli_port;
	char cli_ip[INET_ADDRSTRLEN];
	pthread_pool_t *thread_pool;
	reactor_t *reactor;
} con_sock_t;

con_sock_t *malloc_consock_t(const con_sock_t *params);
reactor_t *malloc_reactor_t(int con_fd, func_type func_handler, void *arg);
void *reactor_listen(void *arg);
void *deal_with_socket(void *);
int main()
{
	// 创建监听套接字,设置为非阻塞
	int lfd = Socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	// 设置套接字端口、地址复用
	int opt = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int));
	// 绑定
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind(lfd, (sock_addr_type *)&server_addr, sizeof(server_addr));
	// 使监听套接字属性由主动连接变为被动链接
	Listen(lfd, 0);
	// 创建线程池，用线程池来处理连接的各种业务
	pthread_pool_t *pool = pthread_pool_create(MAX_THREAD_SIZE);
	if (!pool)
		exit(-1);
	// 创建epoll实例
	int epfd = Epoll_create(1);
	// 绑定套接字的要监听的事件
	event_type ep_event;
	ep_event.events = EPOLLIN; // 可以用或运算进行添加 | EPOLLOUT
	// 创建反应堆的事件驱动结构体
	con_sock_t temp;
	temp.epfd = epfd;
	temp.con_fd = lfd;
	temp.thread_pool = pool;
	con_sock_t *sct = malloc_consock_t(&temp);
	if (!sct)
	{
		close(lfd);
		return -1;
	}
	reactor_t *reactor = malloc_reactor_t(lfd, reactor_listen, (void *)sct);
	if (!reactor)
	{
		close(lfd);
		return -1;
	}
	// 将epoll监听事件之前绑定的fd切换为绑定结构体指针
	ep_event.data.ptr = (void *)reactor;
	Epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ep_event);
	// 内核监听事件
	event_type event_buffer[EVENT_BUFFER_SIZE];
	while (1)
	{
		// 判断一下是否是被信号中断的，如果是
		int event_count;
		while (((event_count = epoll_wait(epfd, event_buffer, EVENT_BUFFER_SIZE, -1)) == -1 && errno == EINTR) || event_count == 0)
			;
		for (int i = 0; i < event_count; i++)
		{
			event_type event = event_buffer[i];
			// 拿到事件的反应堆结构体
			reactor_t *cur_reactor = (reactor_t *)event.data.ptr;
			// 调用反应堆中绑定的相关函数
			cur_reactor->func_handler(cur_reactor->arg);
		}
	}
	pthread_pool_destory(pool, 1);
	free(sct);
	free(reactor);
	close(lfd);
	return 0;
}
// 申请套接字连接信息的结构体
con_sock_t *malloc_consock_t(const con_sock_t *params)
{
	con_sock_t *cst = malloc(sizeof(con_sock_t));
	if (!cst)
	{
		perror("malloc con_sock_t error");
		return NULL;
	}
	cst->epfd = params->epfd;
	cst->con_fd = params->con_fd;
	cst->cli_port = params->cli_port;
	cst->thread_pool = params->thread_pool;
	memcpy(cst->cli_ip, params->cli_ip, INET_ADDRSTRLEN);
	return cst;
}
// 申请反应堆的结构体
reactor_t *malloc_reactor_t(int con_fd, func_type func_handler, void *arg)
{
	reactor_t *reactor = malloc(sizeof(reactor_t));
	if (!reactor)
	{
		perror("malloc reactor  error");
		free(reactor);
		return NULL;
	}
	// 设置事件驱动的函数与参数
	reactor->cur_fd = con_fd;
	reactor->func_handler = func_handler;
	reactor->arg = arg;
	return reactor;
}
// 连接套接字的处理函数
void *reactor_connection(void *arg)
{
	con_sock_t *cskt = (void *)arg;
	pthread_pool_submit(((con_sock_t *)arg)->thread_pool, deal_with_socket, arg);
	return NULL;
}

// 反应堆的连接处理函数
void *reactor_listen(void *arg)
{
	con_sock_t *cskt = (void *)arg;
	int epfd = cskt->epfd, lfd = cskt->con_fd;
	con_sock_t temp;
	temp.thread_pool = cskt->thread_pool;
	// 如果是监听套接字，那就accept连接，并将新的
	// 连接套接字注册到epoll红黑树结构中监听
	struct sockaddr_in cli_addr;
	socklen_t stk_len = sizeof(cli_addr);
	int con_fd = Accept(lfd, (sock_addr_type *)&cli_addr, &stk_len);
	// 设置新连接的套接字为非阻塞模式
	int flags = fcntl(con_fd, F_GETFL, 0);
	fcntl(con_fd, F_SETFL, flags | O_NONBLOCK);
	get_client_info_ipv4(&cli_addr, temp.cli_ip, &temp.cli_port);
	printf("[%s:%d]已上线!\n", temp.cli_ip, temp.cli_port);
	temp.epfd = epfd;
	temp.con_fd = con_fd;
	// 设置连接套接字的反应堆结构体
	con_sock_t *sct = malloc_consock_t(&temp);
	if (!sct)
	{
		close(con_fd);
		return (void *)(long)-1;
	}
	reactor_t *reactor = malloc_reactor_t(con_fd, reactor_connection, (void *)sct);
	if (!reactor)
	{
		close(con_fd);
		return (void *)(long)-1;
	}
	sct->reactor = reactor;
	event_type ep_event;
	// 将已连接的socket注册监听事件
	// 设置事件触发为边沿触发
	// 注意：当监听写事件时，必须设置为边沿触发，以免不必要的状态切换
	ep_event.events = EPOLLIN | EPOLLET; // | EPOLLOUT;
	// 将epoll监听事件之前绑定的fd切换为绑定结构体指针
	ep_event.data.ptr = (void *)reactor;
	Epoll_ctl(epfd, EPOLL_CTL_ADD, con_fd, &ep_event);
	return (void *)(long)0;
}

/**
 * @brief 根据文件名后缀获取HTTP Content‑Type MIME字符串
 * @param filename 文件名，如 index.html、data.json、a.txt
 * @return 静态字符串，不要free；未知后缀返回 application/octet‑stream
 */
const char *get_content_type(const char *filename)
{
	// 找到最后一个 '.' 的位置
	const char *ext = strrchr(filename, '.');
	if (ext == NULL)
	{
		// 没有后缀
		return "application/octet-stream";
	}
	ext++; // 跳过 '.'，指向后缀文本，例如 "html"

	// 全部转小写比较，简单实现
	if (strcasecmp(ext, "html") == 0 || strcasecmp(ext, "htm") == 0)
		return "text/html; charset=utf-8";
	else if (strcasecmp(ext, "css") == 0)
		return "text/css; charset=utf-8";
	else if (strcasecmp(ext, "js") == 0)
		return "application/javascript; charset=utf-8";
	else if (strcasecmp(ext, "txt") == 0)
		return "text/plain; charset=utf-8";
	else if (strcasecmp(ext, "csv") == 0)
		return "text/csv; charset=utf-8";
	else if (strcasecmp(ext, "xml") == 0)
		return "text/xml; charset=utf-8";
	else if (strcasecmp(ext, "json") == 0)
		return "application/json";
	else if (strcasecmp(ext, "jpg") == 0 || strcasecmp(ext, "jpeg") == 0)
		return "image/jpeg";
	else if (strcasecmp(ext, "png") == 0)
		return "image/png";
	else if (strcasecmp(ext, "gif") == 0)
		return "image/gif";
	else if (strcasecmp(ext, "svg") == 0)
		return "image/svg+xml";
	else if (strcasecmp(ext, "ico") == 0)
		return "image/x-icon";

	// 未知后缀：二进制流，下载文件
	return "application/octet-stream";
}

// 获取文件大小
off_t get_file_size_stat(const char *file)
{
	struct stat st;
	if (stat(file, &st) == -1)
		return -1;
	return st.st_size;
}

// 处理GET请求
int handler_get_request(char *resource_url, int con_fd)
{
	char file_path[128] = STATIC_HOME_DIR;
	char state_message[50];
	int state_code = 0;
	off_t file_length = 0;
	if (strcmp("/", resource_url) == 0)
		resource_url = "/index.html";
	strcat(file_path, resource_url);
	char file_path_decode[128];
	utf_8_decoder(file_path_decode, file_path);
	printf("file_path = %s\n", file_path_decode);
	FILE *fptr;
	// 文件不存在，抛404
	struct stat st;
	if (stat(file_path_decode, &st) == -1)
	{
		state_code = 404;
		strcpy(state_message, "Not Found");
		strcpy(file_path_decode,  STATIC_HOME_DIR"/not_found.html");
		fptr = fopen(file_path_decode, "rb");
	}else{
		// 如果请求的是文件夹，需要回填文件夹的互动html界面
		if (S_ISDIR(st.st_mode))
			strcat(file_path_decode,"/index.html");
		//如果请求的是普通文件,直获取对应url下的文件，组包发送
		printf("请求的文件路径 = %s\n",file_path_decode);
		fptr = fopen(file_path_decode,"rb");
		//设置状态码与状态信息
		strcpy(state_message, "OK");
		state_code = 200;
	}
	// 需要再次判断请求的文件是目录还是普通文件
	// 开始读取文件内容.
	char message_buf[1024];
	int total_length = 0;
	// 拼接响应头
	total_length = sprintf(message_buf, "%s %d %s\r\n", "HTTP/1.1", state_code, state_message);
	// 设置文件长度
	total_length += sprintf(message_buf + total_length, "Content-Length: %lu\r\n", get_file_size_stat(file_path_decode));
	// 设置文件类型
	total_length += sprintf(message_buf + total_length, "Content-Type: %s\r\n", get_content_type(file_path_decode));
	total_length += sprintf(message_buf + total_length, "%c%c", '\r', '\n');
	// 查看请求头打印内容
	// message_buf[total_length] = 0;
	// printf("%s\n",message_buf);
	// 先发送响应报文头部
	Write(con_fd, message_buf, total_length);
	while (1)
	{
		total_length = fread(message_buf, sizeof(char), sizeof(message_buf), fptr);
		if (total_length == 0)
			break;
		Write(con_fd, message_buf, total_length);
	}
	fclose(fptr);
	return 0;
}

// 解析http请求
int parse_http_request(int con_fd, char *recv_buffer, int r_len, char *error_buf)
{
	char *error_message;
	char sub_str_buf[1024];
	char *sub_str = "\r\n";
	char request_type[8], request_resource[50];
	// 解析请求类型、请求资源
	// 1、使用strstr、strtok函数截取
	// 获取\r\n的位置
	/*
	char* ptr = strstr(recv_buffer,sub_str);
	printf("ptr == %d\n",ptr != NULL);
	if(!ptr){
		error_message = "http request format error!";
		goto failure_return;
	}
	uint32_t sub_len = (uint32_t)(ptr-recv_buffer);
	memcpy(sub_str_buf,recv_buffer,sub_len);
	sub_str_buf[sub_len] = 0;
	printf("数据=%s\n",sub_str_buf);
	//解析请求头：请求类型，资源
	char * pch;
	pch = strtok(sub_str_buf," ");
	//获取请求类型
	if(!pch){
		error_message = "get request type error!";
		goto failure_return;
	}
	strcpy(request_type,pch);
	pch = strtok(NULL," ");
	//获取请求的文件路径
	if(!pch){
		error_message = "get request resource url error!";
		goto failure_return;
	}
	strcpy(request_resource,pch);
	*/
	// 2、使用sscanf按照表达式截取
	sscanf(recv_buffer, "%[^ ] %[^ ]", request_type, request_resource);
	printf("请求类型 = %s\n", request_type);
	printf("请求资源 = %s\n", request_resource);
	// 根据请求资源查找路径下的文件，读取文件发送
	if (strcasecmp(request_type, "GET") == 0)
		handler_get_request(request_resource, con_fd);
	return 0;
failure_return:
	sprintf(error_buf, "%s", error_message);
	return -1;
}

// 需要修改arg参数为一个结构体：结构体分别存放当前套接字cur_fd与epoll根节点的描述符epfd
void *deal_with_socket(void *arg)
{
	con_sock_t *con_sock = (con_sock_t *)arg;
	if (!con_sock)
	{
		perror("con_sock_t* format error");
		return NULL;
	}
	int epfd = con_sock->epfd, cur_fd = con_sock->con_fd;
	char *cli_ip = con_sock->cli_ip;
	uint16_t cli_port = con_sock->cli_port;
	char recv_buffer[MESSAGE_BUFFER_SIZE + 1];
	// 获取线程的tid
	// pid_t tid = syscall(SYS_gettid);
	while (1)
	{
		int r_len = Read(cur_fd, recv_buffer, MESSAGE_BUFFER_SIZE);
		if (r_len == 0)
		{
			printf("[%s:%d]已下线!\n", cli_ip, cli_port);
			goto return_func;
		}
		if (r_len == -1)
		{
			// 由于设置了非阻塞，read可能读不到数据返回-1，此时需要判断
			// 是否为正常读不到数据还是异常
			if (!(errno == EAGAIN || errno == EWOULDBLOCK))
				// 如果是非正常读取，将该socket关闭，从epoll结构中删除
				perror("read error");
			else
				cur_fd = -1;
			goto return_func;
		}
		// recv_buffer[r_len] =0;
		// printf("[%s:%d]:%s\n",cli_ip,cli_port,recv_buffer);
		// 解析http请求，发送相关的资源
		char error_buf[512];
		if (parse_http_request(cur_fd, recv_buffer, r_len, error_buf) == -1)
			printf("error:%s\n", error_buf);
		// Write(cur_fd,recv_buffer,r_len);
	}
return_func:
	if (cur_fd >= 0)
	{
		// 需要将这个socket从epoll红黑树中去除
		// 下线断开连接
		Epoll_ctl(epfd, EPOLL_CTL_DEL, cur_fd, NULL);
		// 释放资源
		free(con_sock->reactor);
		con_sock->reactor = NULL;
		free(con_sock);
		close(cur_fd);
	}
	return NULL;
}

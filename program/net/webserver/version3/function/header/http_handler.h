#ifndef __HTTP_HANDLER_V2_H_
#define __HTTP_HANDLER_V2_H_
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "decode.h"
#include <event.h>
#include <event2/listener.h>
#define STATIC_HOME_DIR "static"
#define MESSAGE_BUFFER_SIZE 4096
#define FILE_NAME_MAX_SIZE 512
#define METHOD_SIZE 10
#define STATE_MSG_SIZE 64
typedef  struct bufferevent bufferevent_t;
typedef struct {
    int state_code;
    char state_msg[STATE_MSG_SIZE];
} res_state_t;

typedef struct {
	char * msg_buf;
	int buf_size;
}dir_padding_t;

//自定义结构体，创建每一个连接监听事件时传入的参数
typedef struct con_socket_t{
	int con_fd;
	struct sockaddr addr;
	char ip[INET_ADDRSTRLEN];
	uint16_t port;
	int close;
}con_socket_t;

int parse_http_request(bufferevent_t* bev, char *recv_buffer, int r_len, char *error_buf);
int handler_get_request(char *resource_url, bufferevent_t* bev);
const char *get_content_type(const char *filename);
off_t get_file_size_stat(const char *file);

#endif
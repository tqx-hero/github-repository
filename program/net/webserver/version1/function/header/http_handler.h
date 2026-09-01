#ifndef __HTTP_HANDLER_H_
#define __HTTP_HANDLER_H_
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "/home/tqx/net/wrapper/sockwrapper.h"
#include "decode.h"
#define STATIC_HOME_DIR "static"
#define MESSAGE_BUFFER_SIZE 4096
#define STATE_MSG_SIZE 64

typedef struct {
    int state_code;
    char state_msg[64];
} res_state_t;

int parse_http_request(int con_fd, char *recv_buffer, int r_len, char *error_buf);
int handler_get_request(char *resource_url, int con_fd);
const char *get_content_type(const char *filename);
off_t get_file_size_stat(const char *file);

#endif
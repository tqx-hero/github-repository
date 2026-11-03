#ifndef __MY_GETLINE_H
#define __MY_GETLINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#define RESIZE_FACTOR 2
#define DEFAULT_SIZE 128
//自定义实现getline，即按行读取文件流，动态管理内存,模板函数参考getline(3)
ssize_t mygetline(char **lineptr,size_t *size,FILE *stream);
//实现根据文件描述符获取一行
ssize_t fmygetline(int fd,char **lineptr,size_t *size);
//回收行缓冲区
int mygetline_free(char *lineptr);

#endif

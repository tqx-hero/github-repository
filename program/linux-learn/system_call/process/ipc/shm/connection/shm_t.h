#ifndef __MYSHM_T_H
#define __MYSHM_T_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//写入共享内存数据
typedef struct {
        pid_t pid;
        char msg[128];
}shm_msg_t; 

#endif

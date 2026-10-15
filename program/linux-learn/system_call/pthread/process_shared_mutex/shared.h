#ifndef __MY_SHARED_H_
#define __MY_SHARED_H_

#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#define PRO_COUNT 2
#define SHMAT_FAIL ((void*) -1)
#define PRINT_TOTAL_SIZE 10000
#define THREAD_PRINT "thread_print"
#define PTHREAD_COUNT 5

typedef struct {
        pthread_mutex_t lock;
        int total_cnt;
        int cur_cnt;
} shared_info_t;

#endif

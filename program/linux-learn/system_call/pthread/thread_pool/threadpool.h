#ifndef __THREAD_POOL_H
#define __THREAD_POOL_H
#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "ArrayDeque.h"
#define THREADPOOL_MQ_MSIZ 32768
#define THREADPOOL_MAX_SIZ 16
#define THREADPOOL_CORE_SIZ 10
#define THREADPOOL_WAIT_MTIME 10
#define THREADPOOL_ERR_SIZ 128
#define THREADPOOL_RUNNING 1
#define THREADPOOL_SHUTDOWN 0
#define PARAM_NOT_NULL(__PARAM) "参数:["__PARAM "] 不允许为空!"
typedef ArrayDeque mq_t;
typedef int strategy_t;
typedef struct {
	void* (*th_handler) (void*);//线程要执行的函数
	void* arg;//传入函数的参数
}work_t;

//拒绝策略
enum{
	DROP_THIS,
	DROP_MQ_HEAD,
	BLOCK,
	REJECT_RETURN;
};
//定义同步相关的锁、条件变量

typedef struct {
        pthread_mutex_t lock;
        pthread_cond_t full,empty;	
} LOCK_T;

//time_t为long int 类型
//定义线程池的结构体
typedef struct {
	size_t th_msize; //线程最大数量
	size_t th_csize;//核心线程数
	time_t wait_time;//非核心线程最长等待时间，单位秒,时间一到超过核心线程的线程被回收
	size_t mq_size; //消息队列大小
	strategy_t rejected_strategy; //拒绝策略
	int running;	//线程池运行状态，0停止运行；1正在运行
	size_t cur_th_size; //当前线程数
	mq_t* mqp;	//消息队列的地址
	LOCK_T lockinfo; //线程池的同步措施信息	
	pthread_mutex_t curth_lock; //修改当前线程数的锁
	pthread_t threads[];//所有线程的数组
} threadpool_t;

/**
    初始化线程池.
    参数列表：
	pool: 要初始化线程池的参数地址.结构体中必要的参数：
		th_msize、th_csize、wait_time、mq_size、rejected_strategy
	errbuf: 函数调用出现异常时的错误内容地址. 大小必须足够大，建议取值THREADPOOL_ERR_SIZ
    返回值：
	成功: 返回指向堆内存的线程池地址
	失败：返回NULL
*/
threadpool_t* threadpool_init(threadpool_t* pool,char * errbuf); 
/**
	提交任务
	pool: 线程池地址
	work: 线程执行的函数以及参数。该选项必须是指向堆内存的指针。
	errbuf：函数调用出现异常时的错误内容地址. 大小必须足够大，建议取值THREADPOOL_ERR_SIZ
	返回值：
          0: 成功
          -1: 失败，错误信息在errbuf
*/
int threadpool_submit(threadpool_t* pool,work_t* work,char* errbuf);
/**
	回收线程池，释放资源
*/
int threadpool_destory(threadpool_t* pool,char* errbuf);
#endif

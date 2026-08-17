#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/**
 *创建线程池
 *
 */
typedef void*(*func_type) (void*);
//任务队列(链表版本)
typedef struct task_t{
	func_type func;
	void* arg;
	struct task_t * next;
}task_t;

typedef struct {
	int thread_size,task_count; //初始设置的线程池大小、当前还有的任务个数
	task_t *head,*tail;	//任务队列的头尾指针。头负责执行任务(删除)，尾负责添加任务(添加)
	pthread_mutex_t  lock_t;
	pthread_cond_t  not_empty;
	int state; //线程池状态：0、正常；1、正常关闭；2、立即关闭
	pthread_t thread_arr[];// 线程数组-柔性
} pthread_poll_t;


//创建线程池
pthread_poll_t * pthread_poll_create(int poll_size);

//提交任务
int pthread_poll_submit(pthread_poll_t * pthread_poll,func_type func,void* arg);

int pthread_poll_destory(pthread_poll_t* thread_poll_ptr,int mode);

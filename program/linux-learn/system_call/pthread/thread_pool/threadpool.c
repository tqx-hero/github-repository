#include "threadpool.h"
#include <errno.h>
#define TOSTRING_ERRNO strerror(errno)

typedef struct {
	threadpool_t* pool;
	work_t work;
} worker_t;

void init_lockinfo(threadpool_t* pool){
	pthread_mutex_init(&pool->lockinfo.lock,NULL);
	pthread_mutex_init(&pool->curth_lock,NULL);
	pthread_cond_init(&pool->lockinfo.full,NULL);
	pthread_cond_init(&pool->lockinfo.empty,NULL);
}

//初始化线程池,返回线程池的地址
thread_pool_t* threadpool_init(threadpool_t* pool,char * errbuf){
	threadpool_t* retp;
	//参数校验
	if(!pool){
		strcpy(errbuf,PARAM_NOT_NULL("pool"));
		goto fail_ret;
	}
	//消息队列大小不能为0
	if(pool->mq_size <= 0){
		strcpy(errbuf,PARAM_NOT_NULL("mq_size"));
		goto fail_ret;
	}
	//最大线程数一定要大于等于核心线程数
	if(pool->th_msize < pool->th_csize){
		strcpy(errbuf,"th_msize must not be less than th_csize !");
		goto fail_ret;
	}
	if(pool->mq_size > THREADPOOL_MQ_MSIZ)
		pool->mq_size = THREADPOOL_MQ_MSIZ;

	//最大数量
	if(!pool->th_msize || pool->th_msize >= THREADPOOL_MAX_SIZ)
		pool->th_msize = THREADPOOL_MAX_SIZ;
	//核心数量
	if(!pool->th_csize || pool->th_csize >= THREADPOOL_CORE_SIZ)
		pool->th_csize = THREADPOOL_CORE_SIZ;
	if(pool->wait_time <= 0)
		pool->wait_time = THREADPOOL_WAIT_MTIME;
	//使用柔性数组填充线程数组，合并申请线程池的内存空间
	retp = (threadpool_t*) malloc(sizeof(threadpool_t) + pool->th_msize * sizeof(pthread_t));	
	if(!retp){
		strcpy(errbuf,"malloc threadpool error: " strerror(errno));
		goto fail_ret;
	}
	//将参数悉数拷贝到内存空间
	retp-> th_msize = pool->th_msize;
	retp-> th_csize = pool->th_csize;
	retp-> wait_time = pool->wait_time;
	retp-> mq_size = pool->mq_size;
	retp-> running = THREADPOOL_RUNNING;
	retp-> cur_th_size = 0;
	retp-> wait_time = pool->wait_time;
	//先暂时实现直接丢弃这一选项，后面再根据需要扩展
	retp-> rejected_strategy = DROP_THIS;
	//申请消息队列
	arrayDeque_initQueue(&retp->mqp,retp->mq_size);
	//加载条件变量与互斥锁
	init_lockinfo(retp);
	return retp;
fail_ret:
	return NULL;
}
//消费线程有多个
void* worker_handler(void* arg){
	pid_t tid =syscall(SYS_gettid);
	//拷贝出线程池指针、要执行的函数
	worker_t worker;
	memcpy(&worker,arg,sizeof(worker_t));
	//不要忘了释放内存
	free(arg);
	threadpool_t* pool = worker->pool;
	work_t work = worker->work;
	//执行任务
	work.th_handler(work.arg);
	//执行完任务后需要阻塞到消息队列
	while(pool->running){
		//这里先简单实现直接上锁，如果添加超时机制需要替换成timelock
		pthread_mutex_lock(&pool->lockinfo.lock);
		//如果队列已空，阻塞在条件队列,释放锁,同样先简单实现，后面可添加超时功能
		while(pool->running && arrayDeque_isEmpty(pool->mqp))
			pthread_cond_wait(&pool->lockinfo.empty);
		if(!pool->running){
			pthread_mutex_unlock(&pool->lockinfo.lock);
			break;
		}
		//队列不空，取出队头消费
		work_t qwork;
		arrayDeque_poll(pool->mqp,&qwork,sizeof(work_t));
		pthread_cond_signal(&pool->lockinfo.full);
		pthread_mutex_unlock(&pool->lockinfo.lock);
		//处理函数
		qwork.th_handler(qwork.arg);
	}
	//退出时需要修改当前线程数
	pthread_mutex_lock(&pool->curth_lock);
	--pool->cur_th_size;
	pthread_mutex_unlock(&pool->curth_lock);	
	printf("子线程[%d]退出...\n",tid);
	pthread_exit(NULL);
}
//创建临时线程执行任务
/*
int create_temp_thread(threadpool_t* pool,work_t* work,char* errbuf){
	
}
*/

//提交任务暂时只由主线程这一个线程进行提交
int threadpool_submit(threadpool_t* pool,work_t* work,char* errbuf){
	//首先查看当前线程数量,只要小于设定的核心线程数量，就创建
	//拼装指针结构体
	int newtemp = 0;
create_thread_start:
	pthread_mutex_lock(&pool->curth_lock);
	//线程数量已超过最大允许数量，直接丢弃
	if(pool->cur_th_size >= pool->th_msize){
		pthread_mutex_unlock(&pool->curth_lock);
		strcpy(errbuf,"线程池繁忙,请稍后再提交任务!");
		goto fail_ret;
	}
	//当小于核心线程数 || 需要创建临时线程时:
	if(newtemp || pool->cur_th_size < pool-> th_csize){
		pthread_t thread = pool->threads[pool->cur_th_size++];
		pthread_mutex_unlock(&pool->curth_lock);
		worker_t* worker = (worker_t*) malloc(sizeof(worker_t));
		if(!worker){
			strcpy(errbuf,"malloc error:" TOSTRING_ERRNO);
			goto fail_ret;
		}
		worker->pool = pool;
		memcpy(&worker->work,work,sizeof(work_t));//拷贝要执行的函数以及参数到结构体
		//创建新线程，执行任务
		if(pthread_create(&thread,NULL,worker_handler,worker)){
			strcpy(errbuf,"create thread error:" TOSTRING_ERRNO);
			goto fail_ret;
		}
		//设置线程自动分离属性
		if(pthread_detach(thread)){
			strcpy(errbuf,"detach thread error:" TOSTRING_ERRNO);
			goto fail_ret;
		}
		return 0;
	}
	pthread_mutex_unlock(&pool->curth_lock);
	//如果线程数在核心线程与最大线程之间，将任务入队列
	pthread_mutex_lock(&pool->lockinfo.lock);
	//队列已满,就需要尽可能地创建最大线程数
	if(arrayDeque_isFull(pool->mqp)){
		//不要忘了先解锁，再创建更多线程
		pthread_mutex_unlock(&pool->lockinfo.lock);
		newtemp = 1;
		goto create_thread_start;
	}
	//队列不空，入队列
	arrayDeque_offer(pool->mqp,work,sizeof(work_t));
	//唤醒有可能阻塞的消费线程，解锁
	pthread_cond_signal(&pool->lockinfo.empty);
	pthread_mutex_unlock(&pool->lockinfo.lock);
	return 0;
fail_ret:
	return -1;
}

int threadpool_destory(threadpool_t* pool,char* errbuf){
	pool->running = THREADPOOL_SHUTDOWN;
	//唤醒所有条件变量上阻塞的线程
	pthread_cond_broadcast(&pool->lockinfo.full);
	pthread_cond_broadcast(&pool->lockinfo.empty);
	//判断是否所有线程已全部退出
	while(1){
		pthread_mutex_lock(&pool->curth_lock);
		if(pool->cur_th_size ==0){
			pthread_mutex_unlock(&pool->curth_lock);
			printf("所有子线程已全部退出,开始回收资源\n");
			break;
		}
		pthread_mutex_unlock(&pool->curth_lock);
	}
	//销毁mutex、cond
	pthread_mutex_destroy(pool->lockinfo.lock);
	pthread_mutex_destroy(pool->curth_lock);
	pthread_cond_destroy(pool->lockinfo.full);
	pthread_cond_destroy(pool->lockinfo.empty);
	//销毁消息队列
	arrayDeque_destory(pool->mqp);
	free(pool);
	return 0;
}

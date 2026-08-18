#include "thread-pool.h"
#define POOL_DEFAULT_SIZE 10
//执行任务函数
static void* worker(void * arg){
	pthread_pool_t * thread_pool_ptr = (pthread_pool_t*) arg;
	for(;;){
		//上锁
		pthread_mutex_lock(&thread_pool_ptr->lock_t);
		//如果没有任务，即链表为空，需要继续阻塞
		while(!thread_pool_ptr->task_count && !thread_pool_ptr->state)
			pthread_cond_wait(&thread_pool_ptr->not_empty,&thread_pool_ptr->lock_t);
		//有任务就领取任务，执行
		//如果当前线程池状态为立即关闭或者优雅关闭+队列为空，直接释放锁并退出
		if(thread_pool_ptr->state ==2 || (thread_pool_ptr->state ==1 && thread_pool_ptr -> task_count ==0))
		{
			pthread_mutex_unlock(&thread_pool_ptr->lock_t);
			break;
		}
		//状态为正常状态，领取任务去执行
		task_t* task = thread_pool_ptr->head->next;
		thread_pool_ptr->head->next = task->next;
		if(--thread_pool_ptr->task_count == 0 )
			thread_pool_ptr->tail = thread_pool_ptr->head;
		pthread_mutex_unlock(&thread_pool_ptr->lock_t);
		task->func(task->arg);
		free(task);
		task =NULL;
	}
	return NULL;
}

//创建线程池
pthread_pool_t * pthread_pool_create(int pool_size){
	if(pool_size <=0)
		pool_size = POOL_DEFAULT_SIZE;
	pthread_pool_t * pool_ptr = (pthread_pool_t*) malloc(sizeof(pthread_pool_t) + pool_size *sizeof(pthread_t));
	if(!pool_ptr){
		perror("malloc error");
		return NULL;
	}
	//设置线程池属性
	pool_ptr -> state =0;
	pool_ptr -> task_count =0;
	pool_ptr -> thread_size = pool_size;
	if((pool_ptr -> head = malloc(sizeof(task_t))) == NULL)
	{
		perror("create sentinel error");
		free(pool_ptr);
		pool_ptr =NULL;
		return NULL;
	}
	pool_ptr->head->next =NULL;
	pool_ptr -> tail = pool_ptr->head;
	pthread_mutex_init(&pool_ptr->lock_t,NULL);
	pthread_cond_init(&pool_ptr->not_empty,NULL);
	//创建线程
	for(int i=0;i<pool_size;i++){
		if(pthread_create(&pool_ptr->thread_arr[i],NULL,worker,pool_ptr)){
			//创建失败，需要回收线程与线程池相关资源
			perror("pthread create error");
			//需要回收已创建的线程
			pool_ptr -> state =2;
			pthread_cond_broadcast(&pool_ptr->not_empty);
			for(int k =0;k<i;++k)
				pthread_join(pool_ptr->thread_arr[k],NULL);
			free(pool_ptr);
			pool_ptr =NULL;
			return NULL;
		}
	}
	return pool_ptr;
}
//
//提交任务
int pthread_pool_submit(pthread_pool_t * thread_pool_ptr,func_type func_sub,void* args){
	//先加锁，在添加任务
	pthread_mutex_lock(&thread_pool_ptr->lock_t);
	//申请空间
	task_t * task = (task_t*) malloc(sizeof(task_t));
	if(!task){
		perror("malloc task_t error");
		return -1;
	}
	task->func = func_sub;
	task -> arg = args;
	task -> next = NULL;
	//尾插法放入队列
	thread_pool_ptr->tail ->next =task;
	thread_pool_ptr->tail = task;
	thread_pool_ptr -> task_count++;
	//解锁，唤醒沉睡的工作线程
	pthread_mutex_unlock(&thread_pool_ptr->lock_t);
	pthread_cond_signal(&thread_pool_ptr->not_empty);
	return 0;
}
//销毁线程池
int pthread_pool_destory(pthread_pool_t* thread_pool_ptr,int mode){
	if(!thread_pool_ptr)
		return -1;
	//加锁，设置状态
	pthread_mutex_lock(&thread_pool_ptr->lock_t);
	thread_pool_ptr->state = mode;
	pthread_mutex_unlock(&thread_pool_ptr->lock_t);
	//唤醒所有正在阻塞的线程
	pthread_cond_broadcast(&thread_pool_ptr->not_empty);
	int pool_size = thread_pool_ptr->thread_size;
	//阻塞主线程等待所有子线程退出
	for(int i=0;i < pool_size;++i)
		pthread_join(thread_pool_ptr->thread_arr[i],NULL);
	//释放持有的资源
	task_t * cur = thread_pool_ptr->head;
	while(cur){
		task_t * nt = cur->next;
		free(cur);
		cur = nt;
	}
	thread_pool_ptr->head = thread_pool_ptr->tail =NULL;
	pthread_cond_destroy(&thread_pool_ptr->not_empty);
	pthread_mutex_destroy(&thread_pool_ptr->lock_t);
	free(thread_pool_ptr);
	thread_pool_ptr =NULL;
	return 0;
}


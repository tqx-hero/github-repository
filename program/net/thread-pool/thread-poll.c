#include "thread-poll.h"
#define POLL_DEFAULT_SIZE 10
//执行任务函数
static void* worker(void * arg){
	pthread_poll_t * thread_poll_ptr = (pthread_poll_t*) arg;
	for(;;){
		//上锁
		pthread_mutex_lock(&thread_poll_ptr->lock_t);
		//如果没有任务，即链表为空，需要继续阻塞
		while(!thread_poll_ptr->task_count && !thread_poll_ptr->state)
			pthread_cond_wait(&thread_poll_ptr->not_empty,&thread_poll_ptr->lock_t);
		//有任务就领取任务，执行
		//如果当前线程池状态为立即关闭或者优雅关闭+队列为空，直接释放锁并退出
		if(thread_poll_ptr->state ==2 || (thread_poll_ptr->state ==1 && thread_poll_ptr -> task_count ==0))
		{
			pthread_mutex_unlock(&thread_poll_ptr->lock_t);
			break;
		}
		//状态为正常状态，领取任务去执行
		task_t* task = thread_poll_ptr->head->next;
		thread_poll_ptr->head->next = task->next;
		if(--thread_poll_ptr->task_count == 0 )
			thread_poll_ptr->tail = thread_poll_ptr->head;
		pthread_mutex_unlock(&thread_poll_ptr->lock_t);
		task->func(task->arg);
		free(task);
		task =NULL;
	}
	return NULL;
}

//创建线程池
pthread_poll_t * pthread_poll_create(int poll_size){
	if(poll_size <=0)
		poll_size = POLL_DEFAULT_SIZE;
	pthread_poll_t * poll_ptr = (pthread_poll_t*) malloc(sizeof(pthread_poll_t) + poll_size *sizeof(pthread_t));
	if(!poll_ptr){
		perror("malloc error");
		return NULL;
	}
	//设置线程池属性
	poll_ptr -> state =0;
	poll_ptr -> task_count =0;
	poll_ptr -> thread_size = poll_size;
	if((poll_ptr -> head = malloc(sizeof(task_t))) == NULL)
	{
		perror("create sentinel error");
		free(poll_ptr);
		poll_ptr =NULL;
		return NULL;
	}
	poll_ptr->head->next =NULL;
	poll_ptr -> tail = poll_ptr->head;
	pthread_mutex_init(&poll_ptr->lock_t,NULL);
	pthread_cond_init(&poll_ptr->not_empty,NULL);
	//创建线程
	for(int i=0;i<poll_size;i++){
		if(pthread_create(&poll_ptr->thread_arr[i],NULL,worker,poll_ptr)){
			//创建失败，需要回收线程与线程池相关资源
			perror("pthread create error");
			//需要回收已创建的线程
			poll_ptr -> state =2;
			pthread_cond_broadcast(&poll_ptr->not_empty);
			for(int k =0;k<i;++k)
				pthread_join(poll_ptr->thread_arr[k],NULL);
			free(poll_ptr);
			poll_ptr =NULL;
			return NULL;
		}
	}
	return poll_ptr;
}
//
//提交任务
int pthread_poll_submit(pthread_poll_t * thread_poll_ptr,func_type func_sub,void* args){
	//先加锁，在添加任务
	pthread_mutex_lock(&thread_poll_ptr->lock_t);
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
	thread_poll_ptr->tail ->next =task;
	thread_poll_ptr->tail = task;
	thread_poll_ptr -> task_count++;
	//解锁，唤醒沉睡的工作线程
	pthread_mutex_unlock(&thread_poll_ptr->lock_t);
	pthread_cond_signal(&thread_poll_ptr->not_empty);
	return 0;
}
//销毁线程池
int pthread_poll_destory(pthread_poll_t* thread_poll_ptr,int mode){
	if(!thread_poll_ptr)
		return -1;
	//加锁，设置状态
	pthread_mutex_lock(&thread_poll_ptr->lock_t);
	thread_poll_ptr->state = mode;
	pthread_mutex_unlock(&thread_poll_ptr->lock_t);
	//唤醒所有正在阻塞的线程
	pthread_cond_broadcast(&thread_poll_ptr->not_empty);
	int poll_size = thread_poll_ptr->thread_size;
	//阻塞主线程等待所有子线程退出
	for(int i=0;i < poll_size;++i)
		pthread_join(thread_poll_ptr->thread_arr[i],NULL);
	//释放持有的资源
	free(thread_poll_ptr->head);
	thread_poll_ptr->head = thread_poll_ptr->tail =NULL;
	pthread_cond_destroy(&thread_poll_ptr->not_empty);
	pthread_mutex_destroy(&thread_poll_ptr->lock_t);
	free(thread_poll_ptr);
	thread_poll_ptr =NULL;
	return 0;
}


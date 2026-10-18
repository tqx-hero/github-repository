//
// Created by Administrator on 2026/5/18.
//

#include "ArrayDeque.h"
#include <stdio.h>

_Bool arrayDeque_isEmpty(ArrayDeque *queue) {
    return queue->count == 0;
}

void arrayDeque_initQueue(ArrayDeque **queue_p,size_t size) {
	if(!size || size > ARRAYDEQUE_MAX_SIZE)
		size = ARRAYDEQUE_MAX_SIZE;
	void* queue = calloc(1,sizeof(ArrayDeque) + sizeof(void*) * size);
	if(!queue){
		perror("calloc mq error");
		exit(-1);
	}
	*queue_p = (ArrayDeque*)queue;
	(*queue_p)->mq_size =size;
}

int arrayDeque_poll(ArrayDeque *queue,void* obj,size_t size) {
    if (!arrayDeque_isEmpty(queue)) {
	void* target = queue->obj[queue->front];
	memcpy(obj,target,size);
	//释放这个下标的内存空间
	free(target);
	queue->obj[queue->front] = NULL;
        queue->count--;
        queue->front = (queue->front +1) % queue->mq_size;
        return 0;
    }
    obj = NULL;
    return -1;
}

int arrayDeque_peek(ArrayDeque *queue,void* obj,size_t size) {
    if (!arrayDeque_isEmpty(queue)){
	memcpy(obj,queue->obj[queue->front],size);
        return 0;
    }
    obj = NULL;
    return -1;
}

_Bool arrayDeque_isFull(ArrayDeque *queue) {
    return queue->count == queue->mq_size;
}

int arrayDeque_size(ArrayDeque *queue) {
    return queue->count;
}

int arrayDeque_offer(ArrayDeque *queue, void* obj,size_t size) {
    if (!arrayDeque_isFull(queue)) {
	void* ptr= (void*) malloc(size);
	if(!ptr){
		fprintf(stderr,"malloc error\n");
		exit(-1);
	}
	queue->obj[queue->rear] = ptr;
	memcpy(queue->obj[queue->rear],obj,size);
        queue->rear = (queue->rear + 1) % (queue->mq_size);
        queue->count++;
        return 0;
    }
    return 0;
}

int arrayDeque_destory(ArrayDeque* queue){
	int front = queue->front,rear = queue->rear;
	while( front & (queue->mq_size - 1) != rear){
		free(queue->obj[front]);
		queue->obj[front] = NULL;
		front = (front + 1) % (queue->mq_size);
	}
	//释放柔性数组、mq
	free(queue);
	return 0;
}

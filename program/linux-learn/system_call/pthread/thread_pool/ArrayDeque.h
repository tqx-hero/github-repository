//
// Created by Administrator on 2026/5/18.
//

#ifndef OS_ARRAYDEQUE_H
#define OS_ARRAYDEQUE_H
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

//这里必须为2的整数幂
#define ARRAYDEQUE_MAX_SIZE 32768


//定义一个循环队列
typedef struct ArrayDeque {
    int count;
    int front;
    int rear;
    size_t mq_size;
    void* obj[];
} ArrayDeque;
/**
	查询当前队列的元素个数
	queue: 消息队列对象的地址
	return:
		成功：返回元素个数
		失败：-1
*/
int arrayDeque_size(ArrayDeque *queue);
/**
	初始化队列
        queue: 消息队列对象的地址
*/
void arrayDeque_initQueue(ArrayDeque **queue,size_t size);
/**
	判断当前队列是否为空
        queue: 消息队列对象的地址
        return:
                为空：1
                不为空：0
*/
_Bool arrayDeque_isEmpty(ArrayDeque *queue);
/**
	获取队头元素
        queue: 消息队列对象的地址
	obj: 将队头元素拷贝到该地址
	size：元素的大小，以字节为单位
        return:
                成功：0
                失败：-1
*/
int arrayDeque_peek(ArrayDeque *queue,void* obj,size_t size);
/**
        取出队头元素，队头元素出队
        queue: 消息队列对象的地址
        obj: 将队头元素拷贝到该地址
        size：元素的大小，以字节为单位
        return:
                成功：0
                失败：-1
*/
int arrayDeque_poll(ArrayDeque *queue,void*,size_t);
/**
        判断当前队列是否已满
        queue: 消息队列对象的地址
        return:
                已满：1
                不满：0
*/
_Bool arrayDeque_isFull(ArrayDeque *queue);
/**
        将元素添加到队列
        queue: 消息队列对象的地址
        obj: 元素的地址
        size：元素的大小，以字节为单位
        return:
                成功：0
                失败：-1
*/
int arrayDeque_offer(ArrayDeque *queue, void*,size_t);
/**
        销毁队列，回收队列资源
        queue: 消息队列对象的地址
*/
int arrayDeque_destory(ArrayDeque*);

#endif //OS_ARRAYDEQUE_H

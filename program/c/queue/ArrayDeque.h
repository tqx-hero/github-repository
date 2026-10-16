//
// Created by Administrator on 2026/5/18.
//

#ifndef OS_ARRAYDEQUE_H
#define OS_ARRAYDEQUE_H
#include <stddef.h>

#endif //OS_ARRAYDEQUE_H
//这里必须为2的整数幂
#define MAX_SIZE 64

//定义一个对象结构体
typedef struct Object {
    int num;
} Object;

//定义一个循环队列
typedef struct ArrayDeque {
    Object obj[MAX_SIZE];
    int count;
    int front;
    int rear;
} ArrayDeque;

int size(ArrayDeque *queue);

void initQueue(ArrayDeque *queue);

_Bool isEmpty(ArrayDeque *queue);

Object peek(ArrayDeque *queue);

Object poll(ArrayDeque *queue);

_Bool isFull(ArrayDeque *queue);

int offer(ArrayDeque *queue, Object obj);

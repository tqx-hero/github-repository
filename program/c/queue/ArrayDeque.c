//
// Created by Administrator on 2026/5/18.
//

#include "ArrayDeque.h"

#include <stdio.h>

_Bool isEmpty(ArrayDeque *queue) {
    return queue->count == 0;
}

void initQueue(ArrayDeque *queue) {
    queue->count = 0;
    queue->rear = 0;
    queue->front = 0;
}

Object poll(ArrayDeque *queue) {
    if (!isEmpty(queue)) {
        Object obj = queue->obj[queue->front];
        queue->count--;
        queue->front = (queue->front + 1) & (MAX_SIZE - 1);
        return obj;
    }
    Object obj = {-1};
    return obj;
}

Object peek(ArrayDeque *queue) {
    if (!isEmpty(queue))
        return queue->obj[queue->front];
    Object obj = {-1};
    return obj;
}

_Bool isFull(ArrayDeque *queue) {
    return queue->count == MAX_SIZE;
}

int size(ArrayDeque *queue) {
    return queue->count;
}

int offer(ArrayDeque *queue, Object obj) {
    if (!isFull(queue)) {
        queue->obj[queue->rear] = obj;
        queue->rear = (queue->rear + 1) & (MAX_SIZE - 1);
        queue->count++;
        return 1;
    }
    return 0;
}

// int main() {
//     ArrayDeque queue = {};
//     int i = 0;
//     for (i = 0; i < 64; ++i) {
//         Object obj = {i};
//         offer(&queue, obj);
//     }
//
//     for (i = 0; i < 10; ++i) {
//         Object obj = poll(&queue);
//         printf("%d\n", obj.num);
//     }
//     return 0;
// }

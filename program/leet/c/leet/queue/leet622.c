//
// Created by Administrator on 2026/6/24.
//
/**
*
代码
测试用例
测试用例
测试结果
622. 设计循环队列
中等
相关标签
premium lock icon
相关企业
设计你的循环队列实现。 循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。它也被称为“环形缓冲器”。

循环队列的一个好处是我们可以利用这个队列之前用过的空间。在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，即使在队列前面仍有空间。但是使用循环队列，我们能使用这些空间去存储新的值。

你的实现应该支持如下操作：

MyCircularQueue(k): 构造器，设置队列长度为 k 。
Front: 从队首获取元素。如果队列为空，返回 -1 。
Rear: 获取队尾元素。如果队列为空，返回 -1 。
enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
isEmpty(): 检查循环队列是否为空。
isFull(): 检查循环队列是否已满。


示例：

MyCircularQueue circularQueue = new MyCircularQueue(3); // 设置长度为 3
circularQueue.enQueue(1);  // 返回 true
circularQueue.enQueue(2);  // 返回 true
circularQueue.enQueue(3);  // 返回 true
circularQueue.enQueue(4);  // 返回 false，队列已满
circularQueue.Rear();  // 返回 3
circularQueue.isFull();  // 返回 true
circularQueue.deQueue();  // 返回 true
circularQueue.enQueue(4);  // 返回 true
circularQueue.Rear();  // 返回 4


提示：

所有的值都在 0 至 1000 的范围内；
操作数将在 1 至 1000 的范围内；
请不要使用内置的队列库。
 * @return
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int front, rear, size;
    int nums[];
} MyCircularQueue;


MyCircularQueue *myCircularQueueCreate(int k) {
    MyCircularQueue *queue = (MyCircularQueue *) malloc(sizeof(MyCircularQueue) + (k + 1) * sizeof(int));
    if (!queue) {
        printf("error: %s\n", strerror(errno));
        return NULL;
    }
    queue->size = k + 1;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

bool myCircularQueueIsEmpty(MyCircularQueue *obj) {
    return obj->rear == obj->front;
}

bool myCircularQueueIsFull(MyCircularQueue *obj) {
    return (obj->rear + 1) % obj->size == obj->front;
}

bool myCircularQueueEnQueue(MyCircularQueue *obj, int value) {
    if (myCircularQueueIsFull(obj))
        return false;
    obj->nums[obj->rear] = value;
    obj->rear = (obj->rear + 1) % obj->size;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue *obj) {
    if (myCircularQueueIsEmpty(obj))
        return false;
    obj->front = (obj->front + 1) % obj->size;
    return true;
}

int myCircularQueueFront(MyCircularQueue *obj) {
    if (myCircularQueueIsEmpty(obj))
        return -1;
    return obj->nums[obj->front];
}

int myCircularQueueRear(MyCircularQueue *obj) {
    if (myCircularQueueIsEmpty(obj))
        return -1;
    return obj->nums[(obj->rear - 1 + obj->size) % obj->size];
}


void myCircularQueueFree(MyCircularQueue *obj) {
    free(obj);
    obj = NULL;
}

int main() {
    /*MyCircularQueue circularQueue = new MyCircularQueue(3); // 设置长度为 3
circularQueue.enQueue(1);  // 返回 true
circularQueue.enQueue(2);  // 返回 true
circularQueue.enQueue(3);  // 返回 true
circularQueue.enQueue(4);  // 返回 false，队列已满
circularQueue.Rear();  // 返回 3
circularQueue.isFull();  // 返回 true
circularQueue.deQueue();  // 返回 true
circularQueue.enQueue(4);  // 返回 true
circularQueue.Rear();  // 返回 4*/
    // MyCircularQueue *queue = myCircularQueueCreate(3);
    // printf("%d\n", myCircularQueueEnQueue(queue, 1));
    // printf("%d\n", myCircularQueueEnQueue(queue, 2));
    // printf("%d\n", myCircularQueueEnQueue(queue, 3));
    // printf("%d\n", myCircularQueueEnQueue(queue, 4));
    //
    // printf("%d\n", myCircularQueueRear(queue));
    // printf("%d\n", myCircularQueueIsFull(queue));
    // printf("%d\n", myCircularQueueDeQueue(queue));
    // printf("%d\n", myCircularQueueEnQueue(queue, 4));
    // printf("%d\n", myCircularQueueRear(queue));
    // myCircularQueueFree(queue);


    /*"MyCircularQueue","enQueue","Front","isFull","enQueue","enQueue","enQueue","deQueue","enQueue","enQueue","isEmpty","Rear"]
￼
[       [4],                [3],    [],     [],         [7],    [2],        [5],    [],     [4],        [2],        [],[]]*/

    MyCircularQueue *queue = myCircularQueueCreate(4);
    printf("%d\n", myCircularQueueEnQueue(queue, 3));
    printf("%d\n", myCircularQueueFront(queue));
    printf("%d\n", myCircularQueueIsFull(queue));
    printf("%d\n", myCircularQueueEnQueue(queue, 7));
    printf("%d\n", myCircularQueueEnQueue(queue, 2));
    printf("%d\n", myCircularQueueEnQueue(queue, 5));
    printf("%d\n", myCircularQueueDeQueue(queue));
    printf("%d\n", myCircularQueueEnQueue(queue, 4));
    printf("%d\n", myCircularQueueEnQueue(queue, 2));
    printf("%d\n", myCircularQueueIsEmpty(queue));
    printf("%d\n", myCircularQueueRear(queue));
    myCircularQueueFree(queue);
    return 0;
}

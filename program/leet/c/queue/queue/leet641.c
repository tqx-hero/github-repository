//
// Created by Administrator on 2026/6/24.
//
/**
*
代码
测试用例
测试用例
测试结果
641. 设计循环双端队列
中等
相关标签
premium lock icon
相关企业
设计实现双端队列。

实现 MyCircularDeque 类:

MyCircularDeque(int k) ：构造函数,双端队列最大为 k 。
boolean insertFront()：将一个元素添加到双端队列头部。 如果操作成功返回 true ，否则返回 false 。
boolean insertLast() ：将一个元素添加到双端队列尾部。如果操作成功返回 true ，否则返回 false 。
boolean deleteFront() ：从双端队列头部删除一个元素。 如果操作成功返回 true ，否则返回 false 。
boolean deleteLast() ：从双端队列尾部删除一个元素。如果操作成功返回 true ，否则返回 false 。
int getFront() )：从双端队列头部获得一个元素。如果双端队列为空，返回 -1 。
int getRear() ：获得双端队列的最后一个元素。 如果双端队列为空，返回 -1 。
boolean isEmpty() ：若双端队列为空，则返回 true ，否则返回 false  。
boolean isFull() ：若双端队列满了，则返回 true ，否则返回 false 。


示例 1：

输入
["MyCircularDeque", "insertLast", "insertLast", "insertFront", "insertFront", "getRear", "isFull", "deleteLast", "insertFront", "getFront"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
输出
[null, true, true, true, false, 2, true, true, true, 4]

解释
MyCircularDeque circularDeque = new MycircularDeque(3); // 设置容量大小为3
circularDeque.insertLast(1);			        // 返回 true
circularDeque.insertLast(2);			        // 返回 true
circularDeque.insertFront(3);			        // 返回 true
circularDeque.insertFront(4);			        // 已经满了，返回 false
circularDeque.getRear();  				// 返回 2
circularDeque.isFull();				        // 返回 true
circularDeque.deleteLast();			        // 返回 true
circularDeque.insertFront(4);			        // 返回 true
circularDeque.getFront();				// 返回 4



提示：

1 <= k <= 1000
0 <= value <= 1000
insertFront, insertLast, deleteFront, deleteLast, getFront, getRear, isEmpty, isFull  调用次数不大于 2000 次
 * @return
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int front, rear, size;
    int nums[];
} MyCircularDeque;


MyCircularDeque *myCircularDequeCreate(int k) {
    MyCircularDeque *queue = (MyCircularDeque *) malloc(sizeof(MyCircularDeque) + (k + 1) * sizeof(int));
    if (!queue) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    queue->size = k + 1;
    queue->front = queue->rear = 0;
    return queue;
}


bool myCircularDequeIsEmpty(MyCircularDeque *obj) {
    return obj->rear == obj->front;
}

bool myCircularDequeIsFull(MyCircularDeque *obj) {
    return (obj->rear + 1) % obj->size == obj->front;
}

bool myCircularDequeInsertFront(MyCircularDeque *obj, int value) {
    if (myCircularDequeIsFull(obj))
        return false;
    int f = obj->front = (obj->front - 1 + obj->size) % obj->size;
    obj->nums[f] = value;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque *obj, int value) {
    if (myCircularDequeIsFull(obj))
        return false;
    obj->nums[obj->rear] = value;
    obj->rear = (obj->rear + 1) % obj->size;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque *obj) {
    if (myCircularDequeIsEmpty(obj))
        return false;
    obj->front = (obj->front + 1) % obj->size;
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque *obj) {
    if (myCircularDequeIsEmpty(obj))
        return false;
    obj->rear = (obj->rear - 1 + obj->size) % obj->size;
    return true;
}

int myCircularDequeGetFront(MyCircularDeque *obj) {
    if (myCircularDequeIsEmpty(obj))
        return -1;
    return obj->nums[obj->front];
}

int myCircularDequeGetRear(MyCircularDeque *obj) {
    if (myCircularDequeIsEmpty(obj))
        return -1;
    return obj->nums[(obj->rear - 1 + obj->size) % obj->size];
}

void myCircularDequeFree(MyCircularDeque *obj) {
    free(obj);
    obj = NULL;
}

int main() {
    /*MyCircularDeque circularDeque = new MycircularDeque(3); // 设置容量大小为3
circularDeque.insertLast(1);			        // 返回 true
circularDeque.insertLast(2);			        // 返回 true
circularDeque.insertFront(3);			        // 返回 true
circularDeque.insertFront(4);			        // 已经满了，返回 false
circularDeque.getRear();  				// 返回 2
circularDeque.isFull();				        // 返回 true
circularDeque.deleteLast();			        // 返回 true
circularDeque.insertFront(4);			        // 返回 true
circularDeque.getFront();				// 返回 4*/
    MyCircularDeque * queue = myCircularDequeCreate(3);
    printf("%d\n",myCircularDequeInsertLast(queue, 1));
    printf("%d\n",myCircularDequeInsertLast(queue, 2));
    printf("%d\n",myCircularDequeInsertFront(queue, 3));
    printf("%d\n",myCircularDequeInsertFront(queue, 4));
    printf("%d\n",myCircularDequeGetRear(queue));
    printf("%d\n",myCircularDequeIsFull(queue));
    printf("%d\n",myCircularDequeDeleteLast(queue));
    printf("%d\n",myCircularDequeInsertFront(queue, 4));
    printf("%d\n",myCircularDequeGetFront(queue));
    myCircularDequeFree(queue);
    return 0;
}

//
// Created by Administrator on 2026/6/8.
//
/**
*
￼
代码
￼
测试用例
测试用例
￼
测试结果
225. 用队列实现栈
￼
简单
￼
相关标签
￼
相关企业
￼
请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。
实现 MyStack 类：
• void push(int x) 将元素 x 压入栈顶。
• int pop() 移除并返回栈顶元素。
• int top() 返回栈顶元素。
• boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。 
注意：
• 你只能使用队列的标准操作 —— 也就是 push to back、peek/pop from front、size 和 is empty 这些操作。
• 你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。 
示例：
输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False
  提示：
• 1 <= x <= 9
• 最多调用100 次 push、pop、top 和 empty
• 每次调用 pop 和 top 都保证栈不为空 
进阶：你能否仅用一个队列来实现栈。
 * @return
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128
#define STACK MyStack*
#define QUEUE ArrayDeque*
#define QUEUE_PTR(p) &p->queue

//定义一个循环队列
typedef struct ArrayDeque {
    int obj[MAX_SIZE];
    int count;
    int front;
    int rear;
} ArrayDeque;

typedef struct {
    ArrayDeque queue;
} MyStack;

_Bool isEmpty(ArrayDeque *queue) {
    return queue->count == 0;
}

void initQueue(ArrayDeque *queue) {
    queue->count = 0;
    queue->rear = 0;
    queue->front = 0;
}

int poll(ArrayDeque *queue) {
    if (!isEmpty(queue)) {
        int obj = queue->obj[queue->front];
        queue->count--;
        queue->front = (queue->front + 1) & (MAX_SIZE - 1);
        return obj;
    }
    return -1;
}

int peek(ArrayDeque *queue) {
    if (!isEmpty(queue)) {
        return queue->obj[queue->front];
    }
    return -1;
}

_Bool isFull(ArrayDeque *queue) {
    return queue->count == MAX_SIZE;
}

int size(ArrayDeque *queue) {
    return queue->count;
}

int offer(ArrayDeque *queue, int obj) {
    if (!isFull(queue)) {
        queue->obj[queue->rear] = obj;
        queue->rear = (queue->rear + 1) & (MAX_SIZE - 1);
        queue->count++;
        return 1;
    }
    return 0;
}


MyStack *myStackCreate() {
    STACK stack = malloc(sizeof(MyStack));
    if (!stack) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    //加载队列
    initQueue(QUEUE_PTR(stack));
    return stack;
}

void myStackPush(MyStack *obj, int x) {
    offer(&obj->queue, x);
}

void reverseQ(STACK obj) {
    QUEUE deque = QUEUE_PTR(obj);
    //获取当前队列的size
    int sz = size(deque), i = 0;
    for (; i < sz - 1; ++i)
        offer(deque, poll(deque));
}

int myStackPop(MyStack *obj) {
    reverseQ(obj);
    return poll(QUEUE_PTR(obj));
}

int myStackTop(MyStack *obj) {
    reverseQ(obj);
    QUEUE queue = QUEUE_PTR(obj);
    int ret = poll(queue);
    offer(queue, ret);
    return ret;
}

bool myStackEmpty(MyStack *obj) {
    return isEmpty(QUEUE_PTR(obj));
}

void myStackFree(MyStack *obj) {
    free(obj);
    obj = NULL;
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);

 * int param_2 = myStackPop(obj);

 * int param_3 = myStackTop(obj);

 * bool param_4 = myStackEmpty(obj);

 * myStackFree(obj);
*/

int main() {
    STACK stack = myStackCreate();
    myStackPush(stack, 1);
    myStackPush(stack, 2);
    printf("%d\n", myStackTop(stack));
    printf("%d\n", myStackPop(stack));
    printf("%d\n", myStackEmpty(stack));

    printf("%d\n", myStackTop(stack));
    printf("%d\n", myStackPop(stack));
    printf("%d\n", myStackEmpty(stack));
    myStackFree(stack);
    return 0;
}

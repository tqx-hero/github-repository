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
232. 用栈实现队列
￼
简单
￼
相关标签
￼
相关企业
￼
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
实现 MyQueue 类：
• void push(int x) 将元素 x 推到队列的末尾
• int pop() 从队列的开头移除并返回元素
• int peek() 返回队列开头的元素
• boolean empty() 如果队列为空，返回 true ；否则，返回 false
说明：
• 你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
• 你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。 
示例 1：
输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
￼ 
提示：
• 1 <= x <= 9
• 最多调用 100 次 push、pop、peek 和 empty
• 假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作） 
进阶：
• 你能否实现每个操作均摊时间复杂度为 O(1) 的队列？换句话说，执行 n 个操作的总时间复杂度为 O(n) ，即使其中一个操作可能花费较长时间
 * @return
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_MAX_SIZE 101
#define STACK Stack*
#define QUEUE MyQueue*

//-------------stack-------------------------
typedef struct Stack {
    int arr[STACK_MAX_SIZE];
    int ptr;
    //可选函数指针
    // int (*func_ptr)(void *, ...);
} Stack;

typedef struct {
    STACK push_stack;
    STACK pop_stack;
} MyQueue;


void init(Stack *this) {
    this->ptr = -1;
}

void push(Stack *this, int x) {
    this->arr[++this->ptr] = x;
}

_Bool isEmpty(Stack *this) {
    return this->ptr == -1;
}

int pop(Stack *this) {
    return this->arr[this->ptr--];
}


int peek(Stack *this) {
    return this->arr[this->ptr];
}

//----------------------------------------

MyQueue *myQueueCreate() {
    QUEUE queue = malloc(sizeof(MyQueue));
    STACK push_stack = malloc(sizeof(Stack));
    STACK pop_stack = malloc(sizeof(Stack));
    if (!queue || !push_stack || !pop_stack) {
        printf("%s\n", strerror(errno));
        free(pop_stack);
        free(push_stack);
        free(queue);
        pop_stack = NULL;
        push_stack = NULL;
        queue = NULL;
        return NULL;
    }
    init(push_stack);
    init(pop_stack);
    queue->pop_stack = pop_stack;
    queue->push_stack = push_stack;
    return queue;
}

void myQueuePush(MyQueue *obj, int x) {
    push(obj->push_stack, x);
}

void transferData(MyQueue *obj) {
    STACK push_stack = obj->push_stack;
    STACK pop_stack = obj->pop_stack;
    //判断pop栈内是否为空，不为空弹栈，为空需要从push栈内所有数据压入pop栈，然后弹出栈顶
    if (isEmpty(pop_stack)) {
        while (!isEmpty(push_stack))
            push(pop_stack, pop(push_stack));
    }
}

int myQueuePop(MyQueue *obj) {
    transferData(obj);
    return pop(obj->pop_stack);
}

int myQueuePeek(MyQueue *obj) {
    transferData(obj);
    return peek(obj->pop_stack);
}

bool myQueueEmpty(MyQueue *obj) {
    return isEmpty(obj->pop_stack) && isEmpty(obj->push_stack);
}

void myQueueFree(MyQueue *obj) {
    free(obj->push_stack);
    free(obj->pop_stack);
    obj->push_stack = NULL;
    obj->pop_stack = NULL;
    free(obj);
    obj = NULL;
}

/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);

 * int param_2 = myQueuePop(obj);

 * int param_3 = myQueuePeek(obj);

 * bool param_4 = myQueueEmpty(obj);

 * myQueueFree(obj);
*/

int main() {
    MyQueue * queue = myQueueCreate();
    myQueuePush(queue, 1);
    myQueuePush(queue, 2);
    printf("%d\n",myQueuePeek(queue));
    printf("%d\n",myQueuePop(queue));
    printf("%d\n",myQueueEmpty(queue));
    myQueueFree(queue);
    return 0;
}

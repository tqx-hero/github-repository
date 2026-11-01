//
// Created by Administrator on 2026/6/5.
//
/**
*
代码
测试用例
测试用例
测试结果
155. 最小栈
中等
相关标签
premium lock icon
相关企业
提示
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int value) 将元素 value 推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。


示例 1:

输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.


提示：

-231 <= val <= 231 - 1
pop、top 和 getMin 操作总是在 非空栈 上调用
push, pop, top, and getMin最多被调用 3 * 104 次
 * @return
 */

#define STACK_MAX_SIZE  30001
#include <stdlib.h>

typedef struct {
    //当前值
    int val;
    //当前最小值
    int cur_min_val;
} stack_val;

typedef struct {
    int ptr;
    stack_val arr[STACK_MAX_SIZE];
} MinStack;


MinStack *minStackCreate() {
    MinStack *stack = malloc(sizeof(MinStack));
    stack->ptr = -1;
    return stack;
}

//是否为空？ptr=-1？
_Bool isEmpty(MinStack *obj) {
    return obj->ptr == -1;
}

void minStackPush(MinStack *obj, int value) {
    int cur_min_val;
    if (!isEmpty(obj)) {
        cur_min_val = obj->arr[obj->ptr].cur_min_val;
        cur_min_val = value >= cur_min_val ? cur_min_val : value;
    } else
        cur_min_val = value;
    int index = ++obj->ptr;
    obj->arr[index].val = value;
    obj->arr[index].cur_min_val = cur_min_val;
}

void minStackPop(MinStack *obj) {
    if (isEmpty(obj))
        return;
    obj->ptr--;
}

int minStackTop(MinStack *obj) {
    return obj->arr[obj->ptr].val;
}

int minStackGetMin(MinStack *obj) {
    return obj->arr[obj->ptr].cur_min_val;
}

void minStackFree(MinStack *obj) {
    free(obj);
}

// int main() {
//     return 0;
// }

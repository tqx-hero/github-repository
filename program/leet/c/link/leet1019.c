//
// Created by Administrator on 2026/6/25.
//
/**
* 1019. 链表中的下一个更大节点
中等
相关标签
premium lock icon
相关企业
提示
给定一个长度为 n 的链表 head

对于列表中的每个节点，查找下一个 更大节点 的值。也就是说，对于每个节点，找到它旁边的第一个节点的值，这个节点的值 严格大于 它的值。

返回一个整数数组 answer ，其中 answer[i] 是第 i 个节点( 从1开始 )的下一个更大的节点的值。如果第 i 个节点没有下一个更大的节点，设置 answer[i] = 0 。



示例 1：



输入：head = [2,1,5]
输出：[5,5,0]
示例 2：



输入：head = [2,7,4,3,5]
输出：[7,0,5,5,0]


提示：

链表中节点数为 n
1 <= n <= 104
1 <= Node.val <= 109
 * @return
 */
#include <stdlib.h>

#include "../node/listnode.h"
typedef struct ListNode *list_ptr;

// #define STACK_MAX_SIZE 100001
#define STACKPTR(name) Stack* name

//
typedef struct Stack {
    int ptr, size;
    int arr[];
    //可选函数指针
    // VOID (*func_ptr)(VOID, ...);
} Stack;

Stack *init(int size) {
    Stack *stack = malloc(sizeof(Stack) + size * sizeof(int));
    stack->ptr = -1;
    stack->size = size;
    return stack;
}

void push(STACKPTR(this), int x) {
    this->arr[++this->ptr] = x;
}

_Bool isEmpty(STACKPTR(this)) {
    return this->ptr == -1;
}

int pop(STACKPTR(this)) {
    return this->arr[this->ptr--];
}


int peek(STACKPTR(this)) {
    return this->arr[this->ptr];
}

void free_stack(STACKPTR(this)) {
    free(this);
}

//单调栈，倒着压栈，每次与栈顶比较，小与栈顶记录最近较大元素为栈顶元素，丢弃这个元素
//大于栈顶元素，则弹栈，直到找到比当前元素更大，记录答案、丢弃当前元素，或者栈空，答案记为0，入栈
int *nextLargerNodes(struct ListNode *head, int *returnSize) {
    list_ptr cur = head;
    int size = 0;
    while (cur) {
        size++;
        cur = cur->next;
    }
    *returnSize = size;
    int *ans = calloc(size, sizeof(int));
    cur = head;
    int i = 0;
    while (cur) {
        ans[i++] = cur->val;
        cur = cur->next;
    }
    Stack *stack = init(size);
    for (i = size - 1; i >= 0; i--) {
        int num = ans[i], answer = 0;
        while (!isEmpty(stack) && (answer = peek(stack)) <= num)
            pop(stack);
        //栈空
        if (isEmpty(stack))
            ans[i] = 0;
        else
            ans[i] = answer;
        push(stack, num);
    }
    free_stack(stack);
    return ans;
}

int main() {
    
    return 0;
}

//
// Created by Administrator on 2026/6/22.
//
/**
* Q2. 每日温度
中等
相关标签
premium lock icon
相关企业
提示
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。



示例 1:

输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
示例 2:

输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]
示例 3:

输入: temperatures = [30,60,90]
输出: [1,1,0]


提示：

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
 * @return
 */

#include <stdlib.h>


#define STACK_MAX_SIZE 100001
#define STACKPTR(name) Stack* name
#include <stdbool.h>
#include <stdio.h>

typedef struct Stack {
    int arr[STACK_MAX_SIZE];
    int ptr;
    //可选函数指针
} Stack;

void init(STACKPTR(this)) {
    this->ptr = -1;
}

void push(STACKPTR(this), int x) {
    this->arr[++this->ptr] = x;
}

bool isEmpty(STACKPTR(this)) {
    return this->ptr == -1;
}

int pop(STACKPTR(this)) {
    return this->arr[this->ptr--];
}


int peek(STACKPTR(this)) {
    return this->arr[this->ptr];
}


int *dailyTemperatures(int *temperatures, int temperaturesSize, int *returnSize) {
    *returnSize = temperaturesSize;
    int *ans = calloc(temperaturesSize, sizeof(int));
    Stack stack = {};
    init(&stack);
    int i = temperaturesSize - 1;
    push(&stack, i);
    ans[i] = 0;
    int index = -1;
    for (i--; i >= 0; i--) {
        while (!isEmpty(&stack) && temperatures[(index = peek(&stack))] <= temperatures[i])
            pop(&stack);
        if (isEmpty(&stack))
            ans[i] = 0;
        else
            ans[i] = index - i;
        push(&stack, i);
    }
    return ans;
}

int main() {
    int arr[] = {73, 74, 75, 71, 69, 72, 76, 73}, size;
    int *ans = dailyTemperatures(arr, sizeof(arr) / sizeof(int), &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", ans[i]);
    }
    free(ans);
    return 0;
}

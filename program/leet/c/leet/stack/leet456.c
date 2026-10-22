//
// Created by Administrator on 2026/6/6.
//
/**
* 456. 132 模式
中等
相关标签
premium lock icon
相关企业
给你一个整数数组 nums ，数组中共有 n 个整数。132 模式的子序列 由三个整数 nums[i]、nums[j] 和 nums[k] 组成，并同时满足：i < j < k 和 nums[i] < nums[k] < nums[j] 。

如果 nums 中存在 132 模式的子序列 ，返回 true ；否则，返回 false 。



示例 1：

输入：nums = [1,2,3,4]
输出：false
解释：序列中不存在 132 模式的子序列。
示例 2：

输入：nums = [3,1,4,2]
输出：true
解释：序列中有 1 个 132 模式的子序列： [1, 4, 2] 。
示例 3：

输入：nums = [-1,3,2,0]
输出：true
解释：序列中有 3 个 132 模式的的子序列：[-1, 3, 2]、[-1, 3, 0] 和 [-1, 2, 0] 。


提示：

n == nums.length
1 <= n <= 2 * 105
-109 <= nums[i] <= 109
 * @return
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define STACK_MAX_SIZE 200001

//
typedef struct Stack {
    int arr[STACK_MAX_SIZE];
    int ptr;
    //可选函数指针
} Stack;

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

//单调栈实现,栈内存放k
//从后往前压栈，每次与栈顶比较
//小于栈顶，入栈
//直到大于栈顶，记录栈顶元素为j，弹栈
//满足以上条件持续弹栈，同时更新j(因为是单调递增栈，所以j会逐渐增大)
//当栈顶元素不再小于当前元素或者栈空，停止弹栈，压入当前元素
//后续持续比较当前元素是否小于j，大于j的重复以上步骤，更新j的最大值
//只要出现小于j的情况，直接返回true
bool find132pattern(int *nums, int numsSize) {
    //初始化j
    int j = INT32_MIN;
    Stack stack = {};
    init(&stack);
    int index = numsSize - 1;
    push(&stack,  nums[index--]);
    while (index >= 0) {
        int num = nums[index--];
        //首先判断当前元素是否比j要小
        if (num < j)
            return true;
        if (num == j)
            continue;
        //大于j的，那就是k，根据条件入栈
        while (!isEmpty(&stack)) {
            int top = (int) peek(&stack);
            //小于栈顶元素,入栈
            if (num == top)
                break;
            if (num < top) {
                push(&stack,  num);
                break;
            }
            //大于栈顶元素，开始弹栈记录j的最大值
            if (num > top) {
                j = top;
                pop(&stack);
            }
        }
        //如果栈空，说明栈全部清理，num还没入栈，这时入栈
        if (isEmpty(&stack))
            push(&stack, num);
    }
    return false;
}

// int main() {
//     // int arr[]={-1,3,2,0};
//     // int arr[]={1,0,1,-4,-3};
//     int arr[] = {-2, 1, -2};
//     printf("%d\n", find132pattern(arr, 3));
//
//     return 0;
// }

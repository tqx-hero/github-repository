#include <stdio.h>
#include <stdlib.h>
//
// Created by Administrator on 2026/6/9.
//
/**
* 1475. 商品折扣后的最终价格
简单
相关标签
premium lock icon
相关企业
提示
给你一个数组 prices ，其中 prices[i] 是商店里第 i 件商品的价格。

商店里正在进行促销活动，如果你要买第 i 件商品，那么你可以得到与 prices[j] 相等的折扣，其中 j 是满足 j > i 且 prices[j] <= prices[i] 的 最小下标 ，如果没有满足条件的 j ，你将没有任何折扣。

请你返回一个数组，数组中第 i 个元素是折扣后你购买商品 i 最终需要支付的价格。



示例 1：

输入：prices = [8,4,6,2,3]
输出：[4,2,4,2,3]
解释：
商品 0 的价格为 price[0]=8 ，你将得到 prices[1]=4 的折扣，所以最终价格为 8 - 4 = 4 。
商品 1 的价格为 price[1]=4 ，你将得到 prices[3]=2 的折扣，所以最终价格为 4 - 2 = 2 。
商品 2 的价格为 price[2]=6 ，你将得到 prices[3]=2 的折扣，所以最终价格为 6 - 2 = 4 。
商品 3 和 4 都没有折扣。
示例 2：

输入：prices = [1,2,3,4,5]
输出：[1,2,3,4,5]
解释：在这个例子中，所有商品都没有折扣。
示例 3：

输入：prices = [10,1,1,6]
输出：[9,0,1,6]


提示：

1 <= prices.length <= 500
1 <= prices[i] <= 10^3
 * @return
 */
//用单调递减栈。
//从后往前压栈，栈空入栈，ret[i]=a[i]。
//栈不为空，与栈顶比较，大于的弹栈，直到栈空或者栈顶小于等于它。
//当小于时，ret[i]=a[i]-top,并压栈。等于时ret[i]=0,不入栈

#define STACK_MAX_SIZE 501

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

int *finalPrices(int *prices, int pricesSize, int *returnSize) {
    *returnSize = pricesSize;
    int *ret = (int *) calloc(pricesSize, sizeof(int));
    Stack stack = {};
    init(&stack);
    int i = pricesSize - 1;
    for (; i >= 0; --i) {
        int cur = *(prices+i);
        while (!isEmpty(&stack)) {
            int top = peek(&stack);
            if (cur < top)
                pop(&stack);
            else if (cur ==top) {
                *(ret+i)=0;
                break;
            }else {
                *(ret+i)=cur-top;
                push(&stack, cur);
                break;
            }
        }
        if (isEmpty(&stack)) {
            *(ret+i)=cur;
            push(&stack, cur);
        }
    }
    return ret;
}

int main() {
    int prices[]={8,4,6,2,3};
    int size;
    int *ret= finalPrices(prices,5,&size);
    for (int i = 0; i < size; ++i) {
        printf("%d ",ret[i]);
    }
    free(ret);
    return 0;
}

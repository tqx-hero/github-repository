//
// Created by Administrator on 2026/6/5.
//
/**
*
代码
测试用例
测试用例
测试结果
150. 逆波兰表达式求值
中等
相关标签
premium lock icon
相关企业
给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。

请你计算该表达式。返回一个表示表达式值的整数。

注意：

有效的算符为 '+'、'-'、'*' 和 '/' 。
每个操作数（运算对象）都可以是一个整数或者另一个表达式。
两个整数之间的除法总是 向零截断 。
表达式中不含除零运算。
输入是一个根据逆波兰表示法表示的算术表达式。
答案及所有中间计算结果可以用 32 位 整数表示。


示例 1：

输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
示例 2：

输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
示例 3：

输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22


提示：

1 <= tokens.length <= 104
tokens[i] 是一个算符（"+"、"-"、"*" 或 "/"），或是在范围 [-200, 200] 内的一个整数


逆波兰表达式：

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
逆波兰表达式主要有以下两个优点：

去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中
 * @return
 */

#include <stdlib.h>

// #include  "stack.h"

#include <ctype.h>  // 用到 isdigit() 判断数字
#include <stdio.h>

#define STACK_MAX_SIZE 100001
//
typedef struct Stack {
    int arr[STACK_MAX_SIZE];
    int count;
    int ptr;
} Stack;
// 判断字符串是否是纯整数
int isInteger(const char *str) {
    // 空字符串直接不是整数
    if (str == NULL || *str == '\0') {
        return 0;
    }

    // 第一位可以是正负号
    if (*str == '+' || *str == '-') {
        str++; // 跳过符号
        // 只有符号没有数字，也不是整数
        if (*str == '\0') {
            return 0;
        }
    }

    // 剩下的每一位必须都是数字
    while (*str != '\0') {
        if (!isdigit(*str)) {
            // 只要有一个不是数字
            return 0;
        }
        str++;
    }

    return 1; // 全部符合
}

void init(Stack *this) {
    this->count = 0;
    this->ptr = -1;
}

int push(Stack *this, int x) {
    if (this->count >= STACK_MAX_SIZE)
        return -1;
    this->arr[++this->ptr] = x;
    this->count++;
    return 0;
}

int pop(Stack *this) {
    if (this->count == 0)
        return -1;
    this->count--;
    return this->arr[this->ptr--];
}

_Bool isEmpty(Stack *this) {
    return this->count == 0;
}

int peek(Stack *this) {
    if (this->count == 0)
        return -1;
    return this->arr[this->ptr];
}

int evalRPN(char **tokens, int tokensSize) {
    if (tokensSize == 1)
        return atoi(tokens[0]);
    Stack stack = {};
    init(&stack);
    for (int i = 0; i < tokensSize; ++i) {
        char *str = *(tokens + i);
        //字符串是数字就压栈
        if (isInteger(str))
            push(&stack, atoi(str));
        else
        //不是数字，那就是符号，
        //弹出栈内两个元素进行计算，并把结果压栈
        {
            int imm2 = pop(&stack);
            int imm1 = pop(&stack);
            int result;
            //imm1 +操作符+imm2
            if (*str == '-')
                result = imm1 - imm2;
            else if (*str == '+')
                result = imm1 + imm2;
            else if (*str == '*')
                result = imm1 * imm2;
            else
                result = imm1 / imm2;
            push(&stack, result);
        }
    }
    return pop(&stack);
}

// int main() {
//
//     char * tokens[] = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
//     printf("%d\n",evalRPN(tokens,13));
//     return 0;
// }

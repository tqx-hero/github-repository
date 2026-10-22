//
// Created by Administrator on 2026/6/5.
//
/**
*
代码
测试用例
测试用例
测试结果
227. 基本计算器 II
中等
相关标签
premium lock icon
相关企业
给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。

整数除法仅保留整数部分。

你可以假设给定的表达式总是有效的。所有中间结果将在 [-231, 231 - 1] 的范围内。

注意：不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。



示例 1：

输入：s = "3+2*2"
输出：7
示例 2：

输入：s = " 3/2 "
输出：1
示例 3：

输入：s = " 3+5 / 2 "
输出：5


提示：

1 <= s.length <= 3 * 105
s 由整数和算符 ('+', '-', '*', '/') 组成，中间由一些空格隔开
s 表示一个 有效表达式
表达式中的所有整数都是非负整数，且在范围 [0, 231 - 1] 内
题目数据保证答案是一个 32-bit 整数
 * @return
 */
//用2个栈，1个压数字，另一个压运算符
//数字直接入栈
//运算符需要查看栈顶的运算符优先级是否大于等于要入栈的算符
//如果小于，直接入栈
//大于，就开始弹栈，每次弹出一个算符，就拿数字栈内的2个栈顶元素进行运算，运算完成后再放入栈内
//持续进行上述步骤，直到运算符栈空或者栈顶算符优先级小于当前算符。当前算符入栈
//持续进行上述步骤，直到遍历完成字符串
//最后把栈内剩余的算符弹栈，进行运算得出结果
#define STACK_MAX_SIZE 200
#define VOID void*
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define CALNUM int res = cal((int) pop(&numStack),\
    (int) pop(&numStack), top);\
    push(&numStack, (VOID) res);

//通用栈
typedef struct Stack {
    VOID arr[STACK_MAX_SIZE];
    int ptr;
    //函数指针，动态绑定结构体的函数入口
    // void* (*func)(void *);
} Stack;

void init(Stack *this) {
    this->ptr = -1;
}

void push(Stack *this, VOID x) {
    this->arr[++this->ptr] = x;
}

_Bool isEmpty(Stack *this) {
    return this->ptr == -1;
}

VOID pop(Stack *this) {
    return this->arr[this->ptr--];
}


VOID peek(Stack *this) {
    return this->arr[this->ptr];
}

int priority(char c) {
    int pri;
    switch (c) {
        case '+':
            pri = 0;
            break;
        case '-':
            pri = 0;
            break;
        case '*':
            pri = 1;
            break;
        case '/':
            pri = 1;
            break;
        default:
            pri = 0;
            break;
    }
    return pri;
}

int cal(int num1, int num2, char c) {
    int res;
    switch (c) {
        case '+':
            res = num1 + num2;
            break;
        case '-':
            res = num1 - num2;
            break;
        case '*':
            res = num1 * num2;
            break;
        case '/':
            res = num1 / num2;
            break;
        default:
            res = 0;
            break;
    }
    return res;
}

int calculate(char *s) {
    Stack numStack = {}, calStack = {};
    init(&numStack);
    init(&calStack);
    //加载字符串
    char c;
    for (int i = 0; (c = *(s + i)) != '\0';) {
        if (c == ' ') {
            i++;
            continue;
        }
        //如果是数字，就需要截取字符
        int begin = i;
        for (; (c = *(s + i)) != '\0' && isdigit(c); ++i);
        //j>i表明是数字
        if (i > begin) {
            int num = atoi(s + begin);
            push(&numStack, (VOID) num);
        }
        //i=begin,表明是算符
        else {
            //先查看字符栈是否存在更高或者等于该字符优先级的算符
            //栈不为空，需要迭代查看栈顶优先级是否大于等于当前算符
            while (!isEmpty(&calStack)) {
                char top = (char) peek(&calStack);
                //优先级更高，弹栈运算
                if (priority(top) >= priority(c)) {
                    pop(&calStack);
                    //进行运算：num1+操作符+num2
                    CALNUM
                }
                //优先级低，直接压栈
                else {
                    push(&calStack, (VOID) c);
                    break;
                }
            }
            if (isEmpty(&calStack))
                push(&calStack, (VOID) c);
            i++;
        }
    }
    //执行结束如果算符栈不为空，按顺序弹栈处理
    while (!isEmpty(&calStack)) {
        char top = (char) pop(&calStack);
        CALNUM
    }
    return (int) pop(&numStack);
}

// int main() {
//     // char *ca = "3+2*2";
//     char *ca = " 3/2 ";
//     printf("%d\n", calculate(ca));
//     return 0;
// }

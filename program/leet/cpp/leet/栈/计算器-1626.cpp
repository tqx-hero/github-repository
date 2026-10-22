//
// Created by Administrator on 2026/8/2.
//
/**
* 面试题 16.26. 计算器
中等
相关标签
premium lock icon
相关企业
提示
给定一个包含正整数、加(+)、减(-)、乘(*)、除(/)的算数表达式(括号除外)，计算其结果。

表达式仅包含非负整数，+， - ，*，/ 四种运算符和空格  。 整数除法仅保留整数部分。

示例 1：

输入："3+2*2"
输出：7
示例 2：

输入：" 3/2 "
输出：1
示例 3：

输入：" 3+5 / 2 "
输出：5
说明：

你可以假设所给定的表达式都是有效的。
请不要使用内置的库函数 eval。
 * @return
 */
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class Solution {
    bool shouldPop(const char top, const char cur) {

        if (cur == '+' || cur == '-')
            return true;
        if (cur == '*' || cur == '/')
            return top == '*' || top == '/';
        return false;
    }

    int doCalculate(const int x, const int y, const char z) {
        switch (z) {
            case '+':
                return x + y;
            case '-':
                return x - y;
            case '*':
                return x * y;
            case '/':
                return x / y;
            default:
                return 0;
        }
    }

    void doCalculate(stack<int> &numStack, stack<char> &charStack) {
        char chr = charStack.top();
        //如果栈顶运算符优先级大于等于当前运算符，需要弹栈计算
        charStack.pop();
        int first = numStack.top();
        numStack.pop();
        int second = numStack.top();
        numStack.pop();
        numStack.push(doCalculate(second, first, chr));
    }

    int strToInt(const vector<int> &nums, int &len) {
        int total = 0;
        for (int i = 0; i < len; i++) {
            total = total * 10 + nums[i];
        }
        len=0;
        return total;
    }

public:
    int calculate(string s) {
        stack<int> numStack;
        stack<char> charStack;
        vector<int> tmp(12);
        int len = 0;
        for (char ch: s) {
            if (ch == ' ') {
                if (len)
                    numStack.push(strToInt(tmp, len));
                continue;
            }
            if (ch >= '0' && ch <= '9') {
                tmp[len++] = ch - '0';
            } else {
                if (len)
                    numStack.push(strToInt(tmp, len));
                //如果字符是运算符
                while (!charStack.empty() && shouldPop(charStack.top(), ch))
                    doCalculate(numStack, charStack);
                charStack.push(ch);
            }
        }
        if (len)
            numStack.push(strToInt(tmp, len));
        while (!charStack.empty())
            doCalculate(numStack, charStack);
        return numStack.top();
    }
};

// int main() {
//     string s = "3+2* 2";
//     Solution sl;
//     cout << sl.calculate(s) << endl;
//     return 0;
// }

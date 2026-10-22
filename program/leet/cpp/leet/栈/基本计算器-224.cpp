//
// Created by Administrator on 2026/8/5.
//
/**
* 224. 基本计算器
困难
相关标签
premium lock icon
相关企业
给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。

注意:不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。



示例 1：

输入：s = "1 + 1"
输出：2
示例 2：

输入：s = " 2-1 + 2 "
输出：3
示例 3：

输入：s = "(1+(4+5+2)-3)+(6+8)"
输出：23


提示：

1 <= s.length <= 3 * 105
s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
s 表示一个有效的表达式
'+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
'-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
输入中不存在两个连续的操作符
每个数字和运行的计算将适合于一个有符号的 32位 整数
 * @return
 */
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class Solution {
    bool shouldPop(const char top, const char cur) {
        if (top == '(' || cur == '(')
            return false;
        if (cur == '+' || cur == '-')
            return true;
        if (cur == '*' || cur == '/')
            return top == '*' || top == '/';
        return false;
    }

    long long doCalculate(const long long x, const long long y, const char z) {
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

    void doCalculate(stack<long long> &numStack, stack<char> &charStack) {
        char chr = charStack.top();
        //如果栈顶运算符优先级大于等于当前运算符，需要弹栈计算
        charStack.pop();
        long long first = numStack.top();
        numStack.pop();
        long long second = numStack.top();
        numStack.pop();
        numStack.push(doCalculate(second, first, chr));
    }

    long long strToInt(const vector<int> &nums, int &len) {
        long long total = 0;
        for (int i = 0; i < len; i++)
            total = total * 10 + nums[i];
        len = 0;
        return total;
    }

    void updateNumberStack(stack<long long> &numberStack, vector<int> &tmp, int &len) {
        if (len)
            numberStack.push(strToInt(tmp, len));
    }

public:
    int calculate(string s) {
        stack<long long> numberStack;
        stack<char> charStack;
        int size = static_cast<int>(s.size()), i;
        vector<int> tmp(12);
        int len = 0;
        char prev = 0;
        for (i = 0; i < size; i++) {
            char ch = s[i];
            if (ch == ' ') {
                updateNumberStack(numberStack, tmp, len);
                continue;
            }
            //如果是数字，转换为数字
            if (ch >= '0' && ch <= '9') {
                //运用函数转换为数字
                tmp[len++] = ch - '0';
            }
            //如果是右括号，需要弹栈计算，直到弹出第一个左括号为止
            else if (ch == ')') {
                updateNumberStack(numberStack, tmp, len);
                while (charStack.top() != '(')
                    doCalculate(numberStack, charStack);
                charStack.pop();
            }
            //其余情况就是运算符以及(
            //此时需要根据优先级来确定是否要弹栈
            //1、 ( :直接入栈，不弹栈
            //2、 *、/ : 弹栈直到碰到(
            //3、 +、- : 栈顶为+或-时弹栈，直到碰到(
            else {
                updateNumberStack(numberStack, tmp, len);
                if (ch == '-' && (prev < '0' || prev > '9') && prev != ')')
                    numberStack.push(0);
                while (!charStack.empty() && shouldPop(charStack.top(), ch))
                    doCalculate(numberStack, charStack);
                charStack.push(ch);
            }
            prev = ch;
        }
        updateNumberStack(numberStack, tmp, len);
        while (!charStack.empty())
            doCalculate(numberStack, charStack);
        return static_cast<int>(numberStack.top());
    }
};

// int main() {
//     // std::string str_dec = "a2001, A Space Odyssey";
//     // std::string::size_type sz; // alias of size_t
//     // int i_dec = std::stoi(&str_dec[1], &sz);
//     // cout << i_dec << " : " << sz << endl;
//     // string s = "1-(     -2)";
//     // string s = " 2-1 + 2 ";
//     string s = "-2147483648";
//     // string s = "(1+(4+5+2)-3)+(6+8)";
//     Solution sl;
//     cout << sl.calculate(s) << endl;
//     return 0;
// }

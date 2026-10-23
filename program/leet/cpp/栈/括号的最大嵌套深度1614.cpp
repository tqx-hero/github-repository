//
// Created by Administrator on 2026/7/23.
//
/**
* 1614. 括号的最大嵌套深度
简单
相关标签
premium lock icon
相关企业
提示
给定 有效括号字符串 s，返回 s 的 嵌套深度。嵌套深度是嵌套括号的 最大 数量。



示例 1：

输入：s = "(1+(2*3)+((8)/4))+1"

输出：3

解释：数字 8 在嵌套的 3 层括号中。

示例 2：

输入：s = "(1)+((2))+(((3)))"

输出：3

解释：数字 3 在嵌套的 3 层括号中。

示例 3：

输入：s = "()(())((()()))"

输出：3



提示：

1 <= s.length <= 100
s 由数字 0-9 和字符 '+'、'-'、'*'、'/'、'('、')' 组成
题目数据保证括号字符串 s 是 有效的括号字符串
 * @return
 */
#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    int maxDepth(string s) {
        stack<char> stack;
        int maxCount = 0, cnt = 0;
        for (char &ch: s) {
            if (ch == '(') {
                cnt += stack.size();
                maxCount = max(maxCount, cnt);
                cnt = 0;
                stack.push(ch);
            } else if (ch == ')' && !stack.empty()) {
                cnt++;
                stack.pop();
            }
        }
        maxCount = max(maxCount, cnt);
        return maxCount;
    }
};

// int main() {
//     string s ="(1)+((2))+(((3)))";
//     // string s = "(1+(2*3)+((8)/4))+1";
//     Solution sl;
//     cout << sl.maxDepth(s) << endl;
//     return 0;
// }

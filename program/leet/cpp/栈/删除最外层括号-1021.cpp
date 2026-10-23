//
// Created by Administrator on 2026/8/6.
//
/**
* 1021. 删除最外层的括号
简单
相关标签
premium lock icon
相关企业
提示
有效括号字符串为空 ""、"(" + A + ")" 或 A + B ，其中 A 和 B 都是有效的括号字符串，+ 代表字符串的连接。

例如，""，"()"，"(())()" 和 "(()(()))" 都是有效的括号字符串。
如果有效字符串 s 非空，且不存在将其拆分为 s = A + B 的方法，我们称其为原语（primitive），其中 A 和 B 都是非空有效括号字符串。

给出一个非空有效字符串 s，考虑将其进行原语化分解，使得：s = P_1 + P_2 + ... + P_k，其中 P_i 是有效括号字符串原语。

对 s 进行原语化分解，删除分解中每个原语字符串的最外层括号，返回 s 。



示例 1：

输入：s = "(()())(())"
输出："()()()"
解释：
输入字符串为 "(()())(())"，原语化分解得到 "(()())" + "(())"，
删除每个部分中的最外层括号后得到 "()()" + "()" = "()()()"。
示例 2：

输入：s = "(()())(())(()(()))"
输出："()()()()(())"
解释：
输入字符串为 "(()())(())(()(()))"，原语化分解得到 "(()())" + "(())" + "(()(()))"，
删除每个部分中的最外层括号后得到 "()()" + "()" + "()(())" = "()()()()(())"。
示例 3：

输入：s = "()()"
输出：""
解释：
输入字符串为 "()()"，原语化分解得到 "()" + "()"，
删除每个部分中的最外层括号后得到 "" + "" = ""。


提示：

1 <= s.length <= 105
s[i] 为 '(' 或 ')'
s 是一个有效括号字符串
 * @return
 */
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    string removeOuterParentheses(string s) {
        string result;
        stack<int> indexStack;
        int size = static_cast<int>(s.length());
        for (int i = 0; i < size; i++) {
            //如果是(,直接入栈
            if (s[i] == '(') {
                indexStack.push(i);
                continue;
            }
            //如果是),判断当前栈是否还剩1个，如果是，则需要统计(栈顶,当前位置i)区间的字符，放入result
            //如果超过1个，直接弹栈
            if (indexStack.size() == 1) {
                for (int k = indexStack.top() + 1; k < i; k++)
                    result.push_back(s[k]);
            }
            indexStack.pop();
        }
        return result;
    }
};
//
// int main() {
//     string str("(()())(())");
//     Solution sl;
//     cout << sl.removeOuterParentheses(str) << endl;
//     return 0;
// }

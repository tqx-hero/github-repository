//
// Created by Administrator on 2026/8/20.
//
/**
* 678. 有效的括号字符串
中等
相关标签
premium lock icon
相关企业
提示
给你一个只包含三种字符的字符串，支持的字符类型分别是 '('、')' 和 '*'。请你检验这个字符串是否为有效字符串，如果是 有效 字符串返回 true 。

有效 字符串符合如下规则：

任何左括号 '(' 必须有相应的右括号 ')'。
任何右括号 ')' 必须有相应的左括号 '(' 。
左括号 '(' 必须在对应的右括号之前 ')'。
'*' 可以被视为单个右括号 ')' ，或单个左括号 '(' ，或一个空字符串 ""。


示例 1：

输入：s = "()"
输出：true
示例 2：

输入：s = "(*)"
输出：true
示例 3：

输入：s = "(*))"
输出：true


提示：

1 <= s.length <= 100
s[i] 为 '('、')' 或 '*'
 * @return
 */
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    bool checkValidString(string s) {
        //定义2个栈，分别存放左括号与*下标
        stack<int> left_index_stack, any_index_stack;
        int size = static_cast<int>(s.size());
        for (int i = 0; i < size; ++i) {
            char ch = s[i];
            //如果字符是左括号或者*，下标直接入栈
            if (ch == '(')
                left_index_stack.push(i);
            else if (ch == '*')
                any_index_stack.push(i);
                //如果是右括号，那就先弹左括号栈
            else if (!left_index_stack.empty()) {
                left_index_stack.pop();
                //左括号不存在，弹*栈
            } else if (!any_index_stack.empty())
                any_index_stack.pop();
            else
                //2个栈都没有，说明这个右括号前面没有与之匹配的左括号，返回false
                return false;
        }
        //上述筛选一轮，可能会出现未匹配的左括号
        //这时需要在栈顶下标的那个左括号后面开始，以*来匹配每一个栈顶左括号
        //这里要注意当作右括号使用的*下标必须要时刻大于左括号下标才行
        //这里用了一个临时栈来存放大于左括号栈顶下标的那些*
        stack<int> temp;
        while (!left_index_stack.empty()) {
            int cur_idx = left_index_stack.top();
            left_index_stack.pop();
            //取出所有比当前左括号靠后的星号
            int any_idx;
            while (!any_index_stack.empty() && (any_idx = any_index_stack.top()) > cur_idx) {
                temp.push(any_idx);
                any_index_stack.pop();
            }
            //当临时栈有值，说明有*可以当作右括号匹配左括号，弹栈并进行下一轮
            if (!temp.empty())
                temp.pop();
                //如果临时栈空，说明没有比左括号栈顶还要靠后的*来匹配，返回false
            else
                return false;
        }
        return true;
    }
};

// int main() {
//     //"(((((*(*********((*(((((****"
//     // string s = "(((((*(()((((*((**(((()()*)()()()*((((**)())*)*)))))))(())(()))())((*()()(((()((()*(())*(()**)()(())";
//     string s = "(*))";
//     // string s = "(*)";
//     Solution sl;
//     cout << sl.checkValidString(s) << endl;
//     return 0;
// }

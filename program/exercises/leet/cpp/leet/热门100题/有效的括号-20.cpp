/**
 * 20. 有效的括号
已解答
简单
相关标签
premium lock icon
相关企业
提示
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。
 

示例 1：

输入：s = "()"

输出：true

示例 2：

输入：s = "()[]{}"

输出：true

示例 3：

输入：s = "(]"

输出：false

示例 4：

输入：s = "([])"

输出：true

示例 5：

输入：s = "([)]"

输出：false

 

提示：

1 <= s.length <= 104
s 仅由括号 '()[]{}' 组成
 */
#include <string>
#include <stack>
#include <iostream>
using namespace std;
class Solution {
    bool top_match(char ch,stack<char>& stk){
        if(stk.empty())
            return false;
        switch (ch)
        {
        case ']':
            return stk.top() == '[';
        case '}':
            return stk.top() == '{';
        case ')':
            return stk.top() == '(';
        default:
            return false;
        }
    }
public:
    bool isValid(string s) {
        stack<char> cache;
        for(auto ch: s){
            //如果为左括号，入栈
            if(ch == '(' || ch == '{' || ch == '[')
                cache.push(ch);
            else if(!top_match(ch,cache))
                return false;
            else
                cache.pop();
        }
        return cache.empty();
    }
};
// int main(){
//     string s = "()[]{";
//     Solution sl;
//     cout << sl.isValid(s) << endl;
//     return 0;
// }
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
#include <stack>
#include <iostream>
using namespace std;

class Solution
{

    bool match(char c1, char c2)
    {
        return c1 == '(' && c2 == ')' ||
               (c1 == '[' && c2 == ']') ||
               (c1 == '{' && c2 == '}');
    }

public:
    bool isValid(string s)
    {
        stack<char> stk;
        for(char ch: s){
            if(ch == '(' || ch =='[' || ch == '{')
                stk.push(ch);
            else if(stk.empty() || !match(stk.top(),ch))
                return false;
            else 
                stk.pop();
        }
        return stk.empty();
    }
};

// int main()
// {
//     return 0;
// }
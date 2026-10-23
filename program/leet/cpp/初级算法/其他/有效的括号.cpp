//
// Created by Administrator on 2026/8/16.
//
/**
* 有效的括号
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

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

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnbcaj/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
    bool isMatch(stack<char> &stk, char ch) {
        if (stk.empty())
            return false;
        char top_ch = stk.top();
        return (ch == ')' && top_ch == '(') || (ch == ']' && top_ch == '[') || (ch == '}' && top_ch == '{');
    }

public:
    bool isValid(string s) {
        stack<char> stk;
        for (char ch: s) {
            if (ch == '(' || ch == '[' || ch == '{')
                stk.push(ch);
            else if (isMatch(stk, ch))
                stk.pop();
            else
                return false;
        }
        return stk.empty();
    }
};

// int main() {
//     string s =  "([)]";
//     Solution sl;
//     cout << sl.isValid(s) << endl;
//     return 0;
// }

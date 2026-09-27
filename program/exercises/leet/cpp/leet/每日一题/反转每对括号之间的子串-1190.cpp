/**
 * 1190. 反转每对括号间的子串
中等
相关标签
premium lock icon
相关企业
提示
给出一个字符串 s（仅含有小写英文字母和括号）。

请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的结果。

注意，您的结果中 不应 包含任何括号。



示例 1：

输入：s = "(abcd)"
输出："dcba"
示例 2：

输入：s = "(u(love)i)"
输出："iloveu"
解释：先反转子字符串 "love" ，然后反转整个字符串。
示例 3：

输入：s = "(ed(et(oc))el)"
输出："leetcode"
解释：先反转子字符串 "oc" ，接着反转 "etco" ，然后反转整个字符串。


提示：

1 <= s.length <= 2000
s 中只有小写英文字母和括号
题目测试用例确保所有括号都是成对出现的
 */
#include <string>
#include <iostream>
#include <deque>
#include <stack>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string reverseParentheses(string s)
    {
        string ret;
        deque<string> str_stk;
        int i, size = static_cast<int>(s.size()), left_cnt = 0;
        for (i = 0; i < size; ++i)
        {
            if (s[i] == ')')
            {
                // 统计，弹栈
                string temp_str;
                do
                {
                    string &str = str_stk.back();
                    if (str == "(")
                    {
                        str_stk.pop_back();
                        break;
                    }
                    temp_str = str + temp_str;
                    str_stk.pop_back();
                } while (true);
                reverse(temp_str.begin(), temp_str.end());
                str_stk.push_back(temp_str);
                continue;
            }
            // if(s[i] == '(')
            //   left_cnt++;
            str_stk.push_back(string(1,s[i]));
        }
        for (auto &str : str_stk)
            ret += str;
        return ret;
    }
};

// int main()
// {
//     // string s = "(abcd)";
//     // string s = "(u(love)i)";
//     string s = "(ed(et(oc))el)";
//     Solution sl;
//     cout << sl.reverseParentheses(s) << endl;
//     return 0;
// }
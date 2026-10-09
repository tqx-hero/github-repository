/**
 * 1541. 平衡括号字符串的最少插入次数
中等
相关标签
premium lock icon
相关企业
提示
给你一个括号字符串 s ，它只包含字符 '(' 和 ')' 。一个括号字符串被称为平衡的当它满足：

任何左括号 '(' 必须对应两个连续的右括号 '))' 。
左括号 '(' 必须在对应的连续两个右括号 '))' 之前。
比方说 "())"， "())(())))" 和 "(())())))" 都是平衡的， ")()"， "()))" 和 "(()))" 都是不平衡的。

你可以在任意位置插入字符 '(' 和 ')' 使字符串平衡。

请你返回让 s 平衡的最少插入次数。



示例 1：

输入：s = "(()))"
输出：1
解释：第二个左括号有与之匹配的两个右括号，但是第一个左括号只有一个右括号。我们需要在字符串结尾额外增加一个 ')' 使字符串变成平衡字符串 "(())))" 。
示例 2：

输入：s = "())"
输出：0
解释：字符串已经平衡了。
示例 3：

输入：s = "))())("
输出：3
解释：添加 '(' 去匹配最开头的 '))' ，然后添加 '))' 去匹配最后一个 '(' 。
示例 4：

输入：s = "(((((("
输出：12
解释：添加 12 个 ')' 得到平衡字符串。
示例 5：

输入：s = ")))))))"
输出：5
解释：在字符串开头添加 4 个 '(' 并在结尾添加 1 个 ')' ，字符串变成平衡字符串 "(((())))))))" 。


提示：

1 <= s.length <= 10^5
s 只包含 '(' 和 ')' 。
 */
#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
    int minInsertions(string s)
    {
        int num = 0, left_num = 0, right_num = 0;
        for (auto ch : s)
        {
            if (ch == '(')
            {
                // 如果右括号存在，右括号必定缺少1个，总计数+1
                if (right_num == 1)
                {
                    num++;
                    // 右括号归0，左括号-1
                    right_num = 0;
                }
                else
                    left_num++;
            }
            else
            {
                right_num++;
                if (left_num == 0)
                {
                    // 左括号不存在，就要num+1，加入左括号
                    num++;
                    left_num++;
                }
                // 如果右括号个数等于2个了，就需要减去一个左括号,右括号归零
                if (right_num == 2)
                {
                    left_num--;
                    right_num = 0;
                }
            }
        }
        // 最后的结果分类讨论
        // 1、只存在left，right=0，只需要再补充2*left个括号
        // 2、left存在，right有且只有1个
        // 3、不存在只有right的情况
        while (left_num)
        {
            if (!right_num)
            {
                num += 2 * left_num;
                break;
            }
            else
            {
                // right存在也只会存在1个,先补齐这1个
                right_num = 0;
                left_num--;
                num++;
            }
        }

        return num;
    }
};

int main()
{
    // string s = "(()))";
    // string s = "())";
    // string s = "))())(";
    // string s = "((((((";
    string s = ")))))))";
    Solution sl;
    cout << sl.minInsertions(s) << endl;
    return 0;
}
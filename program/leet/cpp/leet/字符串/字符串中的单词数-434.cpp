/**
 * 434. 字符串中的单词数
简单
相关标签
premium lock icon
相关企业
统计字符串中的单词个数，这里的单词指的是连续的不是空格的字符。

请注意，你可以假定字符串里不包括任何不可打印的字符。

示例:

输入: "Hello, my name is John"
输出: 5
解释: 这里的单词是指连续的不是空格的字符，所以 "Hello," 算作 1 个单词。
 */
#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
    int countSegments(string s)
    {
        // 以空格为分隔符，统计子串的个数
        int count = 0, size = static_cast<int>(s.size()), cur_size = 0;
        for (auto ch : s)
        {
            if (ch == ' ')
            {
                if (cur_size)
                    count++;
                cur_size = 0;
            }
            else
                cur_size++;
        }
        return cur_size ? count + 1 : count;
    }
};

// int main()
// {
//     string s = "Hello, my name is John";
//     Solution sl;
//     cout << sl.countSegments(s) << endl;
//     return 0;
// }
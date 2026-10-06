/**
 * 409. 最长回文串
简单
相关标签
premium lock icon
相关企业
给定一个包含大写字母和小写字母的字符串 s ，返回 通过这些字母构造成的 最长的 回文串 的长度。

在构造过程中，请注意 区分大小写 。比如 "Aa" 不能当做一个回文字符串。



示例 1:

输入:s = "abccccdd"
输出:7
解释:
我们可以构造的最长的回文串是"dccaccd", 它的长度是 7。
示例 2:

输入:s = "a"
输出:1
解释：可以构造的最长回文串是"a"，它的长度是 1。


提示:

1 <= s.length <= 2000
s 只由小写 和/或 大写英文字母组成
 */
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int longestPalindrome(string s)
    {
        array<int, 64> hash_map{0};
        // 统计词频
        for_each(s.begin(), s.end(), [&hash_map](const char ch)
                 { hash_map[ch - 'A']++; });
        int ret = 0, i, single = 0;
        for (i = 0; i < 64; ++i)
        {
            int cnt = hash_map[i];
            if (cnt == 0)
                continue;
            if (cnt % 2)
            {
                single++;
                ret += cnt - 1;
            }
            else
                ret += cnt;
        }
        return single ? ret + 1 : ret;
    }
};

// int main()
// {
//     return 0;
// }
/**
 * 1422. 分割字符串的最大得分
简单
相关标签
premium lock icon
相关企业
提示
给你一个由若干 0 和 1 组成的字符串 s ，请你计算并返回将该字符串分割成两个 非空 子字符串（即 左 子字符串和 右 子字符串）所能获得的最大得分。

「分割字符串的得分」为 左 子字符串中 0 的数量加上 右 子字符串中 1 的数量。



示例 1：

输入：s = "011101"
输出：5
解释：
将字符串 s 划分为两个非空子字符串的可行方案有：
左子字符串 = "0" 且 右子字符串 = "11101"，得分 = 1 + 4 = 5
左子字符串 = "01" 且 右子字符串 = "1101"，得分 = 1 + 3 = 4
左子字符串 = "011" 且 右子字符串 = "101"，得分 = 1 + 2 = 3
左子字符串 = "0111" 且 右子字符串 = "01"，得分 = 1 + 1 = 2
左子字符串 = "01110" 且 右子字符串 = "1"，得分 = 2 + 1 = 3
示例 2：

输入：s = "00111"
输出：5
解释：当 左子字符串 = "00" 且 右子字符串 = "111" 时，我们得到最大得分 = 2 + 3 = 5
示例 3：

输入：s = "1111"
输出：3


提示：

2 <= s.length <= 500
字符串 s 仅由字符 '0' 和 '1' 组成。
 */
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
// 1.统计1的个数
// 2.再次遍历字符串，记录左边子串0的个数，分别计算得分，维持最大值，返回
class Solution
{
public:
    int maxScore(string s)
    {
        int size = static_cast<int>(s.size()), count_one = 0;
        for (auto ch : s)
            if (ch == '1')
                count_one++;
        // 如果s仅包含0或者1，得分永远是size-1
        if (count_one == 0 || count_one == size)
            return size - 1;
        int ret = 0, left_zero = 0, left_one = 0, i;
        for (i = 0; i < size - 1; ++i)
        {
            if (s[i] == '0')
                left_zero++;
            else
                left_one++;
            ret = max(left_zero + (count_one - left_one), ret);
        }
        return ret;
    }
};

// int main()
// {
//     // string s = "011101";
//     // string s = "00111";
//     string s = "11100";
//     // string s = "1111";
//     // string s = "0100";
//     Solution sl;
//     cout << sl.maxScore(s) << endl;
//     return 0;
// }
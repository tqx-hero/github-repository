/**
 * 763. 划分字母区间
中等
相关标签
premium lock icon
相关企业
提示
给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。例如，字符串 "ababcc" 能够被分为 ["abab", "cc"]，但类似 ["aba", "bcc"] 或 ["ab", "ab", "cc"] 的划分是非法的。

注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。

返回一个表示每个字符串片段的长度的列表。



示例 1：
输入：s = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。
示例 2：

输入：s = "eccbbbbdec"
输出：[10]


提示：

1 <= s.length <= 500
s 仅由小写英文字母组成
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <array>
using namespace std;
// 需要统计每个字母出现的开始，结束下标.
// 以第一个首字母的[left,end]下标区间，往其中添加字符，在添加的同时还要更新它的右边界
// 即选取这个区间内字符最大的右边界作为右边界right，得到的区间[left,right]即为这个最小满足条件的区间
// right+1开始作为首字母继续重复以上步骤，直到字符串结束
class Solution
{
public:
    vector<int> partitionLabels(string s)
    {
        int size = static_cast<int>(s.size());
        // 首位字母相同，返回这一个区间
        if (s[0] == s[size - 1])
            return vector<int>{size};
        vector<int> ret;
        array<int, 26> hash_map{-1};
        int i;
        // 统计每个字符的最晚出现下标
        for (i = 0; i < size; ++i)
            hash_map[s[i] - 'a'] = i;
        for (i = 0; i < size;)
        {
            int left = i + 1, right = hash_map[s[i] - 'a'];
            // 遍历这个区间,更新右边界，只要最大的那个下标
            for (; left < right; ++left)
                right = max(right, hash_map[s[left] - 'a']);
            ret.push_back(right - i + 1);
            //更新i
            i = right + 1;
        }
        return ret;
    }
};

// int main()
// {
//     // string s = "ababcbacadefegdehijhklij";
//     string s = "eccbbbbdec";
//     Solution sl;
//     const auto &vc = sl.partitionLabels(s);
//     for_each(vc.begin(), vc.end(), [](const int &x)
//              { cout << x << " "; });
//     cout << endl;
//     return 0;
// }
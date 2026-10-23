//
// Created by 田庆新 on 2026/9/6.
//
/**
* 115. 不同的子序列
困难
相关标签
premium lock icon
相关企业
给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数。

测试用例保证结果在 32 位有符号整数范围内。



示例 1：

输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
rabbbit
rabbbit
rabbbit
示例 2：

输入：s = "babgbag", t = "bag"
输出：5
解释：
如下所示, 有 5 种可以从 s 中得到 "bag" 的方案。
babgbag
babgbag
babgbag
babgbag
babgbag


提示：

1 <= s.length, t.length <= 1000
s 和 t 由英文字母组成
 * @return
 */
#include <string>
#include <iostream>
#include <vector>
#include <array>
using namespace std;
//TODO
class Solution {
public:
    int numDistinct(string s, string t) {
        int s_size = static_cast<int>(s.size()), t_size = static_cast<int>(t.size());
        //边界判断
        if (s_size < t_size)
            return 0;
        //英文字母分大小写，所以设置桶的大小为64足够
        array<vector<int>, 64> bucket;
        //遍历正文串，获取每个字符的个数，并且统计好下标
        int i;
        for (i = 0; i < s_size; ++i)
            bucket[s[i] - 'A'].push_back(i);
        //倒序遍历模式串t，根据字符的出现次数以及下标来记录可能出现的子串次数
        int cnt = 0;
        // for (i = t_size - 1; i >= 0; --i) {
        //
        // }
        return 0;
    }
};

// int main() {
//     string s = "rabbbit", t = "rabbit";
//     Solution sl;
//     cout << sl.numDistinct(s, t) << endl;
//     return 0;
// }

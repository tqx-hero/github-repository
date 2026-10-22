//
// Created by Administrator on 2026/8/14.
//
/**
* 3090. 每个字符最多出现两次的最长子字符串
简单
相关标签
premium lock icon
相关企业
提示
给你一个字符串 s ，请找出满足每个字符最多出现两次的最长子字符串，并返回该子字符串的 最大 长度。



示例 1：

输入： s = "bcbbbcba"

输出： 4

解释：

以下子字符串长度为 4，并且每个字符最多出现两次："bcbbbcba"。

示例 2：

输入： s = "aaaa"

输出： 2

解释：

以下子字符串长度为 2，并且每个字符最多出现两次："aaaa"。



提示：

2 <= s.length <= 100
s 仅由小写英文字母组成。
 * @return
 */
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int maximumLengthSubstring(string s) {
        int buckets[26]{0}, total_size = 2;
        string::iterator str_end = s.end(), left = s.begin(), right;
        buckets[*left - 'a']++;
        for (right = left + 1; right != str_end; ++right) {
            //当放入右指针的值超过2个时,统计当前长度，左指针右移，直到移除当前元素值
            int cur_index = *right - 'a';
            if (++buckets[cur_index] > 2) {
                total_size = std::max(total_size, static_cast<int>(right - left));
                //左指针右移，直到移出*right为止
                do
                    buckets[*left - 'a']--;
                while (*left++ != *right);
            }
        }
        return std::max(total_size, static_cast<int>(right - left));
    }
};

// int main() {
//     string s = "aaaa";
//     // string s = "bcbbbcba";
//     Solution sl;
//     cout << sl.maximumLengthSubstring(s) << endl;
//     return 0;
// }

//
// Created by 田庆新 on 2026/8/28.
//
/**
* 438. 找到字符串中所有字母异位词
中等
相关标签
premium lock icon
相关企业
给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。



示例 1:

输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
 示例 2:

输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。


提示:

1 <= s.length, p.length <= 3 * 104
s 和 p 仅包含小写字母
 * @return
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <array>
using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int s_size = static_cast<int>(s.size()), p_size = static_cast<int>(p.size());
        vector<int> ret;
        //p长度超过s必定不满足要求
        if (p_size > s_size)
            return ret;
        //使用一个哈希表保存p的词频,用来遍历s时做参照
        array<int, 26> p_bucket{0};
        for (char ch: p)
            p_bucket[ch - 'a']++;
        int left = 0, right = left;
        //统计每一时刻的s累计词频
        array<int, 26> cur_bucket{0};
        for (; right < s_size;) {
            char ch = s[right];
            int cnt = p_bucket[ch - 'a'];
            //如果p不存在字符ch,需要跳过这段区间，从right指针的下一个位置开始统计
            if (cnt == 0) {
                //重置s计数
                cur_bucket.fill(0);
                left = ++right;
                continue;
            }
            //p存在该字符，先将其计数+1
            cur_bucket[ch - 'a']++;
            //如果出现当前的字符ch计数超过了p中ch的个数，需要移动左指针，更新计数直到ch数量等于p中ch数量
            //同时这里只会移动左指针，窗口大小减小，必然会小于p长度。
            //怎么也不会进入下面的if (right - left == p_size - 1)判断
            while (cnt < cur_bucket[ch - 'a'])
                cur_bucket[s[left++] - 'a']--;
            //长度等于p的长度时，且能走到这里，必然符合条件，记录并移动指针
            if (right - left == p_size - 1) {
                ret.push_back(left);
                //左指针前移一格，去掉一个计数
                cur_bucket[s[left++] - 'a']--;
            }
            ++right;
        }
        return ret;
    }
};

// int main() {
//     string s = "abab", p = "ab";
//     // string s = "cbaebabacd", p = "abc";
//     Solution sl;
//     const auto &anagrams = sl.findAnagrams(s, p);
//     for_each(anagrams.begin(), anagrams.end(), [](const int x) {
//         cout << x << " ";
//     });
//     cout << endl;
//     return 0;
// }

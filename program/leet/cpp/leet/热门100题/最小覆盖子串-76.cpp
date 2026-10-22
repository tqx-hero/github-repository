//
// Created by Administrator on 2026/8/31.
//
/**
* 76. 最小覆盖子串
困难
相关标签
premium lock icon
相关企业
提示
给定两个字符串 s 和 t，长度分别是 m 和 n，返回 s 中的 最短窗口 子串，使得该子串包含 t 中的每一个字符（包括重复字符）。如果没有这样的子串，返回空字符串 ""。

测试用例保证答案唯一。



示例 1：

输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
示例 2：

输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。
示例 3:

输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。


提示：

m == s.length
n == t.length
1 <= m, n <= 105
s 和 t 由英文字母组成


进阶：你能设计一个在 O(m + n) 时间内解决此问题的算法吗？
 * @return
 */
#include <string>
#include <iostream>
#include <array>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int s_size = static_cast<int>(s.size()), t_size = static_cast<int>(t.size());
        if (t_size > s_size)
            return "";
        array<int, 64> t_bucket{0}, s_bucket{0};
        //统计模式串t的词频
        for (char t_ch: t)
            t_bucket[t_ch - 'A']++;
        //遍历s，同时将字符出现次数记录下来
        int min_len = s_size + 1, begin_index = -1, valid_cnt = 0, left = 0, right = 0;
        for (; right < s_size; ++right) {
            char ch = s[right];
            //如果字符是存在模式串中，且数量还未超过模式串，增加一个有效计数
            if (s_bucket[ch - 'A']++ < t_bucket[ch - 'A'])
                valid_cnt++;
            //如果有效计数等于t_size，即[left,right]区间的词频满足模式串.
            //需要left++缩小范围，直到有效计数<t_size，记录范围为[left-1,right]
            if (valid_cnt == t_size) {
                while (valid_cnt == t_size) {
                    char left_ch = s[left++];
                    if (s_bucket[left_ch - 'A']-- == t_bucket[left_ch - 'A'])
                        valid_cnt--;
                }
                //记录[left-1,right]范围满足要求
                int len = right - (left - 1) + 1;
                if (len < min_len) {
                    min_len = len;
                    begin_index = left - 1;
                }
            }
        }
        return begin_index == -1 ? "" : string{s.begin() + begin_index, s.begin() + begin_index + min_len};
    }
};

// int main() {
//     string s = "a", t = "b";
//     // string s = "a", t = "a";
//     // string s = "ADOBECODEBANC", t = "ABC";
//     Solution sl;
//     cout << sl.minWindow(s, t) << endl;
//     return 0;
// }

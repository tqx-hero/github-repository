//
// Created by 田庆新 on 2026/8/29.
//
/**
* 3. 无重复字符的最长子串
已解答
中等
相关标签
premium lock icon
相关企业
提示
给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。



示例 1:

输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
示例 2:

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。


提示：

0 <= s.length <= 105
s 由英文字母、数字、符号和空格组成
 * @return
 */
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ret = 0, left = 0, right = 0, size = static_cast<int>(s.length());
        unordered_map<uint8_t, int> bucket;
        for (; right < size; ++right) {
            char ch = s[right];
            if (++bucket[ch] > 1) {
                //桶中如果已经存在该元素，需要记录当前桶的size，
                ret = max(ret, right - left);
                //移动左指针，直到这个字符不再出现
                while (bucket[ch] > 1)
                    bucket[s[left++]]--;
            }
        }
        return max(ret, right - left);
    }
};

// int main() {
//     string s =  "pwwkew";
//     // string s = "abcabcbb";
//     Solution sl;
//     cout << sl.lengthOfLongestSubstring(s) << endl;
//     return 0;
// }

//
// Created by Administrator on 2026/8/10.
//
/**
* 有效的字母异位词
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的 字母异位词。 
示例 1:
输入:
 s = "anagram", t = "nagaram"
输出:
 true
示例 2:
输入:
 s = "rat", t = "car"
输出: false 
提示:
• 1 <= s.length, t.length <= 5 * 104
• s 和 t 仅包含小写字母 
进阶: 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
 * @return
 */
#include <string>
using namespace std;
//统计词频，相同则true，不同则false
// class Solution {
// public:
//     bool isAnagram(string s, string t) {
//         int s_buckets[26]{0}, t_buckets[26]{0};
//         for (auto sch: s)
//             s_buckets[sch - 'a']++;
//         for (auto tch: t)
//             t_buckets[tch - 'a']++;
//         for (int i = 0; i < 26; i++)
//             if (s_buckets[i] != t_buckets[i])
//                 return false;
//         return true;
//     }
// };
//首先判断长度是否相同，不相同直接false
//再统计其中一个数组的词频。
//遍历另一个数组，减去其中的对应字符统计的个数，当不够减时，说明字符不完全匹配，返回false，否则为true
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size())
            return false;
        int s_buckets[26]{0};
        for (auto sch: s)
            s_buckets[sch - 'a']++;
        for (auto tch: t) {
            if (s_buckets[tch - 'a']-- <= 0)
                return false;
        }
        return true;
    }
};

// int main() {
//     return 0;
// }

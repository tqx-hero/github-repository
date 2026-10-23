/**
 * 345. 反转字符串中的元音字母
简单
相关标签
premium lock icon
相关企业
给你一个字符串 s ，仅反转字符串中的所有元音字母，并返回结果字符串。

元音字母包括 'a'、'e'、'i'、'o'、'u'，且可能以大小写两种形式出现不止一次。



示例 1：

输入：s = "IceCreAm"

输出："AceCreIm"

解释：

s 中的元音是 ['I', 'e', 'e', 'A']。反转这些元音，s 变为 "AceCreIm".

示例 2：

输入：s = "leetcode"

输出："leotcede"



提示：

1 <= s.length <= 3 * 105
s 由 可打印的 ASCII 字符组成
 */
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string reverseVowels(string s)
    {
        array<int, 128> hash_map{0};
        hash_map['A'] = 1;
        hash_map['E'] = 1;
        hash_map['I'] = 1;
        hash_map['O'] = 1;
        hash_map['U'] = 1;
        hash_map['a'] = 1;
        hash_map['e'] = 1;
        hash_map['i'] = 1;
        hash_map['o'] = 1;
        hash_map['u'] = 1;

        int left, right, size = static_cast<int>(s.size());
        for (left = 0, right = size - 1; left < right; ++left, --right)
        {
            while (left < right && !hash_map[s[left]])
                left++;
            while (left < right && !hash_map[s[right]])
                right--;
            if (left < right)
                swap(s[left], s[right]);
        }
        return s;
    }
};

// int main()
// {
//     // string s = "IceCreAm";
//     // string s = "leetcode";
//     string s = "a.";
//     Solution sl;
//     cout << sl.reverseVowels(s) << endl;
//     return 0;
// }
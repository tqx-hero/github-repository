//
// Created by Administrator on 2026/8/11.
//
/**
* 实现 strStr()
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。

  

示例 1：

输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。
示例 2：

输入：haystack = "leetcode", needle = "leeto"
输出：-1
解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。
  

提示：

1 <= haystack.length, needle.length <= 104
haystack 和 needle 仅由小写英文字符组成

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnr003/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <iostream>
#include <string>
using namespace std;

class Solution {
    //获取模式串中最后出现的字符位置
    void get_bad_words_array(string &model_str, int *bad_words) {
        size_t size = model_str.size();
        for (int i = 0; i < size; i++)
            bad_words[model_str[i] - 'a'] = i;
    }

public:
    int strStr(string haystack, string needle) {
        int hay_size = static_cast<int>(haystack.size()), n_size = static_cast<int>(needle.size());
        //如果长度超出，直接返回
        if (n_size > hay_size)
            return -1;
        //使用BM算法的坏字符匹配规则
        int bad_words[26];
        std::fill_n(bad_words, 26, -1);
        //加载模式串坏字符数组
        get_bad_words_array(needle, bad_words);
        //遍历正文串，根据BM算法的规则进行匹配，匹配顺序为从右往左
        for (int i = n_size - 1; i < hay_size;) {
            //从后往前遍历，逐个字符匹配
            int j = n_size - 1, k = i;
            for (; j >= 0 && haystack[k] == needle[j]; k--, j--);
            //j<0,说明匹配成功，返回结果为i-模式串长度+1
            if (j == -1)
                return i - n_size + 1;
            //如果j大于0，表明没有完全匹配，查找与正文串k下标相同的字符出现在模式串中的最后位置
            int last_index = bad_words[haystack[k] - 'a'];
            if (last_index == -1)
                i = k + n_size;
            else if (last_index > j)
                i++;
            else
                i = k + (n_size - 1 - last_index);
        }
        return -1;
    }
};

// int main() {
//     string haystack = "hello", needle = "ll";
//     // string haystack = "leetcode", needle = "leeto";
//     // string haystack = "sadbutsad", needle = "sad";
//     Solution sl;
//     cout << sl.strStr(haystack, needle) << endl;
//     return 0;
// }

/**
 * 500. 键盘行
简单
相关标签
premium lock icon
相关企业
给你一个字符串数组 words ，只返回可以使用在 美式键盘 同一行的字母打印出来的单词。键盘如下图所示。

请注意，字符串 不区分大小写，相同字母的大小写形式都被视为在同一行。

美式键盘 中：

第一行由字符 "qwertyuiop" 组成。
第二行由字符 "asdfghjkl" 组成。
第三行由字符 "zxcvbnm" 组成。
American keyboard



示例 1：

输入：words = ["Hello","Alaska","Dad","Peace"]

输出：["Alaska","Dad"]

解释：

由于不区分大小写，"a" 和 "A" 都在美式键盘的第二行。

示例 2：

输入：words = ["omk"]

输出：[]

示例 3：

输入：words = ["adsdf","sfd"]

输出：["adsdf","sfd"]



提示：

1 <= words.length <= 20
1 <= words[i].length <= 100
words[i] 由英文字母（小写和大写字母）组成
 */
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
/* 第一行由字符 "qwertyuiop" 组成。
第二行由字符 "asdfghjkl" 组成。
第三行由字符 "zxcvbnm" 组成。 */
class Solution
{
public:
    vector<string> findWords(vector<string> &words)
    {
        array<int, 26> hash_map{
            2, 3, 3, 2, 1, 2, 2, 2, 1,
            2, 2, 2, 3, 3, 1, 1, 1, 1,
            2, 1, 1, 3, 1, 3, 1, 3};
        vector<string> ret;
        for_each(words.begin(), words.end(), [&ret, &hash_map](const string &word)
                 {
                     int str_value = hash_map[tolower(static_cast<int>(word[0])) - 'a'],i;
                     size_t size = word.size();
                     for (i = 0; i < size && hash_map[tolower(static_cast<int>(word[i])) - 'a'] == str_value; ++i);
                     if(i>= size)
                        ret.push_back(word); });
        return ret;
    }
};

// int main()
// {
//     vector<string> words{"Hello", "Alaska", "Dad", "Peace"};
//     Solution sl;
//     const auto &vc = sl.findWords(words);
//     for_each(vc.begin(), vc.end(), [](const string &v)
//              { cout << v << " "; });
//     cout << endl;
//     return 0;
// }
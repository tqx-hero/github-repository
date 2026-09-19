/**
 * 1143. 最长公共子序列
中等
相关标签
premium lock icon
相关企业
提示
给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。



示例 1：

输入：text1 = "abcde", text2 = "ace"
输出：3
解释：最长公共子序列是 "ace" ，它的长度为 3 。
示例 2：

输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc" ，它的长度为 3 。
示例 3：

输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0 。


提示：

1 <= text1.length, text2.length <= 1000
text1 和 text2 仅由小写英文字符组成。
 */
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//动态规划。使用一个m*n的二维数组(m=text1的长度，n=text2的长度)，用来记录从开始截止到每个下标所对应的最长公共子序列的最大长度
//dp的值初值设置为-1，表示当前下标还没有统计子序列长度，需要继续统计。
//dp[x][y] ==0,表示截止到(x,y)公共子序列长度=0
//dp[x][y] > 0，直接返回
//状态转移方程：f(x,y)
// x/y下标越界时:f(x,y) =0
//text1[x] == text2[y]时：f(x,y) = f(x-1,y-1) +1,
//text1[x] != text2[y]时：f(x,y) = max(f(x-1,y),f(x,y-1))
class Solution
{

    int get_max_length(string &text1, string &text2, vector<vector<int>> &dp, int x, int y)
    {
        if (x == -1 || y == -1 || !dp[x][y])
            return 0;
        if (dp[x][y] == -1)
        {
            if (text1[x] == text2[y])
                dp[x][y] = get_max_length(text1, text2, dp, x - 1, y - 1) + 1;
            else
                dp[x][y] = max(get_max_length(text1, text2, dp, x - 1, y), get_max_length(text1, text2, dp, x, y - 1));
        }
        return dp[x][y];
    }

public:
    int longestCommonSubsequence(string text1, string text2)
    {
        // 使用二维数组，记录公共子序列的字符
        int row_size = static_cast<int>(text1.size()), col_size = static_cast<int>(text2.size());
        vector<vector<int>> dp(row_size, vector<int>(col_size, -1));
        return get_max_length(text1, text2, dp, row_size - 1, col_size - 1);
    }
};

// int main()
// {
//     // string text1 = "abcde", text2 = "ace";
//     // string text1 = "abc", text2 = "abc";
//     // string text1 = "abc", text2 = "def";
//     string text1 = "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc",
//      text2 = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
//     Solution sl;
//     cout << sl.longestCommonSubsequence(text1, text2) << endl;
//     return 0;
// }
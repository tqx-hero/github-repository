/**
 * 2437. 有效时间的数目
简单
相关标签
premium lock icon
相关企业
提示
给你一个长度为 5 的字符串 time ，表示一个电子时钟当前的时间，格式为 "hh:mm" 。最早 可能的时间是 "00:00" ，最晚 可能的时间是 "23:59" 。

在字符串 time 中，被字符 ? 替换掉的数位是 未知的 ，被替换的数字可能是 0 到 9 中的任何一个。

请你返回一个整数 answer ，将每一个 ? 都用 0 到 9 中一个数字替换后，可以得到的有效时间的数目。



示例 1：

输入：time = "?5:00"
输出：2
解释：我们可以将 ? 替换成 0 或 1 ，得到 "05:00" 或者 "15:00" 。注意我们不能替换成 2 ，因为时间 "25:00" 是无效时间。所以我们有两个选择。
示例 2：

输入：time = "0?:0?"
输出：100
解释：两个 ? 都可以被 0 到 9 之间的任意数字替换，所以我们总共有 100 种选择。
示例 3：

输入：time = "??:??"
输出：1440
解释：小时总共有 24 种选择，分钟总共有 60 种选择。所以总共有 24 * 60 = 1440 种选择。


提示：

time 是一个长度为 5 的有效字符串，格式为 "hh:mm" 。
"00" <= hh <= "23"
"00" <= mm <= "59"
字符串中有的数位是 '?' ，需要用 0 到 9 之间的数字替换。
 */
#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
    int countTime(string time)
    {
        char c1 = time[0];
        char c2 = time[1];
        char c3 = time[3];
        char c4 = time[4];
        int hour_total_count = 1, minute1_total_count = 1, minute2_total_count = 1;
        // 统计小时
        if (c1 == '?')
        {
            if (c2 == '?')
                hour_total_count = 24;
            else if (c2 < '4')
                hour_total_count = 3;
            else
                hour_total_count = 2;
        }
        else if (c2 == '?')
        {
            // c2等于?但c1不等于?时，根据c1的值分类
            // c1等于0、1时，c2取值为0~9十种
            if (c1 < '2')
                hour_total_count = 10;
            else
                hour_total_count = 4;
        }
        // 统计分钟
        if (c3 == '?')
            minute1_total_count = 6;
        if (c4 == '?')
            minute2_total_count = 10;
        return hour_total_count * minute1_total_count * minute2_total_count;
    }
};

// int main()
// {
//     // string time = "?5:00";
//     // string time = "0?:0?";
//     // string time = "??:??";
//     string time = "?2:16";
//     Solution sl;
//     cout << sl.countTime(time) << endl;
//     return 0;
// }
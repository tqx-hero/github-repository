/**
 * 441. 排列硬币
简单
相关标签
premium lock icon
相关企业
你总共有 n 枚硬币，并计划将它们按阶梯状排列。对于一个由 k 行组成的阶梯，其第 i 行必须正好有 i 枚硬币。阶梯的最后一行 可能 是不完整的。

给你一个数字 n ，计算并返回可形成 完整阶梯行 的总行数。



示例 1：


输入：n = 5
输出：2
解释：因为第三行不完整，所以返回 2 。
示例 2：


输入：n = 8
输出：3
解释：因为第四行不完整，所以返回 3 。


提示：

1 <= n <= 231 - 1
 */
#include <iostream>
#include <cmath>
using namespace std;

class Solution
{
public:
    int arrangeCoins(int n)
    {
        long long total = (long long)n << 1;
        long long  squart_factor = static_cast<long long>(sqrt(total));
        long long sub = squart_factor * (squart_factor + 1) - total;
        if (sub <= 0)
            return squart_factor;
        if (squart_factor * (squart_factor - 1) >= n)
            return squart_factor - 1;
        return squart_factor;
    }
};

// int main()
// {
//     // int n = 4;
//     int n = 1804289383;
//     Solution sl;
//     cout << sl.arrangeCoins(n) << endl;
//     return 0;
// }
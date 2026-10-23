/**
 * 279. 完全平方数
中等
相关标签
premium lock icon
相关企业
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。



示例 1：

输入：n = 12
输出：3
解释：12 = 4 + 4 + 4
示例 2：

输入：n = 13
输出：2
解释：13 = 4 + 9

提示：

1 <= n <= 104
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
// 动态规划
// 从1递推到n，
// 使用数组dp记录当前值完全平方数和的最少数量
// 从1开始计算每个值的平方(<=n)，把这些平方数dp 设置为1
// 还要把每个完全平方数的2倍，3倍，4倍..直到平方倍之前所有<=10000的数添加到dp
class Solution
{
public:
    int numSquares(int n)
    {
        if (n == 1)
            return 1;
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 1;
        int i;
        for (i = 2; i <= n; ++i)
        {
            dp[i] = min(dp[i], dp[i - 1] + 1);
            // 修改当前值到其平方之间的数的dp值
            int j, cur_idx;
            for (j = 2; j < i && (cur_idx = i * j) <= n; ++j)
                dp[cur_idx] = min(j, dp[cur_idx]);
            if ((cur_idx = i * i) <= n)
            {
                dp[cur_idx] = 1;
                if (cur_idx == n)
                    return 1;
            }
        }
        return dp[n];
    }
};

int main()
{
    int n = 12;
    Solution sl;
    cout << sl.numSquares(n) << endl;
    return 0;
}
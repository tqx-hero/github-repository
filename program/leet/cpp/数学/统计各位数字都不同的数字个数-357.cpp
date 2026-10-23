/**
 * 357. 统计各位数字都不同的数字个数
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数 n ，统计并返回各位数字都不同的数字 x 的个数，其中 0 <= x < 10n 。


示例 1：

输入：n = 2
输出：91
解释：答案应为除去 11、22、33、44、55、66、77、88、99 外，在 0 ≤ x < 100 范围内的所有数字。
示例 2：

输入：n = 0
输出：1


提示：

0 <= n <= 8
 */
#include <iostream>
using namespace std;

class Solution
{
public:
    int countNumbersWithUniqueDigits(int n)
    {
        // n =0 ,取值范围:[0,1)
        int cnt = 1;
        for (int i = 1; i <= n; ++i)
        {
            // 数的最高位取值范围为1~9这9种
            int cur_cnt = 9, high_cnt = 9;
            for (int j = i - 1; j > 0; --j)
            {
                // 从第二位开始取值范围从9个逐步-1
                cur_cnt *= high_cnt;
                --high_cnt;
            }
            cnt += cur_cnt;
        }
        return cnt;
    }
};

// int main()
// {
//     int n = 3;
//     Solution sl;
//     cout << sl.countNumbersWithUniqueDigits(n) << endl;
//     return 0;
// }
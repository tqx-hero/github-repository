//
// Created by Administrator on 2026/7/7.
//
/**
* 3754. 连接非零数字并乘以其数字和 I
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数 n。

将 n 中所有的 非零数字 按照它们的原始顺序连接起来，形成一个新的整数 x。如果不存在 非零数字 ，则 x = 0。

sum 为 x 中所有数字的 数字和 。

返回一个整数，表示 x * sum 的值。



示例 1：

输入： n = 10203004

输出： 12340

解释：

非零数字是 1、2、3 和 4。因此，x = 1234。
数字和为 sum = 1 + 2 + 3 + 4 = 10。
因此，答案是 x * sum = 1234 * 10 = 12340。
示例 2：

输入： n = 1000

输出： 1

解释：

非零数字是 1，因此 x = 1 且 sum = 1。
因此，答案是 x * sum = 1 * 1 = 1。


提示：

0 <= n <= 109
 * @return
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    long long sumAndMultiply(int n) {
        if (!n)
            return 0;
        vector<long long> stack;
        long long sum = 0;
        while (n) {
            long long remain = n % 10;
            if (remain) {
                sum += remain;
                stack.push_back(remain);
            }
            n /= 10;
        }
        //统计余数，即倒栈，将他们乘起来得到x
        long long x = 0;
        for (int i = stack.size() - 1; i >= 0; i--)
            x = x * 10 + stack.at(i);
        return sum * x;
    }
};

// int main() {
//     int n = 10203004;
//     Solution sl;
//     cout << sl.sumAndMultiply(n) << endl;
//     return 0;
// }

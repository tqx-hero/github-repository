//
// Created by Administrator on 2026/8/6.
//
/**
* 3345. 最小可整除数位乘积 I
简单
相关标签
premium lock icon
相关企业
提示
给你两个整数 n 和 t 。请你返回大于等于 n 的 最小 整数，且该整数的 各数位之积 能被 t 整除。



示例 1：

输入：n = 10, t = 2

输出：10

解释：

10 的数位乘积为 0 ，可以被 2 整除，所以它是大于等于 10 且满足题目要求的最小整数。

示例 2：

输入：n = 15, t = 3

输出：16

解释：

16 的数位乘积为 6 ，可以被 3 整除，所以它是大于等于 15 且满足题目要求的最小整数。



提示：

1 <= n <= 100
1 <= t <= 10
 * @return
 */

#include <iostream>
#include <ostream>

class Solution {
    int getMulNumber(int n) {
        int res = 1;
        while (n) {
            res *= n % 10;
            n /= 10;
        }
        return res;
    }

public:
    int smallestNumber(int n, int t) {
        while (true) {
            if (getMulNumber(n) % t == 0)
                return n;
            n++;
        }
    }
};

// int main() {
//     int n=15,t=3;
//     Solution sl;
//     std::cout << sl.smallestNumber(n,t) << std::endl;
//     return 0;
// }

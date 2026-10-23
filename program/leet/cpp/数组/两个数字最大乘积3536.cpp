//
// Created by Administrator on 2026/7/25.
//
/**
* 3536. 两个数字的最大乘积
简单
相关标签
premium lock icon
相关企业
提示
给定一个正整数 n。

返回 任意两位数字 相乘所得的 最大 乘积。

注意：如果某个数字在 n 中出现多次，你可以多次使用该数字。



示例 1：

输入： n = 31

输出： 3

解释：

n 的数字是 [3, 1]。
任意两位数字相乘的结果为：3 * 1 = 3。
最大乘积为 3。
示例 2：

输入： n = 22

输出： 4

解释：

n 的数字是 [2, 2]。
任意两位数字相乘的结果为：2 * 2 = 4。
最大乘积为 4。
示例 3：

输入： n = 124

输出： 8

解释：

n 的数字是 [1, 2, 4]。
任意两位数字相乘的结果为：1 * 2 = 2, 1 * 4 = 4, 2 * 4 = 8。
最大乘积为 8。


提示：

10 <= n <= 109
 * @return
 */

#include <iostream>
#include <ostream>

class Solution {
public:
    int maxProduct(int n) {
        int buckets[10]{0};
        while (n) {
            buckets[n % 10]++;
            n /= 10;
        }
        int mul1 = -1;
        for (int i = 9; i >= 0; i--) {
            int count = buckets[i];
            if (!count)
                continue;
            if (mul1 == -1) {
                mul1 = i;
                --count;
            }
            if (count)
                return mul1 * i;
        }
        return  0;
    }
};

// int main() {
//     using namespace std;
//     int n =124;
//     Solution sl;
//     cout << sl.maxProduct(n) <<endl;
//     return 0;
// }

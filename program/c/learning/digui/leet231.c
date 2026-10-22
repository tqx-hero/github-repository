//
// Created by Administrator on 2026/6/29.
//
/**
* 231. 2 的幂
简单
相关标签
premium lock icon
相关企业
给你一个整数 n，请你判断该整数是否是 2 的幂次方。如果是，返回 true ；否则，返回 false 。

如果存在一个整数 x 使得 n == 2x ，则认为 n 是 2 的幂次方。



示例 1：

输入：n = 1
输出：true
解释：20 = 1
示例 2：

输入：n = 16
输出：true
解释：24 = 16
示例 3：

输入：n = 3
输出：false


提示：

-231 <= n <= 231 - 1


进阶：你能够不使用循环/递归解决此问题吗？
 * @return
 */

#include <stdio.h>
//整型2的幂，首先要是正数，所以负数与0排除
//再就是二进制表示必须有且仅有1位是1，多一位少一位都不满足。
//少一位的情况，即没有1的情况那就是0了
bool isPowerOfTwo(int n) {
    // if (n <= 0)
    //     return false;
    // int count = n & 1 ? 1 : 0;
    // for (int i = 1; n && i <= 31; i++) {
    //     n >>= 1;
    //     if (n & 1 && ++count > 1)
    //         return false;
    // }
    // return true;
    return n > 0 && (n & (n - 1)) == 0;
}

int main() {
    int n = 32;
    printf("%d\n", isPowerOfTwo(n));
    return 0;
}

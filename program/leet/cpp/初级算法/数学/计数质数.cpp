//
// Created by Administrator on 2026/8/15.
//
/**
* 计数质数
给定整数 n ，返回 所有小于非负整数 n 的质数的数量 。 
示例 1：
输入：
n = 10
输出：
4
解释：
小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
示例 2：
输入：
n = 0
输出：
0
示例 3：
输入：
n = 1
输出
：0
  提示：
• 0 <= n <= 5 * 106
 * @return
 */

#include <iostream>
#include <vector>

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2)
            return 0;
        std::vector<bool> flags(n, false);
        flags[2] = true;
        int cnt = 1;
        //仅判断奇数是否为质数，偶数大于2的都不是质数
        for (int i = 3; i < n; i += 2) {
            //如果它是和数，直接跳过
            if (flags[i])
                continue;
            //当前元素是质数，统计数+1，并且更新它的两倍、三倍、四倍...所有的小于n的数为和数
            cnt++;
            for (int k = i << 1; k < n; k += i)
                flags[k] = true;
        }
        return cnt;
    }
};

// int main() {
//     int n =2;
//     Solution sl;
//     std::cout << sl.countPrimes(n) << std::endl;
//     return 0;
// }

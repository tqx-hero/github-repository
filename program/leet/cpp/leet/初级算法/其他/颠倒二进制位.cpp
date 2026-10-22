//
// Created by Administrator on 2026/8/16.
//
/**
* 颠倒二进制位
颠倒给定的 32 位有符号整数的二进制位。

  

示例 1：

输入：n = 43261596

输出：964176192

解释：

整数	二进制
43261596	00000010100101000001111010011100
964176192	00111001011110000010100101000000
示例 2：

输入：n = 2147483644

输出：1073741822

解释：

整数	二进制
2147483644	01111111111111111111111111111100
1073741822	00111111111111111111111111111110
  

提示：

0 <= n <= 231 - 2
n 为偶数
  

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnc5vg/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */

#include <iostream>

class Solution {
public:
    int reverseBits(int n) {
        int ret = 0;
        for (int i = 1; i < 31; i++) {
            if (n & (1 << i))
                ret |= 1 << (31 - i);
        }
        return ret;
    }
};
//
// int main() {
//     Solution sl;
//     int n = 43261596;
//     std::cout << sl.reverseBits(n) << std::endl;
//     return 0;
// }

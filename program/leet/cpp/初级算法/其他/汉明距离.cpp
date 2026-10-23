//
// Created by Administrator on 2026/8/16.
//
/**
* 汉明距离
两个整数之间的 汉明距离 指的是这两个数字对应二进制位不同的位置的数目。

给你两个整数 x 和 y，计算并返回它们之间的汉明距离。

  

示例 1：

输入：x = 1, y = 4
输出：2
解释：
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
上面的箭头指出了对应二进制位不同的位置。
示例 2：

输入：x = 3, y = 1
输出：1
  

提示：

0 <= x, y <= 231 - 1
  

注意：本题与 2220. 转换数字的最少位翻转次数 相同。

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnyode/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */

#include <iostream>

class Solution {
public:
    int hammingDistance(int x, int y) {
        int xor_val = x ^ y, dist = 0;
        while (xor_val) {
            if (xor_val & 0x1)
                dist++;
            xor_val >>= 1;
        }
        return dist;
    }
};

// int main() {
//     int x = 1, y = 3;
//     Solution sl;
//     std::cout << sl.hammingDistance(x,y) << std::endl;
//     return 0;
// }

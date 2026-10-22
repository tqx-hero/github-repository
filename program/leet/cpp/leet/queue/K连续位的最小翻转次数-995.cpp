//
// Created by Administrator on 2026/8/5.
//
/**
* 995. K 连续位的最小翻转次数
困难
相关标签
premium lock icon
相关企业
给定一个二进制数组 nums 和一个整数 k 。

k位翻转 就是从 nums 中选择一个长度为 k 的 子数组 ，同时把子数组中的每一个 0 都改成 1 ，把子数组中的每一个 1 都改成 0 。

返回数组中不存在 0 所需的最小 k位翻转 次数。如果不可能，则返回 -1 。

子数组 是数组的 连续 部分。



示例 1：

输入：nums = [0,1,0], K = 1
输出：2
解释：先翻转 A[0]，然后翻转 A[2]。
示例 2：

输入：nums = [1,1,0], K = 2
输出：-1
解释：无论我们怎样翻转大小为 2 的子数组，我们都不能使数组变为 [1,1,1]。
示例 3：

输入：nums = [0,0,0,1,0,1,1,0], K = 3
输出：3
解释：
翻转 A[0],A[1],A[2]: A变成 [1,1,1,1,0,1,1,0]
翻转 A[4],A[5],A[6]: A变成 [1,1,1,1,1,0,0,0]
翻转 A[5],A[6],A[7]: A变成 [1,1,1,1,1,1,1,1]


提示：

1 <= nums.length <= 105
1 <= k <= nums.length
 * @return
 */
#include <iostream>
#include <vector>
using namespace std;

//todo暴力遍历会超时，O(n*k)在n为10万样本的情况下会有上亿的复杂度，需要进行优化
class Solution {
public:
    int minKBitFlips(vector<int> &nums, int k) {
        size_t size = nums.size();
        int i, maxIndex = static_cast<int>(size) - k, cnt = 0;
        for (i = 0; i <= maxIndex; i++) {
            if (nums[i])
                continue;
            for (int j = 0; j < k; j++)
                nums[i + j] ^= 1;
            cnt++;
        }
        for (; i < size; i++) {
            if (!nums[i])
                return -1;
        }
        return cnt;
    }
};

// int main() {
//     vector<int> nums {0,1,0};
//     // vector<int> nums {1,1,0};
//     // vector<int> nums {0,0,0,1,0,1,1,0};
//     int k=1;
//     Solution sl;
//     cout << sl.minKBitFlips(nums,k) << endl;
//     return 0;
// }

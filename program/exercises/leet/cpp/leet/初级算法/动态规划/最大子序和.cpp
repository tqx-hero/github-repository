//
// Created by Administrator on 2026/8/14.
//
/**
* 最大子序和
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。

  

示例 1：

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
示例 2：

输入：nums = [1]
输出：1
示例 3：

输入：nums = [5,4,-1,7,8]
输出：23
  

提示：

1 <= nums.length <= 105
-104 <= nums[i] <= 104
  

进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xn3cg3/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    //使用前缀和
    // int maxSubArray(vector<int> &nums) {
    //     size_t size = nums.size();
    //     if (size == 1)
    //         return nums[0];
    //     vector<int> prefix_sum;
    //     prefix_sum.resize(size);
    //     prefix_sum[0] = nums[0];
    //     int i;
    //     for (i = 1; i < size; ++i)
    //         prefix_sum[i] = prefix_sum[i - 1] + nums[i];
    //     int cur_min_idx = 0, cur_max_idx = cur_min_idx, total_max = prefix_sum[cur_min_idx];
    //     for (i = 1; i < size; i++) {
    //         int cur_num = prefix_sum[i], cur_max = prefix_sum[cur_max_idx], cur_min = prefix_sum[cur_min_idx];
    //         total_max = max(total_max, nums[i] > cur_num ? nums[i] : cur_num);
    //         if (cur_num == cur_max)
    //             continue;
    //         if (cur_num > cur_max)
    //             cur_max_idx = i;
    //         else {
    //             if (cur_min_idx != cur_max_idx)
    //                 total_max = std::max(total_max, cur_max - cur_min);
    //             if (cur_num < cur_min)
    //                 cur_min_idx = cur_max_idx = i;
    //         }
    //     }
    //     if (cur_min_idx != cur_max_idx)
    //         total_max = std::max(total_max, prefix_sum[cur_max_idx] - prefix_sum[cur_min_idx]);
    //     return total_max;
    // }
    //使用动态规划
    //每次取值，与前面的和相加，如果前面的和为正数，直接相加(因为加正数肯定比自身大)，如果前面和为负数，那就取自身为以自身为终点的最大值
    int maxSubArray(vector<int> &nums) {
        size_t size = nums.size();
        if (size == 1)
            return nums[0];
        vector<int> dp;
        dp.resize(size);
        int total_max = dp[0] = nums[0];
        for (int i = 1; i < size; i++) {
            //如果前面所求的和为正数，进行相加，如果为负数，直接取nums[i]自身
            dp[i] = nums[i] + max(dp[i - 1], 0);
            total_max = max(dp[i], total_max);
        }
        return total_max;
    }
};

// int main() {
//     // vector<int> nums{-2, -1};
//     vector<int> nums{5, 4, -1, 7, 8};
//     // vector<int> nums{-2, 1, -3, 4, -1, 2, 1, -5, 4};
//     Solution sl;
//     cout << sl.maxSubArray(nums) << endl;
//     return 0;
// }

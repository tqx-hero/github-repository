//
// Created by 田庆新 on 2026/8/31.
//
/**
* 53. 最大子数组和
已解答
中等
相关标签
premium lock icon
相关企业
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组是数组中的一个连续部分。



示例 1：

输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
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
 * @return
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int> &nums) {
        //使用动态规划，遍历数组，每次获取i-1位置的最大和，如果最大和为负数，令i位置的最大和为nums[i],如果i-1最大和非负
        //那就与其相加，最后统计最大和即可
        int ret, size = static_cast<int>(nums.size());
        vector<int> cur_max_prefix(size, 0);
        cur_max_prefix[0] = ret = nums[0];
        int i = 1;
        for (; i < size; ++i) {
            cur_max_prefix[i] = max(cur_max_prefix[i - 1], 0) + nums[i];
            if (cur_max_prefix[i] > ret)
                ret = cur_max_prefix[i];
        }
        return ret;
    }
};

// int main() {
//     return 0;
// }
